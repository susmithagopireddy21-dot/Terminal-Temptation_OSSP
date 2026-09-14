# Practical-01 – OS Hardware Abstraction Report

## Objective

To investigate the Linux system using the commands `uname`, `lscpu`, `lsblk`, `ps`, and `top`, and understand how the Operating System abstracts CPU, memory, storage, and I/O devices.

## Commands Used

### 1. uname

The `uname` command provides information about the Linux operating system, kernel, and system architecture.

**Command:**

```bash
uname -a
```

**Output:**

```text
Linux IdeapadSlim3 6.18.33.2-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Thu Jun 18 21:54:43 UTC 2026 x86_64 GNU/Linux
```

**Observation:**

The system is running Linux through WSL2 on an x86_64 architecture. The command provides details about the kernel and system environment.

### 2. lscpu

The `lscpu` command displays information about the CPU architecture, cores, threads, and processor model.

**Command:**

```bash
lscpu
```

**Output:**

```text
Architecture:                x86_64
CPU(s):                      16
Model name:                 13th Gen Intel(R) Core(TM) i7-13620H
Thread(s) per core:         2
Core(s) per socket:         8
Socket(s):                  1
```

**Observation:**

The CPU has 8 cores and 2 threads per core, providing 16 logical CPUs. Linux uses these logical CPUs to schedule processes and threads.

### 3. lsblk

The `lsblk` command displays information about block devices available to the Linux system.

**Command:**

```bash
lsblk
```

**Output:**

```text
NAME MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
sda    8:0    0 356.9M  1 disk
sdb    8:16   0 159.4M  1 disk
sdc    8:32   0     2G  0 disk [SWAP]
sdd    8:48   0     1T  0 disk /mnt/wslg/distro
                               /
```

**Observation:**

The WSL2 Linux environment provides block devices that are managed by the operating system. The `sdd` device is mounted as the main Linux filesystem, while `sdc` is used as swap space.

### 4. ps

The `ps` command displays information about currently running processes.

**Command:**

```bash
ps
```

**Output:**

```text
PID TTY          TIME CMD
333 pts/0    00:00:00 bash
1213 pts/0    00:00:00 ps
```

**Observation:**

The output shows the running shell process and the `ps` command itself. Each process has a unique Process ID (PID) managed by the operating system.

### 5. top

The `top` command provides a real-time view of processes and system resource usage.

**Command:**

```bash
top
```

**Important Observations:**

```text
Tasks: 24 total, 1 running, 23 sleeping, 0 stopped, 0 zombie

Memory:
7771.7 MiB total
7039.0 MiB free
577.7 MiB used

Swap:
2048.0 MiB total
2048.0 MiB free
```

**Observation:**

The `top` command shows that Linux monitors process states, CPU usage, memory usage, and swap usage. It provides a real-time view of how system resources are being used.

## OS Hardware Abstraction

### CPU

Linux abstracts the CPU through processes, threads, and scheduling. Applications do not directly control the physical CPU cores. The operating system scheduler decides which process or thread gets CPU time and manages access to the available logical CPUs.

### Memory

Linux provides each process with a virtual address space. Applications can use memory without directly dealing with physical RAM addresses. The operating system manages memory allocation, protection, virtual memory, and swap space.

### Storage

Linux abstracts storage through block devices and file systems. Applications normally access files and directories instead of directly controlling the physical storage device. The operating system manages storage allocation, files, directories, and device access.

### I/O Devices

Linux provides standard interfaces and system calls for input/output operations. Applications can communicate with hardware devices through the operating system instead of directly controlling the hardware. Device drivers and the kernel handle communication between software and hardware.

## Conclusion

The Linux Operating System acts as an abstraction layer between applications and hardware. It manages CPU scheduling, memory, storage, and I/O devices and provides standard interfaces for applications to use these resources. Commands such as `uname`, `lscpu`, `lsblk`, `ps`, and `top` help users observe how these resources are managed by the operating system.

