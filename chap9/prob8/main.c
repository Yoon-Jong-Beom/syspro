#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 100
#define MAX_INPUT_LENGTH 1024

void execute_command(char *args[]) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        printf("[Child] PID = %d started\n", getpid());
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        printf("[Parent] Child PID = %d\n", pid);
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    char *token;
    int arg_count;

    while (1) {
        printf("[Shell] ");
        fgets(input, MAX_INPUT_LENGTH, stdin);

        // Remove trailing newline
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // Parse input into arguments
        arg_count = 0;
        token = strtok(input, " \t\n");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " \t\n");
        }
        args[arg_count] = NULL;

        // Check for background execution
        if (arg_count > 0 && strcmp(args[arg_count - 1], "&") == 0) {
            args[arg_count - 1] = NULL; // Remove the "&" from arguments
            execute_command(args);
        } else if (arg_count > 0) {
            execute_command(args);
        }
    }

    return 0;
}
