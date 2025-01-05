#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

typedef enum {
    CMD_EXTERNAL,
    CMD_BUILTIN
} cmd_type;

typedef struct s_builtin {
    const char * name;
    int (*func)(char **args);
} builtin;

int execute_command(t_command *cmd);
cmd_type get_command_type(const char *cmd_name);
int wait_for_children(void);
int handle_redirections(t_command *cmd);

#endif