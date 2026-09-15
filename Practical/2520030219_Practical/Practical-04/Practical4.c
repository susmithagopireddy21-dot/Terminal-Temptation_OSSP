#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child1, child2;
    int status;

    printf("Parent process started\n");
    printf("Parent PID: %d\n\n", getpid());

    child1 = fork();

    if (child1 < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (child1 == 0)
    {
        printf("Child 1 started\n");
        printf("Child 1 PID: %d\n", getpid());

        sleep(3);

        printf("Child 1 completed\n");
        return 10;
    }

    child2 = fork();

    if (child2 < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (child2 == 0)
    {
        printf("\nChild 2 started\n");
        printf("Child 2 PID: %d\n", getpid());

        sleep(6);

        printf("Child 2 completed\n");
        return 20;
    }

    printf("\nParent waiting using wait()\n");

    wait(&status);

    printf("wait() collected a child process\n");
    printf("Child exit status: %d\n", WEXITSTATUS(status));

    printf("\nParent waiting for Child 2 using waitpid()\n");

    waitpid(child2, &status, 0);

    printf("waitpid() collected Child 2\n");
    printf("Child 2 exit status: %d\n", WEXITSTATUS(status));

    printf("\nAll child processes completed\n");

    return 0;
}
