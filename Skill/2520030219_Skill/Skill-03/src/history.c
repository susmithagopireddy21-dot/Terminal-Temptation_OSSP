#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

static HistoryNode *head = NULL;
static HistoryNode *tail = NULL;
static int count = 0;

void add_history(const char *command)
{
    HistoryNode *node = malloc(sizeof(HistoryNode));

    if (node == NULL)
    {
        perror("malloc");
        return;
    }

    node->command = malloc(strlen(command) + 1);

    if (node->command == NULL)
    {
        perror("malloc");
        free(node);
        return;
    }

    strcpy(node->command, command);
    node->next = NULL;

    if (head == NULL)
        head = node;
    else
        tail->next = node;

    tail = node;
    count++;
}

const char *get_history(int index)
{
    HistoryNode *current = head;

    if (index < 0 || index >= count)
        return NULL;

    for (int i = 0; i < index; i++)
        current = current->next;

    return current->command;
}

int history_count(void)
{
    return count;
}

void free_history(void)
{
    HistoryNode *current = head;

    while (current != NULL)
    {
        HistoryNode *next = current->next;
        free(current->command);
        free(current);
        current = next;
    }

    head = NULL;
    tail = NULL;
    count = 0;
}
