#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filename = "traditional_file.txt";
    const char *message = "Hello from traditional read/write I/O!\n";
    char buffer[100];

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    /* Writing data using write() */
    if (write(fd, message, strlen(message)) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("Data written using write(): %s", message);

    /* Move file pointer to beginning */
    lseek(fd, 0, SEEK_SET);

    /* Reading data using read() */
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';

    printf("Data read using read(): %s", buffer);

    close(fd);

    return 0;
}
