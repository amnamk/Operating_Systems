#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h> // for file operations

#define MAX_LINE 256
#define MAX_HISTORY 10

char history[MAX_HISTORY][MAX_LINE];
int history_index = 0;

// ANSI color codes
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

void display_prompt() {
    printf(BLUE "MyShell> " RESET);
    fflush(stdout); // Flush output to ensure prompt is displayed immediately
}

void cp(char *src, char *dest) {
    FILE *fp_src, *fp_dest;
    char ch;

    if ((fp_src = fopen(src, "rb")) == NULL) {
        perror("cp: source file error");
        return;
    }

    if ((fp_dest = fopen(dest, "wb")) == NULL) {
        perror("cp: destination file error");
        fclose(fp_src);
        return;
    }

    while ((ch = fgetc(fp_src)) != EOF) {
        fputc(ch, fp_dest);
    }

    fclose(fp_src);
    fclose(fp_dest);
    printf("cp: '%s' copied to '%s'\n", src, dest);
}

void history_cmd() {
    if (history_index == 0) {
        printf(CYAN "history: no commands in history\n" RESET);
        return;
    }

    printf(GREEN "History:\n" RESET);
    for (int i = 0; i < history_index; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}

void free_cmd() {
    // Simulate the free command by using system calls (consider platform-specific tools)
    system("free | grep Mem");  // Output limited to memory information
}


void wc(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror(RED "Error opening file");
        exit(EXIT_FAILURE);
    }

    int lines = 0, words = 0, characters = 0;
    int in_word = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        characters++;

        if (c == '\n') {
            lines++;
        }

        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f') {
            in_word = 0;
        } else if (!in_word) {
            words++;
            in_word = 1;
        }
    }

    // Check if the last word is counted
    if (in_word) {
        words++;
    }

    fclose(file);

    printf("%d %d %d %s\n", lines, words, characters, filename);
}

void fortune_cmd() {
    FILE *fp = popen("fortune", "r");
    if (fp == NULL) {
        perror("fortune");
        return;
    }

    char buffer[MAX_LINE];
    printf(YELLOW "Fortune:\n" RESET);
    while (fgets(buffer, MAX_LINE, fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

void sl() {
    printf(MAGENTA "Displaying steam locomotive animation...\n");
    system("sl");
}

int main() {
    char buffer[MAX_LINE];

    while (1) {
        display_prompt();
        fgets(buffer, MAX_LINE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline

        // Update history
        if (strlen(buffer) > 0) {
            strncpy(history[history_index], buffer, MAX_LINE - 1);
            history[history_index][MAX_LINE - 1] = '\0';
            history_index = (history_index + 1) % MAX_HISTORY;  // Circular buffer
        }

        // Handle commands with output redirection
        char *token = strtok(buffer, " ");
        if (token != NULL) {
            if (strcmp(token, "cp") == 0) {
                char *src = strtok(NULL, " ");
                char *dest = strtok(NULL, " ");
                if (src != NULL && dest != NULL) {
                    cp(src, dest);
                } else {
                    printf(RED "Error: Usage - cp <source> <destination>\n" RESET);
                }
            } else if (strcmp(token, "history") == 0) {
                history_cmd();
            } else if (strcmp(token, "exit") == 0) {
                break;
            }else if (strcmp(token, "free") == 0) {
                free_cmd();
            } else if (strcmp(token, "fortune") == 0) {
                fortune_cmd();
             }else if (strcmp(token, "wc") == 0) {
        token = strtok(NULL, " "); // Move to the next token which should be the filename
        if (token != NULL) {
            wc(token); // Call the wc function with the filename
        } else {
            printf(RED "Error: Usage - wc <filename>\n" RESET);
        } } else if (strcmp(token, "sl") == 0) {
                sl();
            } else {
             // Handle unrecognized commands and output redirection
char *output_file = strtok(NULL, " ");
if (output_file != NULL && strcmp(output_file, ">") == 0) {
    output_file = strtok(NULL, " ");
    if (output_file != NULL) {
        // Redirect output to the specified file
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open");
        } else {
            dup2(fd, STDOUT_FILENO); // Redirect stdout to the file
            close(fd);
            system(buffer); // Execute the command
            dup2(STDOUT_FILENO, STDOUT_FILENO); // Restore stdout
        }
    } else {
        printf(RED "Error: Missing output file\n" RESET);
    }
} else {
    // Regular command execution
    //system(buffer);
     printf(RED "Error: Command not found\n" RESET);
        
}
            }
        }
    }

    return 0;
}
