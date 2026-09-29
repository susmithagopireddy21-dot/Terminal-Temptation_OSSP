#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    // malloc()
    int *arr = (int *)malloc(3 * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Memory allocated using malloc():\n");
    for (i = 0; i < 3; i++) {
        arr[i] = (i + 1) * 10;
        printf("%d ", arr[i]);
    }
    printf("\n");

    // calloc()
    int *zero_arr = (int *)calloc(3, sizeof(int));

    if (zero_arr == NULL) {
        printf("Memory allocation failed\n");
        free(arr);
        return 1;
    }

    printf("Memory allocated using calloc():\n");
    for (i = 0; i < 3; i++) {
        printf("%d ", zero_arr[i]);
    }
    printf("\n");

    // realloc()
    arr = (int *)realloc(arr, 5 * sizeof(int));

    if (arr == NULL) {
        printf("Memory reallocation failed\n");
        free(zero_arr);
        return 1;
    }

    printf("Memory after realloc():\n");
    for (i = 0; i < 5; i++) {
        if (i >= 3) {
            arr[i] = (i + 1) * 10;
        }
        printf("%d ", arr[i]);
    }
    printf("\n");

    // free()
    free(arr);
    free(zero_arr);

    printf("Memory freed successfully.\n");

    return 0;
}
