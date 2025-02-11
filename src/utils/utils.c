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