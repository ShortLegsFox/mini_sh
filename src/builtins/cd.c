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
    if (args[0] == NULL) {
        // cd sans argument -> aller au home directory
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
        return chdir(home);
    }
    if (chdir(args[0]) != 0) {
        perror("cd");
        return 1;
    }
    return 0;
}