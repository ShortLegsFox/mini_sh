/**
* \file export.c
 * \export command for mini_sh (env variable).
 * \author Ian B, Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Change current directory location.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "builtins.h"


int builtin_export(char **args) {
    if (!args[1] || !strchr(args[1], '=')) {
        fprintf(stderr, "Usage: export VAR=value\n");
        return 1;
    }
    char *name = strtok(args[1], "=");
    char *value = strtok(NULL, "");
    if (setenv(name, value, 1) != 0) {
        perror("setenv");
        return 1;
    }
    return 0;
}