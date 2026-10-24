
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define MAX_INPUT 100

int read_command(char *buffer, int size)
{
    struct termios old_term, new_term;
    int ch;
    int pos = 0;

    if (tcgetattr(STDIN_FILENO, &old_term) == -1)
        return -1;

    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) == -1)
        return -1;

    while (1)
    {
        ch = getchar();

        if (ch == EOF)
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
            return -1;
        }

        if (ch == '\n' || ch == '\r')
        {
            putchar('\n');
            break;
        }

        if (ch == 127 || ch == 8)
        {
            if (pos > 0)
            {
                pos--;
                printf("\b \b");
                fflush(stdout);
            }
        }
        else if (ch >= 32 && ch <= 126 && pos < size - 1)
        {
            buffer[pos++] = (char)ch;
            putchar(ch);
            fflush(stdout);
        }
    }

    buffer[pos] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);

    return pos;
}
