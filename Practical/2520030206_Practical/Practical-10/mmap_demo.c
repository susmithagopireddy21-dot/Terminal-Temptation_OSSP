#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "mmap_file.txt";
    const char *message = "Hello from memory-mapped I/O!\n";

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    size_t length = strlen(message);

    if (ftruncate(fd, length) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    char *mapped = mmap(NULL, length, PROT_READ | PROT_WRITE,
                        MAP_SHARED, fd, 0);

    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    /* Writing data using memory mapping */
    memcpy(mapped, message, length);

    if (msync(mapped, length, MS_SYNC) == -1) {
        perror("msync");
    }

    printf("Data written using mmap(): %.*s", (int)length, mapped);

    /* Reading data using memory mapping */
    printf("Data read using mmap(): %.*s", (int)length, mapped);

    if (munmap(mapped, length) == -1) {
        perror("munmap");
    }

    close(fd);

    return 0;
}
