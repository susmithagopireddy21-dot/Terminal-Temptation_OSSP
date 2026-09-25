#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int *data;
    pid_t pid;

    data = (int *)malloc(sizeof(int));

    if (data == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    *data = 100;

    printf("Before fork():\n");
    printf("Parent process PID: %d\n", getpid());
    printf("Memory address: %p\n", (void *)data);
    printf("Value: %d\n\n", *data);

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        printf("Child process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Memory address before modification: %p\n", (void *)data);
        printf("Value before modification: %d\n", *data);

        *data = 200;

        printf("Memory address after modification: %p\n", (void *)data);
        printf("Value after modification: %d\n", *data);

        printf("Child modified its copy of the data.\n");
        printf("Child is waiting. PID: %d\n", getpid());
        printf("Press Enter in the child terminal to continue...\n");
        getchar();
        free(data);
        exit(0);
    }
    else
    {
        wait(NULL);

        printf("\nParent process after child modification:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Memory address: %p\n", (void *)data);
        printf("Parent value: %d\n", *data);
        printf("Parent value remains unchanged because of Copy-on-Write.\n");

        free(data);
    }

    return 0;
}
