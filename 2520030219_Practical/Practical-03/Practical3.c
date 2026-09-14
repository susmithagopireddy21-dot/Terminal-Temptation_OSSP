#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent process started\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());

        printf("Child is Running\n");

        sleep(60);

        printf("Child is Terminating\n");
    }
    else
    {
        printf("\nParent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is Running\n");

        sleep(30);

        printf("Parent is Waiting for child\n");

        wait(NULL);

        printf("Child has Terminated\n");
    }

    return 0;
}
