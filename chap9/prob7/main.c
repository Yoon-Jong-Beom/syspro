#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 100

void execute_command(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shell");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void parse_and_execute(char *command) {
    char *args[MAX_ARGUMENTS];
    char *token;
    int arg_count = 0;

    token = strtok(command, " \t\n");
    while (token != NULL) {
        args[arg_count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[arg_count] = NULL;

    if (arg_count > 0) {
        if (strcmp(args[arg_count - 1], "&") == 0) {
            args[arg_count - 1] = NULL;
            execute_command(args);
        } else {
            execute_command(args);
        }
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("[shell] ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            break;
        }

        parse_and_execute(command);
    }

    return 0;
}
