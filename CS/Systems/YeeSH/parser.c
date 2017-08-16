/* INIT ***********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "parser.h"

/* FUNCTIONS ******************************************************************/

/* init_command: initializes a command
 * Initializes default values:
 *   input_fd = stdin
 *   output_fd = stdout
 *   error_fd = stderr
 *   next_operator = NULL
 *   prev_command = NULL
 *   next_command = NULL
 */
void init_command (command *current){
    current->input_fd = STDIN_FILENO;
    current->output_fd = STDOUT_FILENO;
    current->error_fd = STDERR_FILENO;
    current->next_command = 0;
    current->pipe_output = 0;
}

/* break_line: breaks a line into a linked list of commands
 * Input: a string of the line to parse
 * Output: a linked list of parsed commands
 */
command *break_line (char *line){
    line = strsep(&line, "\n");
    char *input;
    char *separators = "|;|";
    command *last;
    command *current;
    command *lead = (command *)malloc(sizeof(command));
    char sep = first_occurence(line, separators);

    if (sep) {
        input = strsep(&line, separators);
    }
    else {
        input = line;
    }

    input = trim(input);
    lead = parse(input, sep);
    last = lead;

    while(line && sep){
        sep = first_occurence(line, separators);
        if (sep) {
            input = strsep(&line, separators);
        }
        else {
            input = line;
        }
        input = trim(input);
        current = parse(input, sep);
        last->next_command = current;
        last = current;
    }
    return lead;
}

/* parse: takes a string and turn it into a command struct
 * TODO long description
 */
command *parse (char *line, char next_op){
    command *current = (command *)malloc(sizeof(command));
    init_command(current);
    char *elements[256];

    if (next_op == '|') {
        current->pipe_output = 1;
    }
    
    int i = 0;
    while (line) {
        elements[i] = strsep(&line, " ");
        i++;
    }
    int c;

    int arg_count = 0;
    for (c = 0 ; c < i ; c++) {
        if (strstr(elements[c], "<")) {
            current->input_fd = open(elements[++c], O_RDONLY);
        }
        else if (strstr(elements[c], "2>>")) {
            current->error_fd = open(elements[++c], O_CREAT | O_APPEND | O_WRONLY, 0644);
        }
        else if (strstr(elements[c], "2>")) {
            current->error_fd = open(elements[++c], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        }
        else if (strstr(elements[c], "&>>")) {
            current->error_fd = open(elements[++c], O_CREAT | O_APPEND | O_WRONLY, 0644);
            current->output_fd = open(elements[c], O_CREAT | O_APPEND | O_WRONLY, 0644);
        }
        else if (strstr(elements[c], "&>")) {
            current->error_fd = open(elements[++c], O_CREAT | O_TRUNC | O_WRONLY, 0644);
            current->output_fd = open(elements[c], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        }
        else if (strstr(elements[c], ">>")) {
            current->output_fd = open(elements[++c], O_CREAT | O_APPEND | O_WRONLY, 0644);
        }
        else if (strstr(elements[c], ">")) {
            current->output_fd = open(elements[++c], O_CREAT | O_TRUNC | O_WRONLY, 0644);
        }

        else {
            current->arguments[arg_count++] = elements[c];
        }
    }
    if (current->input_fd == -1 ||
        current->output_fd == -1 ||
        current->error_fd == -1) {
        fprintf(stderr, "YeeSH Error %d: %s\n", errno, strerror(errno));
        return NULL;
    }
    current->arguments[arg_count] = 0;
    return current;
}

/* first_occurence: finds the first character in keyset that appears in line
 * TODO long description
 */

char first_occurence(char *line, char *keyset) {
    char *keyset_original = keyset;
    while (*line++) {
        while (*keyset++) {
            if (*line == *keyset) {
                return *line;
            }
        }
        keyset = keyset_original;
    }
    return 0;
}

/* trim: deletes white spaces in the beginning and end
 * deletes white spaces at the beginning and end of a given line
 */
char *trim (char *str){
    char *end;
    while (*str == ' ') {
        str++;
    }

    if (*str == 0) {
        return str;
    }

    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') {
        end--;
    }

    *(end + 1) = 0;

    return str;
}

//int main(int argc, char *argv[]) {
//
//    command *current;
//    char line[] = "cat -a -l < hello.txt >> blah.txt 2> errs.txt\n";
//    printf("%s\n", line);
//    current = parse(line, ';');
//    printf("commands: %s\n", current->command);
//    printf("input_fd: %d\n", current->input_fd);
//    printf("output_fd: %d\n", current->output_fd);
//    printf("error_fd: %d\n", current->error_fd);
//    printf("next_op: %c\n", current->next_operator);
//    int i = 0;
//    printf("arguments\n");
//    while (*(current->arguments + i)) {
//        printf("%s\n", *(current->arguments + i));
//        i++;
//    }
//    return 0;
//}
