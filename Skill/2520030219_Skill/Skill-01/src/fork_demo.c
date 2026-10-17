#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Before fork()\n");

    pid = fork();

    if (pid < 0) {
        printf("fork() failed\n");
    }
    else if (pid == 0) {
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());
        sleep(3);
        printf("Child finished\n");
    }
    else {
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        wait(NULL);

        printf("Parent: Child has finished\n");
    }

    return 0;
}
