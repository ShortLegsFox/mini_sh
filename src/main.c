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
#include <minishell.h>
#include "commands.h"

/**
 * Display prompt
 *
 * void method
 * Showing the "mini_sh$ " prompt in terminal with stdout to retrieve command input from the user
 */
void display_prompt() {
    printf("mini_sh$ ");
    fflush(stdout);
}

/**
 * Shell main loop
 *
 * \return 1 if it exit successfully
 */
int main(int argc, char **argv) {
    char command[MAX_LENGTH];

    while (1) {
        display_prompt();

        if (fgets(command, MAX_LENGTH, stdin) == NULL) {
            printf("Exiting mini_sh, Goodbye !");
            break;
        }

        //printf("You entered: %s\n", command);

        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "ls") == 0) {
            ls_function();
        }

        if (strcmp(command, "who") == 0) {
            who_function();
        }

        if (strcmp(command, "ps") == 0) {
            ps_function();
        }

        if (strcmp(command, "date") == 0) {
            date_function();
        }

        if (strcmp(command, "exit") == 0) {
            printf("Exiting mini_sh, Goodbye !");
            break;
        }
    }
    return EXIT_SUCCESS;
}
