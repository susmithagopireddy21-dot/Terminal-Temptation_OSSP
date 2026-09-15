#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char message[100];
    char response[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    fd = open("server_fifo", O_WRONLY);

    write(fd, message, strlen(message) + 1);

    close(fd);

    fd = open("server_fifo", O_RDONLY);

    read(fd, response, sizeof(response));

    printf("Server response: %s\n", response);

    close(fd);

    return 0;
}
