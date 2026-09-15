#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_variable = 100;

void code_function()
{
    printf("Code address   : %p\n", (void *)code_function);
}

int main()
{
    static int static_variable = 200;
    int stack_variable = 300;
    int *heap_variable;

    heap_variable = (int *)malloc(sizeof(int));
    *heap_variable = 400;

    printf("Process ID     : %d\n", getpid());

    code_function();

    printf("Global address : %p\n", (void *)&global_variable);
    printf("Static address : %p\n", (void *)&static_variable);
    printf("Heap address   : %p\n", (void *)heap_variable);
    printf("Stack address  : %p\n", (void *)&stack_variable);

    printf("\nPress Enter to exit...\n");
    getchar();

    free(heap_variable);

    return 0;
}
