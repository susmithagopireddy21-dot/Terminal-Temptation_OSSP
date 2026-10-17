#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("fork() failed\n");
        return 1;
    }

    if (pid == 0) {
        printf("Child running: PID=%d, PPID=%d\n", getpid(), getppid());
        sleep(10);
        printf("Child finished\n");
    } else {
        printf("Parent running: PID=%d, Child PID=%d\n", getpid(), pid);
        sleep(10);
        wait(NULL);
        printf("Parent finished\n");
    }

    return 0;
}
