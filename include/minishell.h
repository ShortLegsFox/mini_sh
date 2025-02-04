#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include "typedef.h"

#define STDOUT 1
#define STDERR 2
#define MAX_LENGTH 4096
#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 128

void display_prompt(void);
void free_command(t_command *cmd);

#endif