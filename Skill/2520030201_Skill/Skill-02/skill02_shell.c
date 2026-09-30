#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

struct termios original_terminal;

void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal);
}

int setup_terminal(void)
{
    struct termios raw_terminal;

    if (tcgetattr(STDIN_FILENO, &original_terminal) == -1)
    {
        return -1;
    }

    raw_terminal = original_terminal;

    raw_terminal.c_lflag &= ~(ICANON | ECHO);
    raw_terminal.c_cc[VMIN] = 1;
    raw_terminal.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal) == -1)
    {
        return -1;
    }

    atexit(restore_terminal);
    return 0;
}

int main(void)
{
    size_t capacity = 64;
    size_t length = 0;

    char *input_buffer = malloc(capacity);

    if (input_buffer == NULL)
    {
        perror("Memory allocation failed");
        return 1;
    }

    if (setup_terminal() == -1)
    {
        perror("Terminal setup failed");
        free(input_buffer);
        return 1;
    }

    printf("Skill-02: Interactive Input Loop\n");
    printf("Type a command and press Enter.\n");
    printf("Use Backspace to edit the input.\n");
    printf("Type exit to quit.\n\n");

    while (1)
    {
        length = 0;
        input_buffer[0] = '\0';

        printf("Skill-02> ");
        fflush(stdout);

        while (1)
        {
            char ch;

            if (read(STDIN_FILENO, &ch, 1) != 1)
            {
                printf("\n");
                free(input_buffer);
                return 0;
            }

            /* Handle Enter key */
            if (ch == '\n' || ch == '\r')
            {
                input_buffer[length] = '\0';

                printf("\nYou entered: %s\n", input_buffer);

                if (strcmp(input_buffer, "exit") == 0)
                {
                    printf("Exiting Skill-02 shell...\n");
                    free(input_buffer);
                    return 0;
                }

                break;
            }

            /* Handle Backspace key */
            if (ch == 127 || ch == '\b')
            {
                if (length > 0)
                {
                    length--;
                    input_buffer[length] = '\0';

                    write(STDOUT_FILENO, "\b \b", 3);
                }

                continue;
            }

            /* Handle normal printable characters */
            if (isprint((unsigned char)ch))
            {
                if (length + 1 >= capacity)
                {
                    capacity *= 2;

                    char *new_buffer =
                        realloc(input_buffer, capacity);

                    if (new_buffer == NULL)
                    {
                        perror("Buffer expansion failed");
                        free(input_buffer);
                        return 1;
                    }

                    input_buffer = new_buffer;
                }

                input_buffer[length] = ch;
                length++;

                input_buffer[length] = '\0';

                write(STDOUT_FILENO, &ch, 1);
            }
        }
    }
}
