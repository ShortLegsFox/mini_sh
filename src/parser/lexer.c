/**
* \file lexer.c
 * \lexer file for mini_sh.
 * \author Ian B., Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Lexer for command input parsing for mini shell project.
 */
#include "parser.h"

int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int is_special(char c) {
    return c == '|' || c == '<' || c == '>';
}

t_token *create_token(token_type type, char *value) {
    t_token *token = malloc(sizeof(t_token));
    token->type = type;
    token->value = value;
    return token;
}

t_token *get_next_token(t_lexer *lexer) {
    // -- Skip whitespaces
    while (lexer->pos < lexer->length && is_whitespace(lexer->input[lexer->pos])) {
        lexer->pos++;
    }

    // -- End of file token if position >= lenght
    if (lexer->pos >= lexer->length) {
        return create_token(TOKEN_EOF, NULL);
    }

    char current = lexer->input[lexer->pos];

    if (current == '|') {
        lexer->pos++;
        if (lexer->pos < lexer->length && lexer->input[lexer->pos] == '|') {
            lexer->pos++;
            return create_token(TOKEN_OR, strdup("||"));
        }
        return create_token(TOKEN_PIPE, strdup("|"));
    }

    if (current == '&') {
        lexer->pos++;
        if (lexer->pos < lexer->length && lexer->input[lexer->pos] == '&') {
            lexer->pos++;
            return create_token(TOKEN_AND, strdup("&&"));
        }
        return create_token(TOKEN_BACKGROUND, strdup("&"));
    }

    if (current == '<') {
        lexer->pos++;
        return create_token(TOKEN_REDIRECT_IN, strdup("<"));
    }

    if (current == '>') {
        lexer->pos++;
        if (lexer->pos < lexer->length && lexer->input[lexer->pos] == '>') {
            lexer->pos++;
            return create_token(TOKEN_APPEND, strdup(">>"));
        }
        return create_token(TOKEN_REDIRECT_OUT, strdup(">"));
    }

    // -- Handle word tokens
    int start = lexer->pos;
    int in_quotes = 0;
    char quote_char = 0;

    while (lexer->pos < lexer->length) {
        current = lexer->input[lexer->pos];

        if (current == '"' || current == '\'') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_char = current;
            } else if (current == quote_char) {
                in_quotes = 0;
            }
        }

        if (!in_quotes && (is_whitespace(current) || is_special(current))) {
            break;
        }

        lexer->pos++;
    }

    int length = lexer->pos - start;
    char *value = malloc(length + 1);
    strncpy(value, &lexer->input[start], length);
    value[length] = '\0';

    return create_token(TOKEN_WORD, value);
}
