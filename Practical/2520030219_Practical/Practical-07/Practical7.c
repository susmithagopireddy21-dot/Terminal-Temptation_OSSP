#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 10;

void show_code_address()
{
    printf("Code address   : %p\n", (void *)show_code_address);
}

int main()
{
    static int static_var = 20;
    int stack_var = 30;
    int *heap_var = malloc(sizeof(int));

    *heap_var = 40;

    printf("===== Process Memory Addresses =====\n");

    show_code_address();

    printf("Global address : %p\n", (void *)&global_var);
    printf("Static address : %p\n", (void *)&static_var);
    printf("Heap address   : %p\n", (void *)heap_var);
    printf("Stack address  : %p\n", (void *)&stack_var);

    printf("\nProcess PID: %d\n", getpid());

    printf("\nPress Enter to exit...\n");
    getchar();

    free(heap_var);

    return 0;
}
