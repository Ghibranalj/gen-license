#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function to execute a command and capture its output
static char *execute_command(const char *command) {
    char buffer[256];
    char *result = NULL;

    // Open the command for reading
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("Error opening command");
        return NULL;
    }

    // Read the output into the buffer
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // Remove newline characters if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Allocate memory for the result and copy the username
        result = strdup(buffer);
    }

    // Close the file pointer
    int exit = pclose(fp);
    if (exit != 0){
        free(result);
        return NULL;
    }

    return result;
}

char* git_username(){
    return execute_command("git config user.name 2>/dev/null");
}

char* git_root_dir(){
    return execute_command("git rev-parse --show-toplevel 2>/dev/null");
}
