#ifndef BUILTINS_H
#define BUILTINS_H

int builtin_cd(char **args);
int builtin_pwd(char **args);
int builtin_exit(char **args);
int builtin_echo(char **args);
int builtin_export(char **args);
int builtin_unset(char **args);

#endif