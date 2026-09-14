#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
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

        printf("Parent sleeping for 20 seconds...\n");
        printf("Check the child process using ps during this time.\n");

        sleep(20);

        printf("Parent now calling wait()...\n");
        wait(NULL);

        printf("Zombie process eliminated.\n");
    }

    return 0;
}
