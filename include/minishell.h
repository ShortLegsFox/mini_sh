#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define STDOUT 1
#define STDERR 2
#define MAX_LENGTH 4096
#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 128

typedef struct s_command {
    char *name;          // Command name
    char * args[10];         // Command arguments
    char *input_file;    // Input redirection
    char *output_file;   // Output redirection
    int append_output;   // Flag for append mode
    struct s_command *pipe_next;  // Next command in pipeline
} t_command;

void display_prompt(void);
void free_command(t_command *cmd);

#endif