#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_variable = 10;

void code_function()
{
    printf("Code/Function address : %p\n", (void *)code_function);
}

int main()
{
    static int static_variable = 20;
    int stack_variable = 30;

    int *heap_variable = malloc(sizeof(int));

    if (heap_variable == NULL)
    {
        perror("malloc failed");
        return 1;
    }

    *heap_variable = 40;

    printf("Linux Process Memory Layout\n");
    printf("===========================\n");

    code_function();

    printf("Global variable address: %p\n",
           (void *)&global_variable);

    printf("Static variable address: %p\n",
           (void *)&static_variable);

    printf("Heap variable address  : %p\n",
           (void *)heap_variable);

    printf("Stack variable address : %p\n",
           (void *)&stack_variable);

    printf("\nProcess ID: %d\n", getpid());

    printf("\nProcess is running. Press Enter to terminate...\n");
    getchar();

    free(heap_variable);

    return 0;
}
