# Practical-01 – Linux Command Execution and Hardware Abstraction

## Aim

To demonstrate how a Linux Operating System executes a command entered by a user using process creation and system calls.

###Question :

Develop a C program that demonstrates how a Linux operating system executes a command entered by a user that 
1. Accept a Linux command as input. 
2. Create a child process using fork(). 
3. Execute the command in the child process using an appropriate exec() system call. 
4. Allow the parent process to wait for the child using wait (). 
5. Display the Process ID (PID) of both parent and child processes.

Using Linux terminal commands (uname, lscpu, lsblk, ps, top), investigate the relationship between hardware resources and operating system services. Prepare a report explaining how the OS abstracts CPU, memory, storage, and I/O devices. 

## Objective

1. Accept a Linux command as input from the user.
2. Create a child process using `fork()`.
3. Execute the command in the child process.
4. Use the parent process to wait for the child process to complete.
5. Display the Parent PID and Child PID.
6. Study Linux hardware abstraction using system commands.

## Program

The program accepts a Linux command from the user and creates a child process using `fork()`.

The child process executes the command using:

```c
execl("/bin/sh", "sh", "-c", command, NULL);
c```


The parent process waits for the child process using wait().

##Input

The Linux command entered by the user is:

ls

The input is also stored in input.txt.

##Output

The program successfully creates a child process and executes the ls command.

The actual output is stored in output.txt.

Enter Linux command: ls
Parent PID: 1208
Child PID: 1209
Program  Program.c  hardware.md  input.txt  output.txt
Child process completed
System Calls Used:
###fork()

Creates a new child process.

###execl()

Replaces the child process with the specified command.

###wait()

Makes the parent process wait until the child process completes.

###getpid()

Returns the Process ID of the current process.

##Explanation

When the program starts, it accepts a Linux command from the user.

The fork() system call creates a child process.

The child process executes the entered command using the execl() system call.

The parent process waits for the child process using wait().

After the child process finishes execution, the parent process continues.

##Hardware Abstraction

The Linux Operating System provides an abstraction layer between applications and hardware.

The following commands were used to observe system resources:

uname
lscpu
lsblk
ps
top

The detailed hardware abstraction report is available in hardware.md.

##Result

The Linux command was successfully accepted from the user, executed by a child process, and monitored by the parent process. The practical also demonstrates how Linux abstracts hardware resources through the Operating System.
