/**
 * \file main.c
 * \brief main for minishell project
 * \author Ian B, Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Basic parsing options main exemple c file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "minishell.h"
#include "executor.h"
#include "parser.h"


/**
 * Display prompt
 *
 * void method
 * Showing the "mini_sh$ + current folder" prompt in terminal with stdout to retrieve command input from the user
 */
void display_prompt() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("mini_sh$ ");
    } else {
        char *last_dir = strrchr(cwd, '/');
        if (last_dir != NULL) {
            last_dir++;
        } else {
            last_dir = cwd;
        }

        printf("mini_sh->%s$ ", last_dir);
    }
    fflush(stdout);
}


/**
 * Shell main loop
 *
 * \return 1 if it exit successfully
 */
int main(int argc, char **argv) {
    char command[MAX_CMD_LENGTH];
    int status = 0;

    while (1) {
        display_prompt();

        // -- Check for clean exit (in case of error or ctrl D / Z)
        if (fgets(command, MAX_CMD_LENGTH, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        // -- Removing newline character kept by fgets
        command[strcspn(command, "\n")] = '\0';

        // -- Parse input into a command
        t_command *cmd = parse_command_line(command);
        if (!cmd) continue;

        // -- Using the interpretor with the parsed command
        int pid = execute_command(cmd);
        if (pid > 0) {
            status = wait_for_children();
        }

        free_command(cmd);
    }

    return status;
}
