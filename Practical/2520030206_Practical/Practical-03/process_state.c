#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    int status;

    printf("Parent Process Started\n");
    printf("Parent PID: %d\n", getpid());
    printf("Parent State: Running\n\n");

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
        printf("Child PPID: %d\n", getppid());
        printf("Child State: Running\n");

        printf("Child State: Waiting/Sleeping\n");
        sleep(300);

        printf("Child State: Running Again\n");

        printf("Child Process Terminating\n");
        exit(0);
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        printf("Parent State: Waiting for Child\n");

        wait(&status);

        if (WIFEXITED(status))
        {
            printf("\nChild has Terminated\n");
            printf("Parent State: Running Again\n");
        }
    }

    printf("Parent Process Terminating\n");

    return 0;
}
