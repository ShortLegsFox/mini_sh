#ifndef TYPEDEF_H
#define TYPEDEF_H

typedef struct s_command {
    char *name;          // Command name
    char **args;         // Command arguments
    char *input_file;    // Input redirection
    char *output_file;   // Output redirection
    int append_output;   // Flag for append mode
    struct s_command *pipe_next;  // Next command in pipeline
} t_command;

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

#endif
