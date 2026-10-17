#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Before exec()\n");
    printf("PID: %d\n", getpid());

    execlp("ls", "ls", "-l", NULL);

    printf("This line will not execute if exec() succeeds\n");

    return 0;
}
