/* INIT ***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "execute.h"

/* FUNCTIONS ******************************************************************/

/* execute: runs a list of commands
 * Input: a list of commands, mostly read from the parse function
 * Output: 0 when successful
 */
int execute(command *list_o_commands){
    int i, status = 0;
    int fd[2];
    while (list_o_commands) {
        if (!strcmp(list_o_commands->arguments[0], "exit")) {
            exit(0);
        }
        else if (!strcmp(list_o_commands->arguments[0], "cd")) {
            if(chdir(list_o_commands->arguments[1])) {
                fprintf(stderr, "YeeSH Error %d: %s\n", errno, strerror(errno));
            }
        }
        else {
            i = fork();
            if (i == 0) {
                if (list_o_commands->pipe_output) { // means this command is feeding something to the next command
                    pipe(fd);
                    int j = fork();
                    if (j == -1) {
                        fprintf(stderr, "YeeSH: Error forking\n");
                        exit(1);
                    }
                    if (j == 0) { // 'child' aka current command aka write side of the pipe
                        close(fd[0]); // close read side
                        dup2(fd[1], STDOUT_FILENO);
                        dup2(list_o_commands->output_fd, STDOUT_FILENO);
                        execvp(list_o_commands->arguments[0], list_o_commands->arguments);
                        fprintf(stderr, "YeeSH: Command not found: %s\n", list_o_commands->arguments[0]);
                        exit(1);
                    }
                    else { // 'parent' aka next command aka read side of the pipe
                        wait(&j);
                        list_o_commands = list_o_commands->next_command;

                        close(fd[1]); // close write side
                        dup2(fd[0], STDIN_FILENO);
                        dup2(list_o_commands->output_fd, STDOUT_FILENO);
                        dup2(list_o_commands->error_fd, STDERR_FILENO);
                        execvp(list_o_commands->arguments[0], list_o_commands->arguments);
                        fprintf(stderr, "YeeSH: Command not found: %s\n", list_o_commands->arguments[0]);
                        exit(1);
                    }
                }
                else {
                    dup2(list_o_commands->output_fd, STDOUT_FILENO);
                    dup2(list_o_commands->error_fd, STDERR_FILENO);
                    execvp(list_o_commands->arguments[0], list_o_commands->arguments);
                    fprintf(stderr, "YeeSH: Command not found: %s\n", list_o_commands->arguments[0]);
                    exit(1); // something went wrong
                }
            }
            else {
                wait(&status);
                list_o_commands->return_value = WEXITSTATUS(status);
            }
        }
        if (list_o_commands->pipe_output) {
            list_o_commands = list_o_commands->next_command->next_command; // skip twice
        }
        else {
            list_o_commands = list_o_commands->next_command;
        }
    }
    return WEXITSTATUS(status);
}
