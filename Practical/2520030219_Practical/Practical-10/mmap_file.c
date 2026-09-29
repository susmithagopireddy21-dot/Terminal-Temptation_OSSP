#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char *mapped;
    struct stat file_stat;

    fd = open("mmap.txt", O_RDWR | O_CREAT, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    char data[] = "Hello from mmap!";
    write(fd, data, strlen(data));

    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }

    mapped = mmap(NULL, file_stat.st_size,
                  PROT_READ | PROT_WRITE,
                  MAP_SHARED, fd, 0);

    if (mapped == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("Original content: %s\n", mapped);

    mapped[0] = 'h';

    printf("Modified content: %s\n", mapped);

    if (msync(mapped, file_stat.st_size, MS_SYNC) == -1) {
        perror("msync");
    }

    munmap(mapped, file_stat.st_size);
    close(fd);

    return 0;
}
