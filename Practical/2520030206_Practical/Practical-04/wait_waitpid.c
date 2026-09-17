#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t child1, child2, child3;
    int status;

    printf("Parent Process Started\n");
    printf("Parent PID: %d\n\n", getpid());

    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        printf("Child 1: Terminating\n");
        exit(10);
    }

    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(4);
        printf("Child 2: Terminating\n");
        exit(20);
    }

    child3 = fork();

    if (child3 == 0)
    {
        printf("Child 3: PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(3);
        printf("Child 3: Terminating\n");
        exit(30);
    }

    printf("\nParent is using wait()...\n");

    if (wait(&status) > 0)
    {
        printf("wait(): A child process has completed.\n");
        if (WIFEXITED(status))
            printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    printf("\nParent is using waitpid() for Child 2...\n");

    if (waitpid(child2, &status, 0) > 0)
    {
        printf("waitpid(): Child 2 has completed.\n");
        if (WIFEXITED(status))
            printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    if (waitpid(child3, &status, 0) > 0)
    {
        printf("waitpid(): Child 3 has completed.\n");
        if (WIFEXITED(status))
            printf("Exit status: %d\n", WEXITSTATUS(status));
    }

    printf("\nAll child processes have completed.\n");
    printf("Parent Process Terminating\n");

    return 0;
}
