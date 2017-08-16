#ifndef PARSER_H
#define PARSER_H

typedef struct command {
    int input_fd; // input file descriptor
    int output_fd; // output file descriptor
    int error_fd; // error file descriptor
    char *command; // command
    char *arguments[256]; // arguments to command
    int return_value; // return value of the commnad
    int pipe_output; // boolean, if this function is putting anything into a pipe
    struct command *next_command; // next command
} command;

void init_command(command *current);
command *break_line(char *input);
command *parse(char *line, char next_op);
char *trim(char *line);
char first_occurence(char *line, char *keyset);
#endif
