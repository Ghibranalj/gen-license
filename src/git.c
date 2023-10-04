#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

// Function to execute a command and capture its output
static char *execute_command(const char *command) {
    char buffer[MAX_USERNAME_LENGTH];
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
    pclose(fp);

    return result;
}

char* git_username(){
    return execute_command("git config user.name 2>/dev/null");
}
