# Practical-07: Linux Process Address Space and Virtual Memory Analysis

## Objective

To study the memory organization of a Linux process by printing the addresses of code, global, static, heap, and stack variables. The `/proc/<PID>/maps` file and `pmap` command are used to analyze the virtual memory mappings of the running process.

## Program Used

`memory_addresses.c`

The program creates:

* A global variable
* A static variable
* A local stack variable
* A dynamically allocated heap variable
* A function representing the code segment

## Program Output

```text
Process ID     : 1746
Code address   : 0x56ff4a107209
Global address : 0x56ff4a10a010
Static address : 0x56ff4a10a014
Heap address   : 0x56ff7fe45010
Stack address  : 0x7fffbfd5517c
```

## Address Analysis

| Variable/Area | Address          | Memory Region     |
| ------------- | ---------------- | ----------------- |
| Code          | `0x56ff4a107209` | Code/Text segment |
| Global        | `0x56ff4a10a010` | Data segment      |
| Static        | `0x56ff4a10a014` | Data segment      |
| Heap          | `0x56ff7fe45010` | Heap              |
| Stack         | `0x7fffbfd5517c` | Stack             |

## Linux Process Address Space

### 1. Code/Text Segment

The code segment contains the machine instructions of the program.

The code address was:

```text
0x56ff4a107209
```

It falls inside:

```text
56ff4a107000-56ff4a108000 r-xp
```

The `r-xp` permission means the region is readable and executable.

### 2. Data Segment

The data segment stores initialized global and static variables.

The global variable address was:

```text
0x56ff4a10a010
```

The static variable address was:

```text
0x56ff4a10a014
```

Both fall inside:

```text
56ff4a10a000-56ff4a10b000 rw-p
```

The `rw-p` permission means the region is readable and writable.

### 3. BSS Segment

The BSS segment normally contains uninitialized global and static variables.

This program does not contain an uninitialized global or static variable, so a separate BSS example is not visible in the output.

### 4. Heap

The heap is used for dynamically allocated memory.

The program uses `malloc()` to allocate memory.

The heap address was:

```text
0x56ff7fe45010
```

It falls inside:

```text
56ff7fe45000-56ff7fe66000 rw-p [heap]
```

Therefore, the dynamically allocated memory is located in the heap.

### 5. Stack

The stack stores local variables and information related to function calls.

The stack variable address was:

```text
0x7fffbfd5517c
```

It falls inside:

```text
7fffbfd37000-7fffbfd58000 rw-p [stack]
```

Therefore, the local variable is located in the stack region.

## `/proc/1746/maps` Analysis

The `/proc/1746/maps` file shows the virtual memory regions assigned to process 1746.

Important mappings observed were:

```text
56ff4a107000-56ff4a108000 r-xp ... memory_addresses
56ff4a10a000-56ff4a10b000 rw-p ... memory_addresses
56ff7fe45000-56ff7fe66000 rw-p ... [heap]
7fffbfd37000-7fffbfd58000 rw-p ... [stack]
```

Other mappings included:

* `libc.so.6` — C standard library
* `ld-linux-x86-64.so.2` — dynamic linker
* `[vvar]` and `[vvar_vclock]` — kernel-provided virtual data
* `[vdso]` — virtual dynamic shared object

## Meaning of Memory Permissions

The permissions shown in `/proc/<PID>/maps` include:

* `r` → Read
* `w` → Write
* `x` → Execute
* `p` → Private mapping

For example:

```text
r-xp
```

means readable, executable, and privately mapped.

```text
rw-p
```

means readable, writable, and privately mapped.

## `pmap` Analysis

The `pmap` command was used to display the memory mappings of process 1746.

The command showed a total virtual memory mapping of approximately:

```text
2768K
```

It also displayed mappings for the program, heap, shared library `libc.so.6`, dynamic linker, and stack.

## Virtual Memory

Linux provides each process with its own virtual address space.

Virtual memory provides:

1. Process isolation
2. Memory protection
3. Efficient use of physical memory
4. Support for shared libraries
5. Dynamic memory allocation

The operating system maps virtual addresses to physical memory pages when required.

## ASLR

The addresses of memory regions can change between different program executions because Linux uses Address Space Layout Randomization (ASLR).

ASLR improves security by making memory locations less predictable.

## Conclusion

The practical successfully demonstrated the Linux process address space.

The addresses printed by the C program were matched with the corresponding regions in `/proc/1746/maps`. The code was found in the executable region, global and static variables were found in the writable data region, dynamically allocated memory was found in the heap, and the local variable was found in the stack.

The `pmap` command further confirmed the virtual memory organization of the running process.
