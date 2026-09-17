# Practical 4 - Process Synchronization and Zombie Processes

## Objective

To write a C program where a parent process creates multiple child processes and synchronizes their completion using wait() and waitpid().

To compare the behavior of wait() and waitpid() and demonstrate the creation and elimination of a zombie process.

## Program 1 - wait() and waitpid()

The program creates three child processes using fork().

The parent process first uses wait() to wait for any child process that terminates.

After that, waitpid() is used to wait for a specific child process.

### wait()

The wait() system call waits for any one of the terminated child processes of the calling parent.

### waitpid()

The waitpid() system call can wait for a specific child process using its PID.

## Comparison

| wait() | waitpid() |
|---|---|
| Waits for any child process | Waits for a specific child process |
| Does not require a specific PID | Requires the PID of the child |
| Returns when any child terminates | Returns when the specified child terminates |
| Useful for general child synchronization | Useful for controlled child synchronization |

## Program 2 - Zombie Process

A zombie process is a child process that has terminated but whose parent has not yet collected its termination status using wait() or waitpid().

The parent process was kept running using sleep(), while the child terminated immediately.

The process table was checked using:

```bash
ps -ef | grep zombie
