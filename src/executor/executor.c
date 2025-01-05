/**
* \file executor.c
 * \executor file for mini_sh.
 * \author SLF
 * \version 0.1
 * \date 05/01/2025
 *
 * Execute command input for mini shell project.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "executor.h"
#include "builtins.h"

static builtin t_builtins[] = {
    {"cd", &builtin_cd},
    {"date", &builtin_date},
    {"ls", &builtin_ls},
    {"ps", &builtin_ps},
    {"who", &builtin_who},
    {NULL, NULL}
};

cmd_type get_command_type(const char *cmd_name) {
    for (int i = 0; t_builtins[i].name != NULL; i++) {
        if (strcmp(cmd_name, t_builtins[i].name) == 0) {
            return CMD_BUILTIN;
        }
    }
    return CMD_EXTERNAL;
}

int execute_command(t_command *cmd) {
    if (!cmd || !cmd->name) return -1;

    if (get_command_type(cmd->name) == CMD_BUILTIN) {
        for (int i = 0; t_builtins[i].name != NULL; i++) {
            if (strcmp(cmd->name, t_builtins[i].name) == 0) {
                return t_builtins[i].func(cmd->args);
            }
        }
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {  // Processus fils
        // Gestion des redirections si nécessaire
        if (handle_redirections(cmd) != 0) {
            exit(EXIT_FAILURE);
        }

        // Exécute la commande
        execvp(cmd->name, cmd->args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    // Le processus père continue ici
    return pid;  // Retourne le PID pour le wait
}

int wait_for_children(void) {
    int status;
    pid_t pid;
    int last_status = 0;

    // Attend tous les processus fils
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            last_status = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            last_status = 128 + WTERMSIG(status);
        }
    }

    return last_status;
}

int handle_redirections(t_command *cmd) {
    if (cmd->input_file) {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd == -1) {
            perror("open");
            return -1;
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (cmd->output_file) {
        int flags = O_WRONLY | O_CREAT;
        flags |= cmd->append_output ? O_APPEND : O_TRUNC;
        int fd = open(cmd->output_file, flags, 0644);
        if (fd == -1) {
            perror("open");
            return -1;
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    return 0;
}