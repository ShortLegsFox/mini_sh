#ifndef PARSER_H
#define PARSER_H

#include "minishell.h"

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_EOF
} token_type;

typedef struct s_token {
    token_type type;
    char *value;
} t_token;

typedef struct s_lexer {
    char *input;
    int pos;
    int length;
} t_lexer;

int is_special(char c);
int is_whitespace(char c);
t_token *create_token(token_type type, char *value);
t_token *get_next_token(t_lexer *lexer);

t_command *parse_command_line(char *line);
void free_command(t_command *cmd);

#endif