# Practical 7 - Linux Process Address Space and Virtual Memory

## Objective

1. To write a C program that prints the addresses of code, global, static, heap, and stack variables.
2. To analyze the Linux process address space layout.
3. To use `/proc/<PID>/maps` and memory analysis tools to study the memory organization of a running process.
4. To understand virtual memory mappings and different memory segments.

---

# Part A - Printing Memory Addresses

## Program Description

The C program creates variables in different memory regions and prints their addresses.

The following memory areas are observed:

- Code/Text segment
- Global variable
- Static variable
- Heap
- Stack

Dynamic memory is allocated using `malloc()` for the heap variable.

The process ID is also displayed so that the process can be examined using the `/proc` filesystem.

## Observed Addresses

The program produced the following addresses during execution:

```text
Code/Function address : 0x638e7e467229
Global variable address: 0x638e7e46a010
Static variable address: 0x638e7e46a014
Heap variable address  : 0x638e9e471010
Stack variable address : 0x7ffc6d36707c

Process ID: 624

The exact addresses can change between executions because Linux uses Address Space Layout Randomization (ASLR).

---

# Part B - Linux Process Address Space

A Linux process has a virtual address space divided into different regions.

## 1. Code/Text Segment

The code segment contains the executable instructions of the program.

In `/proc/<PID>/maps`, it appears with execute permission:

```text
r-xp

The function address printed by the program belongs to this region.

2. Global and Static Data

Global and static variables are stored in the program's data-related memory mappings.

Writable program sections appear with permissions such as:

rw-p

The global and static variable addresses belong to this area.

3. Heap

The heap is used for dynamically allocated memory.

The program uses malloc() to allocate memory dynamically.

In /proc/<PID>/maps, the heap is identified as:

[heap]
4. Stack

The stack stores local variables and information used during function calls.

The local stack variable created in the program is located in the stack region.

In /proc/<PID>/maps, the stack is identified as:

[stack]
5. Shared Libraries

The process also maps shared libraries such as:

libc.so.6

These libraries provide standard functions used by the program.

6. Dynamic Linker

The dynamic linker is mapped into the process address space:

ld-linux-x86-64.so.2

It helps load and link shared libraries when the program starts.

Part C - /proc/<PID>/maps Analysis

The /proc/<PID>/maps file provides information about the virtual memory regions of a running process.

The following command was used:

cat /proc/624/maps

Important mappings observed were:

r-xp  memory_layout
rw-p  memory_layout
rw-p  [heap]
r-xp  libc.so.6
r-xp  ld-linux-x86-64.so.2
rw-p  [stack]

The permissions have the following meaning:

Permission	Meaning
r	Read
w	Write
x	Execute
p	Private mapping

The address range at the beginning of each line represents the virtual address range occupied by that mapping.

Part D - /proc/<PID>/smaps Analysis

The /proc/<PID>/smaps file provides detailed information about each virtual memory mapping.

The following command was used:

cat /proc/624/smaps | head -40

Important fields observed include:

Size
Rss
Pss
Private_Clean
Private_Dirty
Referenced
Swap
VmFlags
Meaning of Important Fields

Size: Total size of the memory mapping.

RSS: Amount of the mapping currently resident in physical memory.

PSS: Memory usage adjusted for shared pages.

Private_Dirty: Private pages that have been modified.

Referenced: Pages that have been recently referenced.

Swap: Amount of the mapping currently stored in swap.

Part E - pmap Memory Analysis

The pmap command was used to obtain a summary of the process memory mappings.

Command:

pmap -x 624

The output showed:

total kB            2768    1812     100

This represents:

Total virtual memory mappings: 2768 kB
Resident memory (RSS): 1812 kB
Dirty memory: 100 kB

The output also identified mappings such as:

memory_layout
libc.so.6
ld-linux-x86-64.so.2
[stack]
Virtual Memory Layout

The process memory organization can be summarized as:

Higher Addresses
-------------------------
        Stack
-------------------------
   Shared Libraries
-------------------------
        Heap
-------------------------
 Global / Static Data
-------------------------
    Code / Text
-------------------------
Lower Addresses

The exact virtual addresses and layout can vary because Linux uses virtual memory management and ASLR.

Observation Table
Memory Region	Purpose	Identification
Code/Text	Stores program instructions	r-xp executable mapping
Global	Stores global variables	Writable data mapping
Static	Stores static variables	Writable data mapping
Heap	Dynamic memory allocation	[heap]
Stack	Local variables and function calls	[stack]
Shared Libraries	Provides library functions	libc.so.6
Dynamic Linker	Loads shared libraries	ld-linux-x86-64.so.2
Screenshots
1. Variable Memory Addresses

2. Process Memory Mappings using /proc/<PID>/maps

3. Detailed Memory Information using /proc/<PID>/smaps

4. Memory Analysis using pmap

Conclusion

The experiment demonstrated the organization of a Linux process virtual address space.

The addresses of code, global, static, heap, and stack variables were obtained using a C program.

The /proc/<PID>/maps file was used to examine virtual memory mappings, while /proc/<PID>/smaps provided detailed memory information.

The pmap -x command was also used to analyze the memory usage of the running process.

The experiment showed how Linux separates different memory regions and provides each process with its own virtual address space.
