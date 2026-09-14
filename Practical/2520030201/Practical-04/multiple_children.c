#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child1, child2;
    int status;

    printf("Parent Process PID: %d\n", getpid());

    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1 PID: %d\n", getpid());
        sleep(2);
        printf("Child 1 completed\n");
        return 10;
    }

    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2 PID: %d\n", getpid());
        sleep(3);
        printf("Child 2 completed\n");
        return 20;
    }

    printf("\nParent using waitpid() for Child 2\n");

    waitpid(child2, &status, 0);

    printf("Child 2 completed using waitpid()\n");

    printf("\nParent using wait() for remaining child\n");

    wait(&status);

    printf("Remaining child completed using wait()\n");

    printf("Parent process completed\n");

    return 0;
}
