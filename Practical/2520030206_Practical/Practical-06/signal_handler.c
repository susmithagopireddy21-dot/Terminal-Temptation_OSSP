#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal_number)
{
    if (signal_number == SIGINT)
    {
        printf("\nSIGINT received. Signal handler executed.\n");
    }
    else if (signal_number == SIGTERM)
    {
        printf("\nSIGTERM received. Signal handler executed.\n");
    }
    else if (signal_number == SIGUSR1)
    {
        printf("\nSIGUSR1 received. Signal handler executed.\n");
    }

    fflush(stdout);
}

int main()
{
    printf("POSIX Signal Handling Program\n");
    printf("Process ID: %d\n", getpid());

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    printf("Signal handlers registered.\n");
    printf("Waiting for signals...\n");

    while (1)
    {
        pause();
    }

    return 0;
}
