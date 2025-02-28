/**
* \file parser.c
 * \parser file for mini_sh.
 * \author Ian B., Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Parse command input for mini shell project.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "utils.h"
#include "alias.h"

/**
 * Command initializer
 *
 * \return an "empty" command, ready to be completed after the parsing process
 */
static t_command *create_command() {
    t_command *cmd = malloc(sizeof(t_command));
    cmd->name = NULL;
    cmd->args = malloc(sizeof(char*) * MAX_ARGS);
    cmd->args[0] = NULL;
    cmd->input_file = NULL;
    cmd->output_file = NULL;
    cmd->append_output = 0;
    cmd->pipe_next = NULL;
    cmd->next_operator = NULL;
    return cmd;
}

/**
 * Command parser function
 *
 * \return the command fully completed after all parsing operations
 */
t_command *parse_command_line(char *line) {
    save_to_history(line);
    char*alias_cmd = get_alias(line);
    t_lexer lexer = {alias_cmd, 0, strlen(alias_cmd)};
    t_command *cmd = create_command();
    t_command *current_cmd = cmd;
    int arg_index = 0;

    t_token *token;
    while ((token = get_next_token(&lexer))->type != TOKEN_EOF) {
        switch (token->type) {
            case TOKEN_WORD: {
                if (!current_cmd->name) {
                    current_cmd->name = strdup(token->value);
                    current_cmd->args[0] = strdup(token->value);
                    arg_index = 1;
                } else {
                    current_cmd->args[arg_index++] = strdup(token->value);
                    current_cmd->args[arg_index] = NULL;
                }
                break;
            }
            case TOKEN_PIPE:
                current_cmd->args[arg_index] = NULL;
                current_cmd->pipe_next = create_command();
                current_cmd = current_cmd->pipe_next;
                arg_index = 0;
                break;

            case TOKEN_REDIRECT_IN:
                free(current_cmd->input_file);
                token = get_next_token(&lexer);
                if (token->type == TOKEN_WORD) {
                    current_cmd->input_file = strdup(token->value);
                }
                break;

            case TOKEN_REDIRECT_OUT:
            case TOKEN_APPEND:
                free(current_cmd->output_file);
                current_cmd->append_output = (token->type == TOKEN_APPEND);
                token = get_next_token(&lexer);
                if (token->type == TOKEN_WORD) {
                    current_cmd->output_file = strdup(token->value);
                }
                break;

            case TOKEN_AND:
            case TOKEN_OR:
                current_cmd->next_operator = malloc(sizeof(t_token));  // Allouer une nouvelle mémoire
                    if (!current_cmd->next_operator) {
                        perror("malloc failed");
                        exit(EXIT_FAILURE);
                    }
                    current_cmd->next_operator->type = token->type;  // Copier seulement le type
                    current_cmd->pipe_next = create_command();
                    current_cmd = current_cmd->pipe_next;
                    arg_index = 0;
            break;


            default:
                break;
        }
        free(token->value);
        free(token);
    }

    free(token);
    return cmd;
}

void free_command(t_command *cmd) {
    if (!cmd) return;

    free(cmd->name);

    for (int i = 0; cmd->args[i] != NULL; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);

    free(cmd->input_file);
    free(cmd->output_file);

    if (cmd->pipe_next) {
        free_command(cmd->pipe_next);
    }

    free(cmd);
}