#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int input_fd, output_fd;
    char buffer[100];

    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    input_fd = open(argv[1], O_RDONLY);

    if (input_fd == -1)
    {
        perror("Error opening input file");
        return 1;
    }

    output_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (output_fd == -1)
    {
        perror("Error opening output file");
        close(input_fd);
        return 1;
    }

    if (dup2(input_fd, STDIN_FILENO) == -1)
    {
        perror("dup2 input failed");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    if (dup2(output_fd, STDOUT_FILENO) == -1)
    {
        perror("dup2 output failed");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    close(input_fd);
    close(output_fd);

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        printf("Data read through redirected standard input:\n");
        printf("%s", buffer);
        printf("Output was written through redirected standard output.\n");
    }

    return 0;
}
