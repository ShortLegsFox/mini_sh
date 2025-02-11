/**
* \file utils.c
 * \utils file for mini_sh.
 * \author Ian B., Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * Some functions usefull for mini shell project.
 */

#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#define HISTORY_FILE "/tmp/mini_shell_history.txt"

/**
 * Save last command to history
 * @param command
 */
void save_to_history(char* command) {

    FILE* file = fopen(HISTORY_FILE, "a");
    if (file) {
        fprintf(file, "%s\n", command);
        fclose(file);
    }
}

/**
 * Retire les quote au debut et a la fin
 * @param str
 * @return
 */
char *strip_outer_quotes_and_backslashes(const char *str)
{
    size_t len = strlen(str);
    if (len == 0) {
        return strdup("");
    }

    char first = str[0];
    char last  = str[len - 1];

    int has_outer_quotes = 0;
    if ((first == '\'' || first == '"') && (first == last)) {
        has_outer_quotes = 1;
    }

    char *cleaned = malloc(len + 1);
    if (!cleaned) {
        perror("malloc failed");
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {

        if (has_outer_quotes && (i == 0 || i == len - 1)) {
            continue;
        }
        if (str[i] == '\\') {
            continue;
        }

        cleaned[j++] = str[i];
    }
    cleaned[j] = '\0';

    return cleaned;
}

