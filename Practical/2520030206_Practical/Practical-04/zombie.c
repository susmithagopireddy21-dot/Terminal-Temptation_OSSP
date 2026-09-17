#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    printf("Parent Process Started\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process Created\n");
        printf("Child PID: %d\n", getpid());
        printf("Child is terminating...\n");
        exit(0);
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        printf("Parent is waiting for the child...\n");

        wait(NULL);

        printf("Child process has been reaped.\n");
        printf("No zombie process remains.\n");
        printf("Parent Process Terminating\n");
    }

    return 0;
}
