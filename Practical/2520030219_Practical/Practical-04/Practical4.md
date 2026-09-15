# Practical-04 – Process Synchronization and Zombie Processes

## Objective

To develop a C program where a parent process creates multiple child processes and synchronizes their completion using `wait()` and `waitpid()`. To compare the behavior of both functions and demonstrate the creation and elimination of a zombie process.

## 1. Multiple Child Processes Using wait() and waitpid()

### Program

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child1, child2;
    int status;

    printf("Parent process started\n");
    printf("Parent PID: %d\n\n", getpid());

    child1 = fork();

    if (child1 < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (child1 == 0)
    {
        printf("Child 1 started\n");
        printf("Child 1 PID: %d\n", getpid());

        sleep(3);

        printf("Child 1 completed\n");
        return 10;
    }

    child2 = fork();

    if (child2 < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (child2 == 0)
    {
        printf("\nChild 2 started\n");
        printf("Child 2 PID: %d\n", getpid());

        sleep(6);

        printf("Child 2 completed\n");
        return 20;
    }

    printf("\nParent waiting using wait()\n");

    wait(&status);

    printf("wait() collected a child process\n");
    printf("Child exit status: %d\n", WEXITSTATUS(status));

    printf("\nParent waiting for Child 2 using waitpid()\n");

    waitpid(child2, &status, 0);

    printf("waitpid() collected Child 2\n");
    printf("Child 2 exit status: %d\n", WEXITSTATUS(status));

    printf("\nAll child processes completed\n");

    return 0;
}


c```


###Compilation
gcc Practical4.c -o Practical4
Execution Output
Parent process started
Parent PID: 2699

Child 1 started

Parent waiting using wait()
Child 1 PID: 2700

Child 2 started
Child 2 PID: 2701
Child 1 completed
wait() collected a child process
Child exit status: 10

Parent waiting for Child 2 using waitpid()
Child 2 completed
waitpid() collected Child 2
Child 2 exit status: 20

All child processes completed
##2. Comparison of wait() and waitpid()
Function	Behavior
wait()	Waits for any child process to terminate.
waitpid()	Waits for a specific child process using its PID.
wait()	Useful when the parent does not need to select a particular child.
waitpid()	Useful when the parent needs control over a particular child.

In this program, wait() collected Child 1 because it was the first child to complete. Then waitpid(child2, &status, 0) specifically waited for Child 2.

##3. Creating a Zombie Process

A zombie process is a child process that has terminated but whose parent has not yet collected its exit status using wait() or waitpid().

###Zombie Program
c```#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child is terminating\n");

        return 0;
    }
    else
    {
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is sleeping\n");

        sleep(60);

        printf("Parent is terminating\n");
    }

    return 0;
} c```
###Zombie Observation

The program was executed and the following process IDs were obtained:

Parent PID: 2846
Child PID: 2847

The following command was used to observe the processes:

ps -o pid,ppid,stat,cmd -p 2846,2847
Output
PID    PPID   STAT   CMD
2846    333   S+     ./zombie
2847   2846   Z+     [zombie] <defunct>

The child process with PID 2847 was in the Z+ state.

Z indicates a zombie process. The child had terminated, but the parent was still alive and had not called wait().

##4. Eliminating the Zombie Process

The program was modified to use wait() in the parent process.

###Modified Program
c```
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child is terminating\n");

        return 0;
    }
    else
    {
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is waiting for child\n");

        wait(NULL);

        printf("Child process collected\n");
        printf("Parent is terminating\n");
    }

    return 0;
}
c```

### Compilation
gcc zombie.c -o zombie

###Execution Output
Parent process
Parent PID: 2953
Child PID: 2954
Parent is waiting for child
Child process
Child PID: 2954
Child is terminating
Child process collected
Parent is terminating

The wait(NULL) system call allows the parent process to collect the terminated child's exit status. Therefore, the child does not remain as a zombie process.

## 5. Conclusion

This practical demonstrated process synchronization using wait() and waitpid(). The difference between waiting for any child and waiting for a specific child was observed.

A zombie process was created by allowing a child to terminate while the parent did not call wait(). The zombie was observed using the ps command with the Z process state.

Finally, the zombie process was eliminated by using wait() in the parent process. This demonstrates the importance of proper process synchronization and child process management in Linux.
