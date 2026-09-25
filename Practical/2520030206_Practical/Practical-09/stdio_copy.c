#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    FILE *source_file, *destination_file;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    source_file = fopen(argv[1], "rb");

    if (source_file == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    destination_file = fopen(argv[2], "wb");

    if (destination_file == NULL)
    {
        perror("Error opening destination file");
        fclose(source_file);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, source_file)) > 0)
    {
        if (fwrite(buffer, 1, bytes_read, destination_file) != bytes_read)
        {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(destination_file);
            return 1;
        }
    }

    printf("File copied successfully using standard library functions.\n");

    fclose(source_file);
    fclose(destination_file);

    return 0;
}
