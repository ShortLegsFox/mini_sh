/**
* \file alias.c
 * \alias builtin file for mini_sh.
 * \author Ian B., Léo H.
 * \version 0.1
 * \date 05/01/2025
 *
 * builtin for alias command.
 */
#include <stdio.h>
#include <stdlib.h>
#include "typedef.h"
#include <string.h>
#include "utils.h"

t_alias *alias_list = NULL;

/**
 * Add the alias to the list
 * @param name
 * @param command
 */
void add_alias(const char *name, const char *command)
{
    t_alias *new_alias = malloc(sizeof(t_alias));
    if (!new_alias) {
        perror("malloc");
        return;
    }
    new_alias->name = strdup(name);
    new_alias->command = strdup(command);
    new_alias->next = alias_list;
    alias_list = new_alias;
}


/**
 * Return original command with alias (if exists)
 * @param name
 * @return
 */
char *get_alias(char *name)
{
    for (t_alias *current = alias_list; current != NULL; current = current->next)
    {
        if (strcmp(current->name, name) == 0){
            char *defaultCmd = strdup(strip_outer_quotes_and_backslashes(current->command));
            return defaultCmd;
        }
    }
    return name;
}


/**
 * Remove alias from list
 * @param name
 * @return
 */
int remove_alias(const char *name)
{
    t_alias *current = alias_list;
    t_alias *previous = NULL;

    while (current)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (previous == NULL)
                alias_list = current->next;
            else
                previous->next = current->next;

            free(current->name);
            free(current->command);
            free(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1; // alias non trouvé
}


/**
 * Free alias list
 */
void free_alias_list(void)
{
    t_alias *current = alias_list;
    while (current)
    {
        t_alias *temp = current;
        current = current->next;
        free(temp->name);
        free(temp->command);
        free(temp);
    }
    alias_list = NULL;
}