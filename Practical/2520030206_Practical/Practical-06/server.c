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
    char buffer[100];
    char response[150];

    // Create named pipes
    mkfifo(CLIENT_FIFO, 0666);
    mkfifo(SERVER_FIFO, 0666);

    printf("Multi-Client Server Started.\n");
    printf("Waiting for client messages...\n");

    while (1)
    {
        // Open client-to-server FIFO for reading
        client_fd = open(CLIENT_FIFO, O_RDONLY);

        if (client_fd == -1)
        {
            perror("Error opening client FIFO");
            return 1;
        }

        // Read message from client
        memset(buffer, 0, sizeof(buffer));
        read(client_fd, buffer, sizeof(buffer));
        close(client_fd);

        printf("Message received: %s\n", buffer);

        // Process the message
        snprintf(response, sizeof(response),
                 "Server processed your message: %s", buffer);

        // Open server-to-client FIFO for writing
        server_fd = open(SERVER_FIFO, O_WRONLY);

        if (server_fd == -1)
        {
            perror("Error opening server FIFO");
            return 1;
        }

        // Send response
        write(server_fd, response, strlen(response) + 1);
        close(server_fd);

        printf("Response sent to client.\n");
        printf("Waiting for next client...\n\n");
    }

    return 0;
}
