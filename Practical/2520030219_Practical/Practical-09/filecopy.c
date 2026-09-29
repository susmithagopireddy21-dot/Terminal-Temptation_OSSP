#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 4096

void low_level_copy()
{
    int source, destination;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    off_t file_size;
    clock_t start, end;

    source = open("sample.txt", O_RDONLY);

    if (source < 0)
    {
        perror("Error opening source file");
        exit(1);
    }

    file_size = lseek(source, 0, SEEK_END);
    lseek(source, 0, SEEK_SET);

    destination = open("copy_low.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (destination < 0)
    {
        perror("Error opening destination file");
        close(source);
        exit(1);
    }

    start = clock();

    while ((bytes_read = read(source, buffer, BUFFER_SIZE)) > 0)
    {
        write(destination, buffer, bytes_read);
    }

    end = clock();

    close(source);
    close(destination);

    printf("\n===== Low-Level File Copy =====\n");
    printf("File size: %ld bytes\n", (long)file_size);
    printf("Methods used: open(), read(), write(), lseek(), close()\n");
    printf("Copy completed successfully\n");
    printf("Time taken: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);
}

void standard_library_copy()
{
    FILE *source, *destination;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    clock_t start, end;

    source = fopen("sample.txt", "r");

    if (source == NULL)
    {
        perror("Error opening source file");
        exit(1);
    }

    destination = fopen("copy_standard.txt", "w");

    if (destination == NULL)
    {
        perror("Error opening destination file");
        fclose(source);
        exit(1);
    }

    start = clock();

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source)) > 0)
    {
        fwrite(buffer, 1, bytes_read, destination);
    }

    end = clock();

    fclose(source);
    fclose(destination);

    printf("\n===== Standard Library File Copy =====\n");
    printf("Methods used: fopen(), fread(), fwrite(), fclose()\n");
    printf("Copy completed successfully\n");
    printf("Time taken: %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);
}

int main()
{
    printf("===== File Copy Performance Comparison =====\n");

    low_level_copy();
    standard_library_copy();

    printf("\n===== Comparison Completed =====\n");

    return 0;
}
