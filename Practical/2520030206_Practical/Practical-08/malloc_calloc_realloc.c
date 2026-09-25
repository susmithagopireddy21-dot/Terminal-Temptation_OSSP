#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;
    int *malloc_ptr;
    int *calloc_ptr;
    int *realloc_ptr;

    printf("Dynamic Memory Allocation Demonstration\n");
    printf("========================================\n\n");

    /* malloc() */
    malloc_ptr = (int *)malloc(5 * sizeof(int));

    if (malloc_ptr == NULL)
    {
        printf("malloc() allocation failed.\n");
        return 1;
    }

    for (i = 0; i < 5; i++)
    {
        malloc_ptr[i] = (i + 1) * 10;
    }

    printf("malloc() allocated 5 integers:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d ", malloc_ptr[i]);
    }
    printf("\n\n");

    /* calloc() */
    calloc_ptr = (int *)calloc(5, sizeof(int));

    if (calloc_ptr == NULL)
    {
        printf("calloc() allocation failed.\n");
        free(malloc_ptr);
        return 1;
    }

    printf("calloc() allocated 5 integers and initialized them to zero:\n");
    for (i = 0; i < 5; i++)
    {
        printf("%d ", calloc_ptr[i]);
    }
    printf("\n\n");

    /* realloc() */
    realloc_ptr = (int *)malloc(3 * sizeof(int));

    if (realloc_ptr == NULL)
    {
        printf("Initial realloc() allocation failed.\n");
        free(malloc_ptr);
        free(calloc_ptr);
        return 1;
    }

    for (i = 0; i < 3; i++)
    {
        realloc_ptr[i] = (i + 1) * 100;
    }

    printf("Before realloc(), 3 integers:\n");
    for (i = 0; i < 3; i++)
    {
        printf("%d ", realloc_ptr[i]);
    }
    printf("\n");

    realloc_ptr = (int *)realloc(realloc_ptr, 6 * sizeof(int));

    if (realloc_ptr == NULL)
    {
        printf("realloc() failed.\n");
        free(malloc_ptr);
        free(calloc_ptr);
        return 1;
    }

    for (i = 3; i < 6; i++)
    {
        realloc_ptr[i] = (i + 1) * 100;
    }

    printf("After realloc(), memory expanded to 6 integers:\n");
    for (i = 0; i < 6; i++)
    {
        printf("%d ", realloc_ptr[i]);
    }
    printf("\n\n");

    /* free() */
    free(malloc_ptr);
    free(calloc_ptr);
    free(realloc_ptr);

    printf("All allocated memory was freed successfully.\n");

    return 0;
}
