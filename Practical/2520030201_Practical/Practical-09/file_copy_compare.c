#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 4096

void low_level_copy(const char *source, const char *destination)
{
    int src = open(source, O_RDONLY);
    int dest = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (src < 0 || dest < 0) {
        perror("open");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while ((bytes_read = read(src, buffer, BUFFER_SIZE)) > 0) {
        write(dest, buffer, bytes_read);
    }

    /* Demonstrate lseek() */
    lseek(src, 0, SEEK_SET);

    close(src);
    close(dest);
}

void standard_library_copy(const char *source, const char *destination)
{
    FILE *src = fopen(source, "rb");
    FILE *dest = fopen(destination, "wb");

    if (src == NULL || dest == NULL) {
        perror("fopen");
        exit(1);
    }

    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        fwrite(buffer, 1, bytes_read, dest);
    }

    fclose(src);
    fclose(dest);
}

int main()
{
    const char *source = "source.txt";
    const char *low_dest = "low_level_copy.txt";
    const char *std_dest = "standard_copy.txt";

    /* Create sample source file */
    FILE *file = fopen(source, "w");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    for (int i = 1; i <= 10000; i++) {
        fprintf(file,
                "This is sample data for file copy performance testing. Line %d\n",
                i);
    }

    fclose(file);

    clock_t start, end;
    double low_time, std_time;

    /* Low-level copy */
    start = clock();
    low_level_copy(source, low_dest);
    end = clock();

    low_time = (double)(end - start) / CLOCKS_PER_SEC;

    /* Standard library copy */
    start = clock();
    standard_library_copy(source, std_dest);
    end = clock();

    std_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("File copy completed successfully.\n");
    printf("\nLow-level system calls:\n");
    printf("open(), read(), write(), lseek(), close()\n");
    printf("Time taken: %.6f seconds\n", low_time);

    printf("\nStandard library functions:\n");
    printf("fopen(), fread(), fwrite(), fclose()\n");
    printf("Time taken: %.6f seconds\n", std_time);

    printf("\nPerformance comparison completed.\n");

    return 0;
}
