#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_builtin(char *token) {
    printf("Checking against builtin commands\n");
    const char *builtin = "exit";
    if (strncmp(token, builtin, 4) == 0) {
        printf("Goodbye.\n");
        exit(0);
    }
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
            if (token_counter == 1) check_builtin(token);
            printf("Token: %s\n", token);
            token = strtok(NULL, &delim);
        }
    }
    return 0;
}
