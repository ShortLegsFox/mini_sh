/**
* \file alias.c
 * \alias alias functions file for mini_sh.
 * \author Ian B., Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 *  alias functions.
 */
#include "builtins.h"
#include "alias.h"
#include "typedef.h"
#include <stdio.h>
#include "string.h"



/**
 * Alias builtin function for mini_sh
 * @param args
 * @return
 */
int builtin_alias(char **args){
    if (!args[1]) {
        for (t_alias *a = alias_list; a != NULL; a = a->next) {
            printf("%s='%s'\n", a->name, a->command);
        }
        return 0;
    }
    for (int i = 1; args[i] != NULL; i++) {
        char *arg = args[i];

        char *equal_sign = strchr(arg, '=');
        if (!equal_sign) {
            const char *alias_value = get_alias(arg);
            if (alias_value) {
                printf("%s='%s'\n", arg, alias_value);
            } else {
                fprintf(stderr, "alias: %s: not found\n", arg);
            }
        } else {
            *equal_sign = '\0';
            char *name = arg;
            char *value = equal_sign + 1;

            remove_alias(name);
            add_alias(name, value);
        }
    }
    return 0;
}