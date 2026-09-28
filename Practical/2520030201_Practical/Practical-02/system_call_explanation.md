# Practical-02 – File Copy Using System Calls

## Objective

To copy the contents of one file to another using the Linux system calls
open(), read(), write(), and close().

## System Calls Used

### 1. open()

The open() system call opens a file and returns a file descriptor.

In this program:
- source.txt is opened in read-only mode.
- destination.txt is opened for writing.

### 2. read()

The read() system call reads data from the source file into a buffer.

### 3. write()

The write() system call writes the data stored in the buffer into the destination file.

### 4. close()

The close() system call closes the file descriptors after the copying is completed.

## User Space and Kernel Space

The C program normally executes in user space.

When the program calls open(), read(), write(), or close(), control moves from user space to kernel space through a system call.

The Linux kernel performs the required file operation and then returns the result to the user-space program.

The basic flow is:

User Program
    |
    | system call
    v
Kernel Space
    |
    | file operation
    v
File System / Storage
    |
    v
Kernel Space
    |
    | return result
    v
User Program

## File Copy Process

source.txt
    |
    | open()
    v
File Descriptor
    |
    | read()
    v
Buffer
    |
    | write()
    v
destination.txt
    |
    | close()
    v
File Copy Completed

## Conclusion

The program successfully copies data from one file to another using
open(), read(), write(), and close(). System calls provide a controlled
interface between the user-space application and the Linux kernel.
