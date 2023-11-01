#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static char *git_command(const char *command) {
    char buffer[256];
    char *result = NULL;

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error opening command");
        return NULL;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }

    int exit = pclose(fp);
    if (exit != 0){
        return NULL;
    }

    return strdup(buffer);
}

char* git_username(){
    return git_command("git config user.name 2>/dev/null");
}

char* git_root_dir(){
    return git_command("git rev-parse --show-toplevel 2>/dev/null");
}
