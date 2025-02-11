/**
* \file pwd.c
 * \pwd command for mini_sh.
 * \author Ian B, Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Show current date (from system).
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"

int builtin_pwd(char **args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd))) {
        printf("%s\n", cwd);
        return 1;
    }

    return 0;
}
