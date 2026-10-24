#ifndef HISTORY_H
#define HISTORY_H

typedef struct HistoryNode
{
    char *command;
    struct HistoryNode *next;
} HistoryNode;

void add_history(const char *command);
const char *get_history(int index);
int history_count(void);
void free_history(void);

#endif
