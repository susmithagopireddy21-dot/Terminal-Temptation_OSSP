#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;

    printf("===== Dynamic Memory Allocation =====\n\n");

    // malloc()
    int *a = malloc(5 * sizeof(int));

    for (i = 0; i < 5; i++)
        a[i] = i + 1;

    printf("malloc(): ");
    for (i = 0; i < 5; i++)
        printf("%d ", a[i]);
    printf("\n");

    // calloc()
    int *b = calloc(5, sizeof(int));

    printf("calloc(): ");
    for (i = 0; i < 5; i++)
        printf("%d ", b[i]);
    printf("\n");

    // realloc()
    a = realloc(a, 10 * sizeof(int));

    for (i = 5; i < 10; i++)
        a[i] = i + 1;

    printf("realloc(): ");
    for (i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");

    // free()
    free(a);
    free(b);

    printf("free(): Memory released\n");

    return 0;
}
