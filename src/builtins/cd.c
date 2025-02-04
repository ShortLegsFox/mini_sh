/**
* \file cd.c
 * \cd command for mini_sh.
 * \author SLF
 * \version 0.1
 * \date 05/01/2025
 *
 * Change current directory location.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"


int builtin_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "cd: missing argument\n");
        return 1;
    }

    if (chdir(args[1]) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}