#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define INITIAL_BUFFER_SIZE 16

typedef struct HistoryNode
{
    char *command;
    struct HistoryNode *next;
} HistoryNode;

void enable_raw_mode(struct termios *original)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void restore_terminal(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}

void free_history(HistoryNode *head)
{
    while (head != NULL)
    {
        HistoryNode *temp = head;
        head = head->next;

        free(temp->command);
        free(temp);
    }
}

int add_history(HistoryNode **head, const char *command)
{
    HistoryNode *new_node = malloc(sizeof(HistoryNode));

    if (new_node == NULL)
        return 0;

    new_node->command = malloc(strlen(command) + 1);

    if (new_node->command == NULL)
    {
        free(new_node);
        return 0;
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
            current = current->next;

        current->next = new_node;
    }

    return 1;
}

HistoryNode *get_history_command(HistoryNode *head, int index)
{
    int current_index = 0;

    while (head != NULL)
    {
        if (current_index == index)
            return head;

        current_index++;
        head = head->next;
    }

    return NULL;
}

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

void clear_display(int length)
{
    while (length > 0)
    {
        printf("\b \b");
        length--;
    }

    fflush(stdout);
}

int main()
{
    struct termios original;

    HistoryNode *history = NULL;
    int history_position = -1;

    enable_raw_mode(&original);

    printf("========================================\n");
    printf("       Skill 3 - Command History\n");
    printf("========================================\n");
    printf("Type commands and press Enter.\n");
    printf("Use Up/Down arrows to recall commands.\n");
    printf("Backspace is supported.\n");
    printf("Type exit to quit.\n\n");

    while (1)
    {
        size_t buffer_size = INITIAL_BUFFER_SIZE;
        size_t length = 0;

        char *input = malloc(buffer_size);

        if (input == NULL)
        {
            printf("\nMemory allocation failed.\n");
            break;
        }

        input[0] = '\0';
        history_position = -1;

        printf("> ");
        fflush(stdout);

        while (1)
        {
            char ch;

            if (read(STDIN_FILENO, &ch, 1) != 1)
                continue;

            /*
             * Enter key
             */
            if (ch == '\n' || ch == '\r')
            {
                input[length] = '\0';
                printf("\n");
                break;
            }

            /*
             * Backspace
             */
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

            /*
             * Escape sequence handling
             *
             * Up arrow:    ESC [ A
             * Down arrow:  ESC [ B
             */
            if (ch == 27)
            {
                char sequence[2];

                if (read(STDIN_FILENO, &sequence[0], 1) != 1)
                    continue;

                if (sequence[0] != '[')
                    continue;

                if (read(STDIN_FILENO, &sequence[1], 1) != 1)
                    continue;

if (sequence[1] == 'A')
{
    int count = history_count(history);

    if (count > 0)
    {
        if (history_position == -1)
            history_position = count - 1;
        else if (history_position > 0)
            history_position--;
        else
            continue;

        HistoryNode *node =
            get_history_command(history, history_position);

        if (node != NULL)
        {
            clear_display((int)length);

            length = strlen(node->command);

            while (buffer_size <= length)
            {
                buffer_size *= 2;

                char *temp = realloc(input, buffer_size);

                if (temp == NULL)
                {
                    free(input);
                    restore_terminal(&original);
                    free_history(history);
                    return 1;
                }

                input = temp;
            }

            strcpy(input, node->command);
            printf("%s", input);
            fflush(stdout);
        }
    }

    continue;
}

if (sequence[1] == 'B')
{
    int count = history_count(history);

    if (count > 0 && history_position != -1)
    {
        if (history_position < count - 1)
        {
            history_position++;

            HistoryNode *node =
                get_history_command(history, history_position);

            if (node != NULL)
            {
                clear_display((int)length);

                length = strlen(node->command);

                while (buffer_size <= length)
                {
                    buffer_size *= 2;

                    char *temp = realloc(input, buffer_size);

                    if (temp == NULL)
                    {
                        free(input);
                        restore_terminal(&original);
                        free_history(history);
                        return 1;
                    }

                    input = temp;
                }

                strcpy(input, node->command);
                printf("%s", input);
                fflush(stdout);
            }
        }
        else
        {
            clear_display((int)length);
            length = 0;
            input[0] = '\0';
            history_position = -1;
            fflush(stdout);
        }
    }

    continue;
}
                continue;
            }

            /*
             * Dynamically resize buffer
             */
            if (length + 1 >= buffer_size)
            {
                size_t new_size = buffer_size * 2;

                char *temp = realloc(input, new_size);

                if (temp == NULL)
                {
                    printf("\nUnable to resize input buffer.\n");
                    free(input);
                    restore_terminal(&original);
                    free_history(history);
                    return 1;
                }

                input = temp;
                buffer_size = new_size;
            }

            /*
             * Store character
             */
            input[length++] = ch;
            input[length] = '\0';

            putchar(ch);
            fflush(stdout);
        }

        /*
         * Exit condition
         */
        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting program...\n");
            free(input);
            break;
        }

        /*
         * Store non-empty command in linked-list history
         */
        if (length > 0)
        {
            if (!add_history(&history, input))
            {
                printf("Warning: unable to store command in history.\n");
            }
        }

        printf("Command received: %s\n", input);

        free(input);
    }

    restore_terminal(&original);
    free_history(history);

    return 0;
}
