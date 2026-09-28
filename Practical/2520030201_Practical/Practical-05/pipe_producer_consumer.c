#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello from Producer!";
    char buffer[100];

    pipe(pipefd);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0)
    {
        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));

        printf("Consumer received: %s\n", buffer);

        close(pipefd[0]);
    }
    else
    {
        close(pipefd[0]);

        write(pipefd[1], message, sizeof(message));

        printf("Producer sent: %s\n", message);

        close(pipefd[1]);

        wait(NULL);
    }

    return 0;
}
