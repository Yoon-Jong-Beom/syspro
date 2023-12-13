#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void intHandler();

int main() {
    signal(SIGINT, intHandler);

    while (1)
		pause();

    printf("end\n");
    return 0;
}

void intHandler(int signo) {
    printf("Interrupt signal\n");
    printf("Signal number: %d\n", signo);
    exit(0);
}

