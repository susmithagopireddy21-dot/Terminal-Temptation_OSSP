#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char message[100];
    int fd;

    mkfifo("server_fifo", 0666);

    printf("Server started. Waiting for clients...\n");

    while (1)
    {
        fd = open("server_fifo", O_RDONLY);

        if (read(fd, message, sizeof(message)) > 0)
        {
            printf("Client message: %s", message);
        }

        close(fd);

        fd = open("server_fifo", O_WRONLY);

        write(fd, "Message processed by server", 28);

        close(fd);

        printf("Response sent to client\n\n");
    }

    return 0;
}
