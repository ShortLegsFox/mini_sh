/**
* \file executor.c
 * \executor file for mini_sh.
 * \author Ian B., Léo H.
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
    {"echo", &builtin_echo},
    {"exit", &builtin_exit},
    {"pwd", &builtin_pwd},
    {NULL, NULL}
};

/**
 * Find command type (based on command name)
 *
 * \return CMD_BUILTIN if in builtins list, otherwise return CMD_EXTERNAL
 */
cmd_type get_command_type(const char *cmd_name) {
    for (int i = 0; t_builtins[i].name != NULL; i++) {
        if (strcmp(cmd_name, t_builtins[i].name) == 0) {
            return CMD_BUILTIN;
        }
    }
    return CMD_EXTERNAL;
}

void execute_pipeline(t_command *cmd) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (!cmd || !cmd->pipe_next) {
        return;
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    // Premier processus (commande de gauche)
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return;
    }
    if (pid1 == 0) {
        dup2(pipefd[1], STDOUT_FILENO); // Redirige stdout vers le pipe
        close(pipefd[0]); // Ferme l'entrée du pipe
        close(pipefd[1]); // Ferme la sortie du pipe après redirection

        if (get_command_type(cmd->name) == CMD_BUILTIN) {
            for (int i = 0; t_builtins[i].name != NULL; i++) {
                if (strcmp(cmd->name, t_builtins[i].name) == 0) {
                    exit(t_builtins[i].func(cmd->args));
                }
            }
        } else {
            execvp(cmd->name, cmd->args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Deuxième processus (commande de droite)
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        return;
    }
    if (pid2 == 0) {
        dup2(pipefd[0], STDIN_FILENO); // Redirige stdin depuis le pipe
        close(pipefd[0]); // Ferme l'entrée après redirection
        close(pipefd[1]); // Ferme la sortie du pipe

        execute_command(cmd->pipe_next); // Exécute la commande suivante
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]); // Ferme le pipe dans le parent
    close(pipefd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}


/**
 * Command executor
 *
 * \return pid of the command once executed, -1 if failed
 */
int execute_command(t_command *cmd) {
    if (!cmd || !cmd->name) return -1;

    if (cmd->pipe_next) {
        execute_pipeline(cmd);
        return 0;
    }

    if (handle_redirections(cmd) != 0) {
        return -1;
    }

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

    if (pid == 0) {  // -- Processus fils
        execvp(cmd->name, cmd->args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    int status;
    waitpid(pid, &status, 0);

    if (cmd->next_operator) {
        if ((cmd->next_operator->type == TOKEN_AND && WIFEXITED(status) && WEXITSTATUS(status) == 0) ||
            (cmd->next_operator->type == TOKEN_OR && (!WIFEXITED(status) || WEXITSTATUS(status) != 0))) {
            return execute_command(cmd->pipe_next);
            }
    }

    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
}


int wait_for_children(void) {
    int status;
    pid_t pid;
    int last_status = 0;

    // -- Attend tous les processus fils
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
