#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_memory_usage() {
    char command[256];
    // sprintf to safely format the command 
    sprintf(command, "ps -p %d -o vsz,rss", getpid());
    system(command); //show VSZ and RSS
}

int main() {
    printf("Program started.\n");
    printf("Initial memory usage:\n");
    check_memory_usage();
    getchar(); // Wait for user input

    // Allocate some memory
    int *array = malloc(1000000 * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Simulate usage
    for (int i = 0; i < 1000000; i++) {
        array[i] = i;
    }

    printf("Memory allocated and used. Current memory usage:\n");
    check_memory_usage();
    getchar(); 

    
    free(array);
    printf("Memory freed. Current memory usage:\n");
    check_memory_usage();
    getchar(); 

    return 0;
}
