#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1000000

int main() {
    int *data = malloc(SIZE * sizeof(int));

    if (data == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        data[i] = i;
    }

    printf("Parent process PID: %d\n", getpid());
    printf("Memory allocated for array: %zu bytes\n",
           SIZE * sizeof(int));

    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        free(data);
        return 1;
    }

    if (pid == 0) {
        printf("\nChild process PID: %d\n", getpid());
        printf("Before modification: data[0] = %d\n", data[0]);

        data[0] = 999;

        printf("After modification: data[0] = %d\n", data[0]);
        printf("Child modified the memory, causing Copy-on-Write.\n");

        free(data);
        exit(0);
    } else {
        wait(NULL);

        printf("\nParent process after child exits:\n");
        printf("Parent data[0] = %d\n", data[0]);
        printf("Parent retains its original value.\n");

        free(data);
    }

    return 0;
}
