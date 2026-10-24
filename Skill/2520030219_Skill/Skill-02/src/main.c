
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100

int read_command(char *buffer, int size);

int main(void)
{
    char command[MAX_INPUT];

    while (1)
    {
        printf("mini-shell> ");
        fflush(stdout);

        int result = read_command(command, MAX_INPUT);

        if (result == -1)
        {
            printf("\nInput ended. Exiting shell.\n");
            break;
        }

        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting shell.\n");
            break;
        }

        if (result == 0)
            continue;

        printf("You entered: %s\n", command);
    }

    return 0;
}
