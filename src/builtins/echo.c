/**
* \file ps.c
 * \ps command for mini_sh.
 * \author SLF
 * \version 0.1
 * \date 05/01/2025
 *
 * list processes of current machine.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"


int builtin_echo(char **args) {
    for (int i = 1; args[i] != NULL; i++) {
        char *arg = args[i];
        int len = strlen(arg);

        // If the first and last characters are quotes, print inside part only
        if ((arg[0] == '"' || arg[0] == '\'') && arg[len - 1] == arg[0] && len > 1) {
            fwrite(arg + 1, 1, len - 2, stdout);
        } else {
            printf("%s", arg);
        }

        if (args[i + 1] != NULL) {
            printf(" ");
        } else {
            printf("\n");
        }
    }
    return 0;
}