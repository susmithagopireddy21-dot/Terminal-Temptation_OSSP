#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "input.h"
#include "history.h"

#define INITIAL_SIZE 16

static int enable_raw_mode(struct termios *old_term)
{
    struct termios new_term;

    if (tcgetattr(STDIN_FILENO, old_term) == -1)
        return -1;

    new_term = *old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 1;
    new_term.c_cc[VTIME] = 0;

    return tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

char *read_command(void)
{
    struct termios old_term;
    char *buffer = malloc(INITIAL_SIZE);
    size_t capacity = INITIAL_SIZE;
    size_t pos = 0;
    int history_pos = history_count();

    if (buffer == NULL)
        return NULL;

    if (enable_raw_mode(&old_term) == -1)
    {
        free(buffer);
        return NULL;
    }

    while (1)
    {
        int ch = getchar();

        if (ch == EOF)
        {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
            free(buffer);
            return NULL;
        }

        if (ch == '\n' || ch == '\r')
        {
            putchar('\n');
            break;
        }

        if (ch == 27)
        {
            int next = getchar();

            if (next == '[')
            {
                int arrow = getchar();

                if (arrow == 'A' && history_pos > 0)
                    history_pos--;
                else if (arrow == 'B' && history_pos < history_count())
                    history_pos++;
                else
                    continue;

                const char *saved = get_history(history_pos);

                if (history_pos == history_count())
                    pos = 0;
                else if (saved != NULL)
                {
                    size_t len = strlen(saved);

                    while (len + 1 > capacity)
                    {
                        size_t new_capacity = capacity * 2;
                        char *temp = realloc(buffer, new_capacity);

                        if (temp == NULL)
                            goto memory_error;

                        buffer = temp;
                        capacity = new_capacity;
                    }

                    memcpy(buffer, saved, len + 1);
                    pos = len;
                }

                if (history_pos == history_count())
                    buffer[0] = '\0';

                printf("\r\033[Kmini-shell> %s", buffer);
                fflush(stdout);
            }

            continue;
        }

        if (ch == 127 || ch == 8)
        {
            if (pos > 0)
            {
                pos--;
                buffer[pos] = '\0';
                printf("\b \b");
                fflush(stdout);
            }

            continue;
        }

        if (ch >= 32 && ch <= 126)
        {
            if (pos + 1 >= capacity)
            {
                size_t new_capacity = capacity * 2;
                char *temp = realloc(buffer, new_capacity);

                if (temp == NULL)
                    goto memory_error;

                buffer = temp;
                capacity = new_capacity;
            }

            buffer[pos++] = (char)ch;
            buffer[pos] = '\0';
            putchar(ch);
            fflush(stdout);
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    return buffer;

memory_error:
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    free(buffer);
    return NULL;
}
