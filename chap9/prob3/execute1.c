#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Create a child process and execute the echo command. */
int main() {
    printf("Parent process started\n");
    if (fork() == 0) {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "First exec failed");
        exit(1);
    }
    printf("Parent process ended\n");
}

