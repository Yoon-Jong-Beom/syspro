#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() 
{
   int pid, child, status;
   printf("[%d] Parent process started \n", getpid( ));
   pid = fork();
   if (pid == 0) {
      printf("[%d] Child process started \n", getpid( ));
      exit(1);
   }
   child = wait(&status); // Wait for the child process to finish.
   printf("[%d] Child process %d terminated \n", getpid(), child);
   printf("\tExit code %d\n", status >> 8);
}
