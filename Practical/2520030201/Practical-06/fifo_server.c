#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    char *fifo1 = "client_to_server";
    char *fifo2 = "server_to_client";

    char message[100];
    char response[100];

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);

    printf("Server started...\n");
    printf("Waiting for client message...\n");

    int read_fd = open(fifo1, O_RDONLY);

    read(read_fd, message, sizeof(message));
    printf("Client sent: %s\n", message);

    close(read_fd);

    strcpy(response, "Server received your message!");

    int write_fd = open(fifo2, O_WRONLY);

    write(write_fd, response, strlen(response) + 1);

    printf("Server response sent.\n");

    close(write_fd);

    unlink(fifo1);
    unlink(fifo2);

    return 0;
}
