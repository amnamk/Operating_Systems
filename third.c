#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

void check_memory_usage() {
    char command[256];
    sprintf(command, "ps -p %d -o vsz,rss", getpid());
    system(command); // Executes the ps command to show VSZ and RSS
}

int main() {
    printf("Program started.\n");
    printf("Initial memory usage:\n");
    check_memory_usage();
    getchar(); 


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
    getchar(); // Wait for user input

    // map an anonymous page
    void *mmap_ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mmap_ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Anonymous page memory-mapped. Current memory usage:\n");
    check_memory_usage();
    getchar(); // Wait for user input

  
    *(int *)mmap_ptr = 123; // Writing an integer to the start of the mapped page

    printf("Data written to memory-mapped page. Current memory usage:\n");
    check_memory_usage();
    getchar();

   
    free(array);
    printf("Dynamically allocated memory freed. Current memory usage:\n");
    check_memory_usage();
    getchar(); // Wait for user input

    // Unmap the memory-mapped page
    if (munmap(mmap_ptr, 4096) != 0) {
        perror("munmap failed");
        return 1;
    }

    printf("Memory unmapped. Final memory usage:\n");
    check_memory_usage();
    getchar(); // Wait for user input

    return 0;
}
