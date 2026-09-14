#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal)
{
    if (signal == SIGINT)
        printf("\nSIGINT received: Interrupt signal handled.\n");

    else if (signal == SIGTERM)
        printf("\nSIGTERM received: Termination signal handled.\n");

    else if (signal == SIGUSR1)
        printf("\nSIGUSR1 received: User-defined signal handled.\n");
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    printf("Signal handling program started.\n");
    printf("Process PID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1)
    {
        pause();
    }

    return 0;
}
