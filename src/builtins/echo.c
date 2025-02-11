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

        // Vérifie si l'argument commence par '$'
        if (arg[0] == '$' && strlen(arg) > 1) {
            char *env_value = getenv(arg + 1); // Récupère la valeur de la variable
            if (env_value) {
                printf("%s", env_value);
            }
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