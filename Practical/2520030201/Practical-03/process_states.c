#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent process started\n");
    printf("Parent PID: %d\n", getpid());
    printf("Parent PPID: %d\n", getppid());

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\nChild process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());

        sleep(20);

        printf("Child process completed\n");
    }
    else
    {
        printf("\nParent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(NULL);

        printf("Parent process completed\n");
    }

    return 0;
}
