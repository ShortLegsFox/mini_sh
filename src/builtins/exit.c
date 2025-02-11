/**
* \file exit.c
 * \exit command for mini_sh.
 * \author Ian B, Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * list directories and file from current position.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"

int builtin_exit(char **args) {
    printf("\nGoodbye dear user !\n");
    exit(0);
}