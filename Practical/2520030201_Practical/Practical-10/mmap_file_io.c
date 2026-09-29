#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>

#define FILE_SIZE 1000

int main()
{
    const char *filename = "mmap_test.txt";
    int fd;
    char *mapped_file;

    /* Create and write initial data */
    fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    if (ftruncate(fd, FILE_SIZE) == -1)
    {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    /* Map the file into memory */
    mapped_file = mmap(NULL, FILE_SIZE,
                       PROT_READ | PROT_WRITE,
                       MAP_SHARED, fd, 0);

    if (mapped_file == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    /* Write through memory mapping */
    strcpy(mapped_file,
           "Hello from memory-mapped file I/O using mmap().");

    /* Make changes visible in the file */
    msync(mapped_file, FILE_SIZE, MS_SYNC);

    printf("Data written using mmap():\n");
    printf("%s\n", mapped_file);

    /* Read through the memory mapping */
    printf("\nData read using mmap():\n");
    printf("%s\n", mapped_file);

    /* Remove mapping */
    munmap(mapped_file, FILE_SIZE);
    close(fd);

    printf("\nMemory-mapped I/O completed successfully.\n");

    printf("\nComparison:\n");
    printf("mmap(): Maps the file directly into memory and allows\n");
    printf("       access using normal memory operations.\n");
    printf("read()/write(): Explicitly transfers data using system calls.\n");
    printf("mmap() can simplify repeated random access, while\n");
    printf("read()/write() is generally simpler for sequential I/O.\n");

    return 0;
}
