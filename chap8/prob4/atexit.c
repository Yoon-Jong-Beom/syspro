#include <stdio.h>
#include <stdlib.h>

static void exit_handler1(void),
exit_handler2(void);

int main(void)
{
    if (atexit(exit_handler1) != 0)	
        perror("Cannot register exit_handler1");
    if (atexit(exit_handler2) != 0) 	
        perror("Cannot register exit_handler2");
    printf("main done\n");
    exit(0);
}

static void exit_handler1(void)
{
    printf("First exit handler\n");
}

static void exit_handler2(void)
{
    printf("Second exit handler\n");
}
