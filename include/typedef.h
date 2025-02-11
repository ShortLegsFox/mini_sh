#ifndef TYPEDEF_H
#define TYPEDEF_H

#define STDOUT 1
#define STDERR 2
#define MAX_LENGTH 4096
#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 128

typedef struct s_command {
    char *name;          // Command name
    char **args;         // Command arguments
    char *input_file;    // Input redirection
    char *output_file;   // Output redirection
    int append_output;   // Flag for append mode
    struct s_command *pipe_next;  // Next command in pipeline
    struct s_token *next_operator; // Next operator in command chain
} t_command;

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_APPEND,
    TOKEN_OR,
    TOKEN_AND,
    TOKEN_BACKGROUND,
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


typedef struct s_alias {
    char *name;
    char *command;
    struct s_alias *next;
} t_alias;

#endif
