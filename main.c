#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int check_builtin(char *token) {
    printf("Checking against builtin commands\n");
    const char *builtin = "exit";
    if (strncmp(token, builtin, 4) == 0) {
        printf("Goodbye.\n");
        exit(0);
    }
    return 0;
}

char *check_command_path(char *token) {
    printf("testing can execute file\n");
    char *command_path = malloc((strlen(token) + 5) * sizeof(char));
    strcpy(command_path, "/bin/");
    strcpy(command_path+5, token);
    command_path[strlen(token) + 4] = '\0'; 
    printf("Path: %s\n", command_path);
    if (access(command_path, F_OK) == 0) return command_path;
    printf("Couldn't get file access... Errno: %i\n", errno);
    free(command_path);
    return NULL;
}

int main() {
    printf("Welcome to dosh, the Dominic shell\n");
    while (1 == 1){
        printf("dosh> ");
        char *command = malloc(3 * sizeof(char));
        *command = NULL;
        size_t n = 3;
        ssize_t n2 = getline(&command, &n, stdin);
        printf("You typed: %s\n", command);
        printf("The line has length: %zu\n", n2);
        printf("The buffer has size: %zu\n", n);
        const char delim = ' ';
        char *token = strtok(command, &delim);
        int token_counter = 0;
        while (token != NULL){
            token_counter++;
            int is_builtin = 0;
            if (token_counter == 1) {
                is_builtin = check_builtin(token);
                if (is_builtin == 0) {
                    char *command = check_command_path(token);
                    if (command == NULL) {
                        char error_message[30] = "An error has occurred\n";
                        write(STDERR_FILENO, error_message, strlen(error_message));
                    }
                }
            }
            printf("Token: %s\n", token);
            token = strtok(NULL, &delim);
        }
    }
    return 0;
}
