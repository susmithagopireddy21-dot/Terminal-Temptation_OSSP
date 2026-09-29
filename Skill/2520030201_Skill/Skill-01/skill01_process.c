#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child;

    printf("Skill-01: Process Abstraction Demo\n");
    printf("Parent Process ID: %d\n", getpid());

    child = fork();

    if (child < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (child == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("Child is executing 'ls' using execvp()...\n");

        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);

        perror("execvp failed");
        exit(1);
    }
    else
    {
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Created Child PID: %d\n", child);

        waitpid(child, NULL, 0);

        printf("\nChild process completed.\n");
        printf("Parent process completed.\n");
    }

    return 0;
}
