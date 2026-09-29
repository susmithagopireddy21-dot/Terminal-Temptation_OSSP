# Skill-01: Process Abstraction and System Call Tracing

## Objective

To understand process abstraction, parent-child process relationships,
process creation using `fork()`, program execution using `exec()`,
process synchronization using `waitpid()`, and system-call tracing.

## Tools Used

- Linux / Ubuntu WSL
- GCC
- GNU Make
- Git
- strace

## Program

The program `skill01_process.c` demonstrates:

1. Creation of a child process using `fork()`.
2. Identification of parent and child process IDs.
3. Execution of the `ls -l` command using `execvp()`.
4. Synchronization using `waitpid()`.
5. Parent-child process relationship.

## Makefile

The Makefile provides targets for:

- Building the program using GCC.
- Running the program.
- Cleaning the generated executable.

## Execution Result

The program successfully created:

- Parent PID: 6583
- Child PID: 6584

The child process executed `ls -l` successfully.

The parent process waited for the child process to complete.

## System Call Tracing

System-call tracing was performed using:

```bash
strace -f -o skill01_strace.txt ./skill01_process
