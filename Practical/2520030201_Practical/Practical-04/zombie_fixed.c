#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("Child process PID: %d\n", getpid());
        printf("Child process exiting...\n");
        return 0;
    }
    else
    {
        printf("Parent process PID: %d\n", getpid());
        printf("Child process PID: %d\n", pid);

        waitpid(pid, &status, 0);

        printf("Child process reaped using waitpid()\n");
        printf("Zombie process eliminated.\n");
    }

    return 0;
}
