# Practical 2 - File Copy Using System Calls

## Objective

To implement file copying in C using Linux system calls such as
open(), read(), write(), and close(), and to observe system calls
using strace.

## 1. File Copy Program

The program file is:

filecopy.c

System calls used:

- open() - Opens the source and destination files.
- read() - Reads data from the source file.
- write() - Writes data into the destination file.
- close() - Closes the opened files.

## 2. User Mode to Kernel Mode Transition

System calls provide an interface between user programs and the
Linux kernel.

When the C program calls open(), read(), write(), or close(), the
request transitions from user mode to kernel mode. The kernel
performs the required file operation and then returns the result
to the user program.

## 3. Program Execution

Source file:

source.txt

Destination file:

destination.txt

The program successfully copied the contents of source.txt into
destination.txt.

Output:

File copied successfully.

## 4. strace Demonstration

Command used:

strace cat sample.txt

The strace output was saved in:

strace_output.txt

Important system calls observed:

- execve() - Executes the cat program.
- openat() - Opens sample.txt.
- read() - Reads data from files.
- splice() - Transfers file data to the terminal.
- close() - Closes the file descriptor.
- exit_group() - Terminates the process successfully.

The command displayed:

This is a sample file for strace.

## Conclusion

The practical demonstrates file handling using Linux system calls.
It also shows how strace can be used to observe the system calls
made by a Linux command.
