#ifndef MINI_SH_ALIAS_H
#define MINI_SH_ALIAS_H
#include "typedef.h"

extern t_alias *alias_list;
void add_alias(const char *name, const char *command);
char *get_alias(char *name);
int remove_alias(const char *name);
void free_alias_list(void);

#endif //MINI_SH_ALIAS_H
