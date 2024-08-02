#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxInput 1024

int main() {
    char input[MaxInput];

    while (1) {
        printf("prompt$ ");
       
        if (!fgets(input, MaxInput, stdin)) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

       
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) {
            break;
        }

        system(input);
    }

    return 0;
}
