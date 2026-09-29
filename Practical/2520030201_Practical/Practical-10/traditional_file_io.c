#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1000

int main()
{
    const char *filename = "traditional_test.txt";
    int fd;
    char buffer[BUFFER_SIZE];
    const char *data = "Hello from traditional file I/O using read() and write().";

    /* Open/create file */
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    /* Write using write() */
    write(fd, data, strlen(data));

    close(fd);

    /* Open file for reading */
    fd = open(filename, O_RDONLY);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    /* Read using read() */
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE - 1);

    if (bytes_read < 0)
    {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';

    printf("Data written using write():\n");
    printf("%s\n", data);

    printf("\nData read using read():\n");
    printf("%s\n", buffer);

    close(fd);

    printf("\nTraditional read()/write() I/O completed successfully.\n");

    printf("\nComparison with mmap():\n");
    printf("read()/write(): Uses explicit system calls to transfer data.\n");
    printf("mmap(): Maps the file into memory for direct memory access.\n");
    printf("read()/write() is straightforward for sequential file I/O.\n");
    printf("mmap() can be convenient for repeated or random access.\n");

    return 0;
}
