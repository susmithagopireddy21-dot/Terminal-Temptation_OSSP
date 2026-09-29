#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int input_fd, output_fd;
    char buffer[100];
    ssize_t bytes_read;

    input_fd = open("input.txt", O_RDONLY);

    if (input_fd < 0) {
        perror("open input.txt");
        return 1;
    }

    output_fd = open("redirected_output.txt",
                     O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (output_fd < 0) {
        perror("open redirected_output.txt");
        close(input_fd);
        return 1;
    }

    /* Redirect standard input */
    if (dup2(input_fd, STDIN_FILENO) < 0) {
        perror("dup2 stdin");
        return 1;
    }

    /* Redirect standard output */
    if (dup2(output_fd, STDOUT_FILENO) < 0) {
        perror("dup2 stdout");
        return 1;
    }

    close(input_fd);
    close(output_fd);

    /* Read from redirected standard input */
    bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    if (bytes_read < 0) {
        perror("read");
        return 1;
    }

    buffer[bytes_read] = '\0';

    printf("Data received through redirected stdin:\n");
    printf("%s", buffer);

    return 0;
}
