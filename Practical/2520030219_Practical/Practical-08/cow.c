#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1000000

int main()
{
    int *data;
    pid_t pid;

    data = malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++)
        data[i] = 10;

    printf("Parent PID: %d\n", getpid());
    printf("Before fork: data[0] = %d\n", data[0]);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild PID: %d\n", getpid());
        printf("Before modification: data[0] = %d\n", data[0]);
        printf("Child paused before modification...\n");
        sleep(10);

        data[0] = 99;

        printf("After modification: data[0] = %d\n", data[0]);
        printf("Child has its own copy of the modified page\n");

        printf("Child paused after modification...\n");
        sleep(30);

        free(data);
        exit(0);
    }
    else
    {
        wait(NULL);

        printf("\nParent after child modification: data[0] = %d\n", data[0]);
        printf("Parent data is unchanged\n");

        free(data);
    }

    return 0;
}
