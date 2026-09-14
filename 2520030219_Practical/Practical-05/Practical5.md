# Practical-05 – Inter-Process Communication Using Anonymous Pipes

## Objective

To implement a producer-consumer communication system using an anonymous pipe where the parent process generates data and the child process consumes it. The communication efficiency is measured by calculating the communication time.

To develop a program that executes the equivalent of the shell command `ls -l | grep ".c"` using `fork()`, `pipe()`, `dup2()`, and `exec()` system calls.

## 1. Producer-Consumer Communication Using Anonymous Pipe

### Program

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main()
{
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello from parent process!";
    char buffer[100];
    struct timespec start, end;
    double time_taken;

    printf("===== Part 1: Producer-Consumer using Anonymous Pipe =====\n\n");

    if (pipe(pipefd) == -1)
    {
        printf("Pipe creation failed\n");
        return 1;
    }

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        close(pipefd[1]);

        read(pipefd[0], buffer, sizeof(buffer));

        printf("Child process (Consumer)\n");
        printf("Received data: %s\n", buffer);

        close(pipefd[0]);
    }
    else
    {
        close(pipefd[0]);

        clock_gettime(CLOCK_MONOTONIC, &start);

        write(pipefd[1], message, strlen(message) + 1);

        clock_gettime(CLOCK_MONOTONIC, &end);

        time_taken = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1000000000.0;

        printf("Parent process (Producer)\n");
        printf("Sent data: %s\n", message);
        printf("Communication time: %.9f seconds\n", time_taken);

        close(pipefd[1]);

        wait(NULL);

        printf("Producer-Consumer communication completed\n");
    }

    if (pid == 0)
    {
        printf("\nConsumer process completed\n");
    }

    if (pid > 0)
    {
        int pipefd2[2];
        pid_t child1, child2;

        printf("\n===== Part 2: ls -l | grep \".c\" =====\n\n");

        if (pipe(pipefd2) == -1)
        {
            printf("Pipe creation failed\n");
            return 1;
        }

        child1 = fork();

        if (child1 < 0)
        {
            printf("Fork failed\n");
            return 1;
        }

        if (child1 == 0)
        {
            close(pipefd2[0]);

            dup2(pipefd2[1], STDOUT_FILENO);
            close(pipefd2[1]);

            execlp("ls", "ls", "-l", NULL);

            printf("Execution of ls failed\n");
            return 1;
        }

        child2 = fork();

        if (child2 < 0)
        {
            printf("Fork failed\n");
            return 1;
        }

        if (child2 == 0)
        {
            close(pipefd2[1]);

            dup2(pipefd2[0], STDIN_FILENO);
            close(pipefd2[0]);

            execlp("grep", "grep", ".c", NULL);

            printf("Execution of grep failed\n");
            return 1;
        }

        close(pipefd2[0]);
        close(pipefd2[1]);

        waitpid(child1, NULL, 0);
        waitpid(child2, NULL, 0);

        printf("\nPipeline execution completed\n");
    }

    return 0;
} c```

###Compilation
gcc Practical5.c -o Practical5

###Execution Output
===== Part 1: Producer-Consumer using Anonymous Pipe =====

Parent process (Producer)
Sent data: Hello from parent process!
Communication time: 0.000003480 seconds
Child process (Consumer)
Received data: Hello from parent process!

Consumer process completed
Producer-Consumer communication completed

===== Part 2: ls -l | grep ".c" =====

-rwxr-xr-x 1 sreeja sreeja 16520 Sep 14 19:13 Practical5
-rw-r--r-- 1 sreeja sreeja  2747 Sep 14 19:13 Practical5.c

Pipeline execution completed

##2. Producer-Consumer Communication

The anonymous pipe provides one-way communication between the parent and child processes.

###Communication Flow
Parent Process
    |
    | write()
    ↓
Anonymous Pipe
    |
    | read()
    ↓
Child Process

The parent process acts as the Producer and writes the message into the pipe.

The child process acts as the Consumer and reads the message from the pipe.

The pipe() system call creates the communication channel.

The write() system call sends data through the pipe, while read() receives the data from the pipe.

The wait() system call allows the parent to wait for the child process to complete.

##3. Communication Efficiency

The communication time was measured using clock_gettime().

###Measured Time
Communication time = 0.000003480 seconds

This is approximately:

3.48 microseconds

The small communication time shows that an anonymous pipe provides fast communication between related processes for small amounts of data.

##4. Executing ls -l | grep ".c"

The second part implements the equivalent of the shell command:

ls -l | grep ".c"
###Pipeline Flow
ls -l
  |
  | Standard Output
  ↓
Anonymous Pipe
  |
  | Standard Input
  ↓
grep ".c"

The first child process executes ls -l.

The output of ls -l is redirected to the pipe using dup2().

The second child process receives the pipe output as its standard input using dup2().

The second child executes grep ".c" using execlp().

The parent process uses waitpid() to wait for both child processes.

##5. System Calls Used
System Call	Purpose
fork()	Creates child processes.
pipe()	Creates an anonymous pipe for IPC.
dup2()	Redirects standard input or output to the pipe.
execlp()	Executes ls and grep.
write()	Writes data into the pipe.
read()	Reads data from the pipe.
wait()	Waits for a child process to complete.
waitpid()	Waits for a specific child process to complete.
close()	Closes unused pipe file descriptors.
##6. Result

The producer-consumer communication system was successfully implemented using an anonymous pipe.

The parent successfully sent data to the child, and the child successfully received the data.

The communication time was measured as 0.000003480 seconds.

The equivalent of ls -l | grep ".c" was successfully implemented using fork(), pipe(), dup2(), and execlp().

##7. Conclusion

This practical demonstrated Inter-Process Communication using anonymous pipes.

The producer-consumer model showed how a parent process can send data to a child process through a pipe.

The second experiment demonstrated how Linux shell pipelines work internally by connecting the output of one process to the input of another process using pipe() and dup2().

Thus, anonymous pipes provide an efficient method for communication between related processes, while fork(), dup2(), and exec() allow multiple processes to work together as a pipeline.
