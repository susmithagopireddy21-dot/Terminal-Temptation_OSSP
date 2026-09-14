#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello from parent process!";
    char buffer[100];
    struct timespec start, end;
    double time_taken;

    printf("===== Part 1: Producer-Consumer using Anonymous Pipe =====\n\n");

    if (pipe(pipefd) == -1)
    {
        printf("Pipe creation failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));

        printf("Child process (Consumer)\n");
        printf("Received data: %s\n", buffer);

        close(pipefd[0]);
    }
    else
    {
        close(pipefd[0]);

        clock_gettime(CLOCK_MONOTONIC, &start);

        write(pipefd[1], message, strlen(message) + 1);

        clock_gettime(CLOCK_MONOTONIC, &end);

        time_taken = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1000000000.0;

        printf("Parent process (Producer)\n");
        printf("Sent data: %s\n", message);
        printf("Communication time: %.9f seconds\n", time_taken);

        close(pipefd[1]);

        wait(NULL);

        printf("Producer-Consumer communication completed\n");
    }

    if (pid == 0)
    {
        printf("\nConsumer process completed\n");
    }

    if (pid > 0)
    {
        int pipefd2[2];
        pid_t child1, child2;

        printf("\n===== Part 2: ls -l | grep \".c\" =====\n\n");

        if (pipe(pipefd2) == -1)
        {
            printf("Pipe creation failed\n");
            return 1;
        }

        child1 = fork();

        if (child1 < 0)
        {
            printf("Fork failed\n");
            return 1;
        }

        if (child1 == 0)
        {
            close(pipefd2[0]);

            dup2(pipefd2[1], STDOUT_FILENO);
            close(pipefd2[1]);

            execlp("ls", "ls", "-l", NULL);

            printf("Execution of ls failed\n");
            return 1;
        }

        child2 = fork();

        if (child2 < 0)
        {
            printf("Fork failed\n");
            return 1;
        }

        if (child2 == 0)
        {
            close(pipefd2[1]);

            dup2(pipefd2[0], STDIN_FILENO);
            close(pipefd2[0]);

            execlp("grep", "grep", ".c", NULL);

            printf("Execution of grep failed\n");
            return 1;
        }

        close(pipefd2[0]);
        close(pipefd2[1]);

        waitpid(child1, NULL, 0);
        waitpid(child2, NULL, 0);

        printf("\nPipeline execution completed\n");
    }

    return 0;
}
