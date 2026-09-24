#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CLIENT_FIFO "client_to_server"
#define SERVER_FIFO "server_to_client"

int main()
{
    int client_fd, server_fd;
    char message[100];
    char response[150];

    printf("Client started.\n");

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    // Remove newline character
    message[strcspn(message, "\n")] = '\0';

    // Open client-to-server FIFO for writing
    client_fd = open(CLIENT_FIFO, O_WRONLY);

    if (client_fd == -1)
    {
        perror("Error opening client FIFO");
        return 1;
    }

    // Send message to server
    write(client_fd, message, strlen(message) + 1);
    close(client_fd);

    printf("Message sent to server.\n");

    // Open server-to-client FIFO for reading
    server_fd = open(SERVER_FIFO, O_RDONLY);

    if (server_fd == -1)
    {
        perror("Error opening server FIFO");
        return 1;
    }

    // Receive response from server
    read(server_fd, response, sizeof(response));
    close(server_fd);

    printf("Response from server: %s\n", response);

    printf("Client terminating.\n");

    return 0;
}
