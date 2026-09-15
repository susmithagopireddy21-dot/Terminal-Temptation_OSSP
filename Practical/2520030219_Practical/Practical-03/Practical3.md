# Practical-03 – Process Creation and State Observation

## Objective

To develop a C program using `fork()` that creates a parent and child process, displays their Process ID (PID) and Parent Process ID (PPID), and observes process states using Linux monitoring tools such as `ps`, `top`, and `/proc`.

## Program

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent process started\n");
    printf("Parent PID: %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());

        printf("Child is Running\n");

        sleep(60);

        printf("Child is Terminating\n");
    }
    else
    {
        printf("\nParent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);

        printf("Parent is Running\n");

        sleep(30);

        printf("Parent is Waiting for child\n");

        wait(NULL);

        printf("Child has Terminated\n");
    }

    return 0;
}
```

## Compilation

The program was compiled using GCC:

```bash
gcc Practical3.c -o Practical3
```

## Execution

The program was executed in the background using:

```bash
./Practical3 &
```

Sample output:

```text
Parent process started
Parent PID: 2411

Parent process
Parent PID: 2411
Child PID: 2413
Parent is Running

Child process
Child PID: 2413
Child PPID: 2411
Child is Running
```

After the parent waits for the child:

```text
Parent is Waiting for child
Child is Terminating
Child has Terminated
```

## Observation Using ps

The following command was used:

```bash
ps -o pid,ppid,stat,cmd -C Practical3
```

Observed output:

```text
PID    PPID    STAT    CMD
2289   333     S       ./Practical3
2291   2289    S       ./Practical3
```

### Observation

* PID `2289` is the parent process.
* PID `2291` is the child process.
* PPID `2289` for the child confirms that the child was created by the parent.
* `S` represents an interruptible sleeping state.
* The processes were in the sleeping state because the program uses `sleep()`.

## Observation Using /proc

The process information was checked using:

```bash
grep -E '^(Name|State|Pid|PPid):' /proc/2411/status
```

Output:

```text
Name:   Practical3
State:  S (sleeping)
Pid:    2411
PPid:   333
```

For the child process:

```bash
grep -E '^(Name|State|Pid|PPid):' /proc/2413/status
```

Output:

```text
Name:   Practical3
State:  S (sleeping)
Pid:    2413
PPid:   2411
```

### Observation

The `/proc` filesystem provides information about active processes.

* Parent PID = `2411`
* Child PID = `2413`
* Child PPID = `2411`
* Both processes were observed in the `S (sleeping)` state.
* The `/proc/<PID>/status` file provides process state, PID, and PPID information.

## Observation Using top

The following command was used:

```bash
top -p 2411,2413
```

The command was executed after the processes had terminated. Therefore, the process table did not show the two `Practical3` processes.

The output showed:

```text
Tasks:   0 total
```

This indicates that the specified processes were no longer active when `top` was executed.

## Process State Transitions

The experiment demonstrates the following process states:

| Stage             | Process State    | Description                                    |
| ----------------- | ---------------- | ---------------------------------------------- |
| Process creation  | Ready/Running    | Parent creates the child using `fork()`        |
| Execution         | Running          | Parent and child execute their respective code |
| `sleep()`         | Waiting/Sleeping | Process waits during the sleep period          |
| `wait()`          | Waiting          | Parent waits for the child to terminate        |
| Child completion  | Terminated       | Child finishes execution                       |
| Parent completion | Terminated       | Parent finishes after `wait()` returns         |

In Linux, the `ps` and `/proc` commands commonly show the sleeping state as `S`. A runnable or currently running process can appear as `R`.

## Conclusion

The program successfully demonstrates process creation using `fork()`. The parent and child processes have separate PIDs, and the child's PPID matches the parent's PID. The `ps` command and `/proc` filesystem were used to observe process information and sleeping states. The `wait()` system call allows the parent process to wait for the child process to complete before terminating.
