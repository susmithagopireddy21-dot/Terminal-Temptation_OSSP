#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int output_fd;
    int input_fd;
    int original_stdout;

    printf("===== I/O Redirection using dup2() =====\n");
    printf("Standard output is currently displayed on the terminal.\n");

    original_stdout = dup(STDOUT_FILENO);

    output_fd = open("redirect_output.txt",
                     O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (output_fd < 0)
    {
        perror("Error opening output file");
        return 1;
    }

    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);

    printf("This output is redirected to redirect_output.txt\n");
    printf("dup2() made the file descriptor become standard output.\n");

    fflush(stdout);

    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);

    printf("Standard output restored to the terminal.\n");

    input_fd = open("redirect_input.txt", O_RDONLY);

    if (input_fd < 0)
    {
        perror("Error opening input file");
        return 1;
    }

    dup2(input_fd, STDIN_FILENO);
    close(input_fd);

    char input[100];

    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        printf("Input read using redirected standard input: %s", input);
    }

    return 0;
}
