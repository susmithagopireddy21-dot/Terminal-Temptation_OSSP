#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define BUFFER_SIZE 100

void enable_raw_mode(struct termios *original)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void restore_terminal(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}

int main()
{
    struct termios original;
    char input[BUFFER_SIZE];
    int length;

    enable_raw_mode(&original);

    printf("========================================\n");
    printf("       Skill 2 - Interactive Loop\n");
    printf("========================================\n");
    printf("Type a command and press Enter.\n");
    printf("Available commands: help, hello, exit\n");
    printf("Backspace is supported.\n\n");

    while (1)
    {
        length = 0;
        input[0] = '\0';

        printf("> ");
        fflush(stdout);

        while (1)
        {
            char ch;

            if (read(STDIN_FILENO, &ch, 1) != 1)
                continue;

            if (ch == '\n' || ch == '\r')
            {
                input[length] = '\0';
                printf("\n");
                break;
            }

            if (ch == 127 || ch == 8)
            {
                if (length > 0)
                {
                    length--;
                    input[length] = '\0';

                    printf("\b \b");
                    fflush(stdout);
                }
                continue;
            }

            if (length < BUFFER_SIZE - 1)
            {
                input[length++] = ch;
                input[length] = '\0';

                putchar(ch);
                fflush(stdout);
            }
        }

        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting program...\n");
            break;
        }
        else if (strcmp(input, "help") == 0)
        {
            printf("Available commands:\n");
            printf("  help  - Display available commands\n");
            printf("  hello - Display greeting\n");
            printf("  exit  - Exit the program\n");
        }
        else if (strcmp(input, "hello") == 0)
        {
            printf("Hello! Command received successfully.\n");
        }
        else if (length > 0)
        {
            printf("You entered: %s\n", input);
        }
        else
        {
            printf("Empty input. Please enter a command.\n");
        }
    }

    restore_terminal(&original);

    return 0;
}
