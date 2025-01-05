/**
 * \file main.c
 * \brief Basic parsing options skeleton.
 * \author SLF
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
        printf("mini_sh: %s$ ", cwd);
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

        if (fgets(command, MAX_CMD_LENGTH, stdin) == NULL) {
            printf("\nGoodbye!\n");
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        t_command *cmd = parse_command_line(command);
        if (!cmd) continue;

        int pid = execute_command(cmd);
        if (pid > 0) {  // External command
            status = wait_for_children();
        }

        // Free command structure
        free_command(cmd);
    }

    return status;
}
