/**
* \file unset.c
 * \unset command for mini_sh (env variable).
 * \author Ian B, Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Change current directory location.
 */
#include <stdio.h>
#include <stdlib.h>
#include "builtins.h"


int builtin_unset(char **args) {
    if (!args[1]) {
        fprintf(stderr, "Usage: unset VAR\n");
        return 1;
    }
    if (unsetenv(args[1]) != 0) {
        perror("unsetenv");
        return 1;
    }
    return 0;
}
