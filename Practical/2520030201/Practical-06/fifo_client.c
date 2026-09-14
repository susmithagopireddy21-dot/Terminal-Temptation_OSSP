#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    char *fifo1 = "client_to_server";
    char *fifo2 = "server_to_client";

    char message[100];
    char response[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    int write_fd = open(fifo1, O_WRONLY);

    write(write_fd, message, strlen(message) + 1);

    close(write_fd);

    int read_fd = open(fifo2, O_RDONLY);

    read(read_fd, response, sizeof(response));

    printf("Server response: %s\n", response);

    close(read_fd);

    return 0;
}
