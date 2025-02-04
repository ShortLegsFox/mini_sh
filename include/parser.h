#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"
#include "typedef.h"

int is_special(char c);
int is_whitespace(char c);
t_token *create_token(token_type type, char *value);
t_token *get_next_token(t_lexer *lexer);

t_command *parse_command_line(char *line);
void free_command(t_command *cmd);

#endif