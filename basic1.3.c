#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid < 0) {  // Error occurred
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {  // Child process
        // Execute 'ls' command
        execlp("/bin/ls", "ls", NULL);
        
        // If execlp fails, print an error
        perror("exec");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        // Wait for the child process to finish
        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}
