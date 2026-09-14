# Practical-01 – OS Hardware Abstraction Report

## Objective

To investigate the Linux system using `uname`, `lscpu`, `lsblk`, `ps`, and `top` commands and understand how the Operating System abstracts hardware resources.

## Commands Used

### 1. uname
The `uname` command provides information about the operating system and kernel.

Command:
```bash
uname -a
### 2. lscpu
The `lscpu` command displays information about the CPU, such as processor architecture, number of CPUs, cores, and threads.

Command:
```bash
lscpu
### 3. lsblk
The `lsblk` command displays information about block devices such as hard disks, SSDs, and partitions.

Command:
```bash
lsblk
### 4. ps
The `ps` command displays information about currently running processes.

Command:
```bash
ps
### 5. top
The `top` command provides a real-time view of running processes and CPU and memory usage.

Command:
```bash
top
## OS Hardware Abstraction

### CPU
Linux abstracts the CPU through processes, threads, and scheduling. Applications do not directly control the CPU. The Operating System scheduler decides which process or thread gets CPU time.

### Memory
Linux provides each process with its own virtual address space. Programs can use memory without directly managing physical RAM addresses. The Operating System manages memory allocation, virtual memory, and protection.

### Storage
Linux represents storage devices through files and device interfaces. Applications can access files without needing to know the physical details of the disk. The file system manages files, directories, blocks, and storage allocation.

### I/O Devices
Linux provides standard interfaces and device files for input/output devices. Applications can communicate with devices through system calls instead of directly controlling hardware.

## Conclusion

The Linux Operating System provides an abstraction layer between applications and hardware. It manages CPU, memory, storage, and I/O devices and provides simple interfaces for programs to use these resources without directly interacting with the hardware.
