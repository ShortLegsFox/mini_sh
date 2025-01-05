/**
* \file parser.c
 * \parser file for mini_sh.
 * \author SLF
 * \version 0.1
 * \date 05/01/2025
 *
 * Parse command input for mini shell project.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"

t_command *parse_command_line(char *line) {
    if (!line) {
        perror("parse");
        return NULL;
    }

    t_command *command = malloc(sizeof(t_command));
    if (!command) {
        perror("malloc");
        return NULL;
    }

    command->name = NULL;
    //command->args = NULL;
    command->input_file = NULL;
    command->output_file = NULL;
    command->append_output = 0;
    command->pipe_next = NULL;

    char * token = strtok(line, " ");
    if (!token) {
        perror("strtok");
        free(command);
        return NULL;
    }

    int i = 0;

    while (token != NULL) {
        if (i == 0) {
            command->name = strdup(token);
        } else {
            command->args[i - 1] = strdup(token);
        }
        token = strtok(NULL, " ");
        i++;
    }

    return command;
}

void free_command(t_command *cmd) {

}