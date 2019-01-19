#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello, World!\n");
    while (1 == 1){
        printf("wish> ");
        char *command = malloc(3 * sizeof(char));
        *command = NULL;
        size_t n = 3;
        ssize_t n2 = getline(&command, &n, stdin);
        printf("You typed: %s\n", command);
        printf("The line has length: %zu\n", n2);
        printf("The buffer has size: %zu\n", n);
    }
    return 0;
}
