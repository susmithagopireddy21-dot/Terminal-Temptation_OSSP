# Practical 1 - Hardware and OS Investigation

## 1. uname -a

Command:
uname -a

Observation:
The command displays information about the Linux kernel, system name,
kernel version, architecture, and WSL2 environment.

Output:
Linux DESKTOP-S2DN3KB 6.18.33.2-microsoft-standard-WSL2 #1 SMP
PREEMPT_DYNAMIC Thu Jun 18 21:54:43 UTC 2026 x86_64 GNU/Linux


## 2. lscpu

Command:
lscpu

Observation:
The system uses an x86_64 architecture and has 12 logical CPUs.
The processor is a 13th Gen Intel Core i7-1355U with 6 cores and
2 threads per core.


## 3. lsblk

Command:
lsblk

Observation:
The command displays the available block devices and their sizes,
types, and mount points. The WSL2 environment provides virtualized
storage devices to Linux.


## 4. ps

Command:
ps -ef

Observation:
The command displays currently running processes along with their
process IDs, parent process IDs, users, and commands.


## 5. top

Command:
top

Observation:
The top command displays running processes and CPU and memory usage.
During the observation, most processes were in the sleeping state
and one process was running.

System observation:
CPU usage was very low and most of the CPU was idle.
Memory usage was also low and no swap was being used.


## OS Abstraction

The operating system provides an abstraction layer between applications
and the hardware.

CPU:
The OS manages CPU resources and schedules processes so that multiple
programs can run efficiently.

Memory:
The OS manages memory and provides each process with its own virtual
address space.

Storage:
The OS provides files and directories as an abstraction over physical
storage devices.

I/O:
The OS provides system calls and device interfaces so applications can
perform input and output without directly controlling hardware.

Conclusion:
The Linux commands show how the operating system provides information
about and manages CPU, memory, storage, processes, and I/O resources.
