#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <ctype.h>

#define INITIAL_BUFFER_SIZE 64

struct termios original_terminal;

typedef struct HistoryNode
{
    char *command;
    struct HistoryNode *next;
} HistoryNode;

/* Restore normal terminal settings */
void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal);
}

/* Enable character-by-character input */
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

/* Add a command to history */
void add_history(HistoryNode **head, const char *command)
{
    HistoryNode *new_node = malloc(sizeof(HistoryNode));

    if (new_node == NULL)
    {
        perror("History allocation failed");
        return;
    }

    new_node->command = malloc(strlen(command) + 1);

    if (new_node->command == NULL)
    {
        perror("Command allocation failed");
        free(new_node);
        return;
    }

    strcpy(new_node->command, command);
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        HistoryNode *current = *head;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_node;
    }
}

/* Count history entries */
int history_count(HistoryNode *head)
{
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}

/* Get command at a particular history position */
char *get_history_command(HistoryNode *head, int index)
{
    int current_index = 0;

    while (head != NULL)
    {
        if (current_index == index)
        {
            return head->command;
        }

        current_index++;
        head = head->next;
    }

    return NULL;
}

/* Free the complete history list */
void free_history(HistoryNode *head)
{
    HistoryNode *current;

    while (head != NULL)
    {
        current = head;
        head = head->next;

        free(current->command);
        free(current);
    }
}

/* Display recalled command */
void display_buffer(const char *buffer)
{
    printf("\r\033[K");
    printf("Skill-03> %s", buffer);
    fflush(stdout);
}

int main(void)
{
    size_t capacity = INITIAL_BUFFER_SIZE;
    size_t length = 0;

    char *input_buffer = malloc(capacity);
    HistoryNode *history = NULL;

    int history_position = -1;

    if (input_buffer == NULL)
    {
        perror("Input buffer allocation failed");
        return 1;
    }

    if (setup_terminal() == -1)
    {
        perror("Terminal setup failed");
        free(input_buffer);
        return 1;
    }

    printf("Skill-03: Command History and Dynamic Memory\n");
    printf("Type commands and press Enter.\n");
    printf("Use Up/Down arrows for command history.\n");
    printf("Use Backspace to edit.\n");
    printf("Type exit to quit.\n\n");

    while (1)
    {
        length = 0;
        input_buffer[0] = '\0';
        history_position = -1;

        printf("Skill-03> ");
        fflush(stdout);

        while (1)
        {
            char ch;

            if (read(STDIN_FILENO, &ch, 1) != 1)
            {
                printf("\n");
                free(input_buffer);
                free_history(history);
                return 0;
            }

            /* Enter key */
            if (ch == '\n' || ch == '\r')
            {
                input_buffer[length] = '\0';

                printf("\n");

                if (length > 0)
                {
                    printf("You entered: %s\n", input_buffer);

                    add_history(&history, input_buffer);

                    if (strcmp(input_buffer, "exit") == 0)
                    {
                        printf("Exiting Skill-03 shell...\n");

                        free(input_buffer);
                        free_history(history);

                        return 0;
                    }
                }

                break;
            }

            /* Backspace */
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

            /* Escape sequence */
            if (ch == 27)
            {
                char sequence[2];

                if (read(STDIN_FILENO, &sequence[0], 1) != 1)
                {
                    continue;
                }

                if (sequence[0] != '[')
                {
                    continue;
                }

                if (read(STDIN_FILENO, &sequence[1], 1) != 1)
                {
                    continue;
                }

                /* Up Arrow */
                if (sequence[1] == 'A')
                {
                    int count = history_count(history);

                    if (count > 0)
                    {
                        if (history_position == -1)
                        {
                            history_position = count - 1;
                        }
                        else if (history_position > 0)
                        {
                            history_position--;
                        }

                        char *command =
                            get_history_command(history, history_position);

                        if (command != NULL)
                        {
                            strcpy(input_buffer, command);
                            length = strlen(input_buffer);

                            display_buffer(input_buffer);
                        }
                    }

                    continue;
                }

                /* Down Arrow */
                if (sequence[1] == 'B')
                {
                    int count = history_count(history);

                    if (count > 0 && history_position != -1)
                    {
                        if (history_position < count - 1)
                        {
                            history_position++;

                            char *command =
                                get_history_command(
                                    history, history_position);

                            if (command != NULL)
                            {
                                strcpy(input_buffer, command);
                                length = strlen(input_buffer);

                                display_buffer(input_buffer);
                            }
                        }
                        else
                        {
                            history_position = -1;
                            length = 0;
                            input_buffer[0] = '\0';

                            display_buffer(input_buffer);
                        }
                    }

                    continue;
                }

                continue;
            }

            /* Printable character */
            if (isprint((unsigned char)ch))
            {
                if (length + 1 >= capacity)
                {
                    size_t new_capacity = capacity * 2;

                    char *new_buffer =
                        realloc(input_buffer, new_capacity);

                    if (new_buffer == NULL)
                    {
                        perror("Buffer expansion failed");

                        free(input_buffer);
                        free_history(history);

                        return 1;
                    }

                    input_buffer = new_buffer;
                    capacity = new_capacity;

                    printf("\n[Input buffer resized to %zu bytes]\n",
                           capacity);

                    printf("Skill-03> %s", input_buffer);
                    fflush(stdout);
                }

                input_buffer[length] = ch;
                length++;

                input_buffer[length] = '\0';

                write(STDOUT_FILENO, &ch, 1);
            }
        }
    }
}
