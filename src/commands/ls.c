/**
* \file ls.c
 * \ls command for mini_sh.
 * \author SLF
 * \version 0.1
 * \date 05/01/2025
 *
 * list directories and file from current position.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include "commands.h"
#include "minishell.h"

void ls_function(int argc, char** argv) {
    /**
    * Input path for ls command
    * set to NULL by default
    */
    char* input_path = NULL;

    // If called without arguments
    if (argc == 1) {
        input_path = ".";
    }
    // If called with one argument (path)
    else if (argc == 2) {
        input_path = argv[1];
    }
    // If called wrong with to many arguments
    else {
        dprintf(STDERR, "Bad usage! To many arguments !\n");
        exit(EXIT_FAILURE);
    }

    DIR *dir = opendir(input_path);
    if (dir == NULL) {
        perror("opendir");
    }

    struct dirent *read_dir = readdir(dir);
    struct stat file_stat;

    while (read_dir != NULL) {

        // Print permissions
        stat(read_dir->d_name, &file_stat);

        dprintf(STDOUT, "%s", (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IRUSR) ? "r" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IWUSR) ? "w" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IXUSR) ? "x" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IRGRP) ? "r" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IWGRP) ? "w" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IXGRP) ? "x" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IROTH) ? "r" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IWOTH) ? "w" : "-");
        dprintf(STDOUT, "%s", (file_stat.st_mode & S_IXOTH) ? "x" : "-");

        dprintf(STDOUT, "%s", "  ");

        // Print owner
        struct passwd *pw = getpwuid(file_stat.st_uid);
        struct group  *gr = getgrgid(file_stat.st_gid);

        dprintf(STDOUT, "%s", pw->pw_name);
        dprintf(STDOUT, "%s", ":");
        dprintf(STDOUT, "%s", gr->gr_name);

        dprintf(STDOUT, "%s", "  ");

        // Print size
        dprintf(STDOUT, "%ld", file_stat.st_size);

        dprintf(STDOUT, "%s", "  ");

        // Print last modifier date
        time_t t = file_stat.st_ctime;
        struct tm * last_modified_date = localtime(&t);
        char date_buffer[100];
        strftime(date_buffer, sizeof(date_buffer), "%a %b %d %H:%M:%S %Y", last_modified_date);
        dprintf(STDOUT, "%s", date_buffer);

        dprintf(STDOUT, "%s", "  ");

        // Print names
        dprintf(STDOUT, "%s\n", read_dir->d_name);

        read_dir = readdir(dir);
    }

    closedir(dir);
}