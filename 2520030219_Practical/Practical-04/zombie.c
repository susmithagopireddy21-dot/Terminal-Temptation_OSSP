#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child is terminating\n");
        return 0;
    }
    else
    {
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is waiting for child\n");

        wait(NULL);
        printf("Child process collected\n");
        printf("Parent is terminating\n");
    }

    return 0;
}
