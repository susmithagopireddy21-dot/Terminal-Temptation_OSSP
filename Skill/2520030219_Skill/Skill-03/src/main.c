#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "history.h"

int main(void)
{
    while (1)
    {
        printf("mini-shell> ");
        fflush(stdout);

        char *command = read_command();

        if (command == NULL)
        {
            printf("\nInput ended or memory allocation failed.\n");
            break;
        }

        if (strcmp(command, "exit") == 0)
        {
            free(command);
            printf("Exiting shell.\n");
            break;
        }

        if (command[0] != '\0')
        {
            add_history(command);
            printf("You entered: %s\n", command);
        }

        free(command);
    }

    free_history();
    return 0;
}
