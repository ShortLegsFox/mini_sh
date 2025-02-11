#ifndef MINI_SH_UTILS_H
#define MINI_SH_UTILS_H
#include <stdio.h>
#include <stdlib.h>

void save_to_history(char *command);
char *strip_outer_quotes_and_backslashes(const char *str);

#endif //MINI_SH_UTILS_H
