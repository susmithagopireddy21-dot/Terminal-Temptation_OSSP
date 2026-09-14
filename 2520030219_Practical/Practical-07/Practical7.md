# Practical-07 – Process Address Space and Virtual Memory Analysis

## Objective

To write a C program that prints the addresses of code, global, static, heap, and stack variables. To analyze the Linux process address space using the `/proc/<PID>/maps` file and the `pmap` memory analysis tool.

## 1. Program to Display Memory Addresses

### Program

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 10;

void show_code_address()
{
    printf("Code address   : %p\n", (void *)show_code_address);
}

int main()
{
    static int static_var = 20;
    int stack_var = 30;
    int *heap_var = malloc(sizeof(int));

    *heap_var = 40;

    printf("===== Process Memory Addresses =====\n");

    show_code_address();

    printf("Global address : %p\n", (void *)&global_var);
    printf("Static address : %p\n", (void *)&static_var);
    printf("Heap address   : %p\n", (void *)heap_var);
    printf("Stack address  : %p\n", (void *)&stack_var);

    printf("\nProcess PID: %d\n", getpid());

    printf("\nPress Enter to exit...\n");
    getchar();

    free(heap_var);

    return 0;
}
```

## 2. Compilation

Command:

```text
gcc Practical7.c -o Practical7
```

The program was compiled successfully without errors.

## 3. Program Execution

Command:

```text
./Practical7
```

Output:

```text
===== Process Memory Addresses =====
Code address   : 0x61528e3a4209
Global address : 0x61528e3a7010
Static address : 0x61528e3a7014
Heap address   : 0x6152b92c7010
Stack address  : 0x7ffea080a09c

Process PID: 4276

Press Enter to exit...
```

## 4. Analysis of Memory Addresses

| Variable | Address | Memory Segment |
|---|---|---|
| Code | `0x61528e3a4209` | Code/Text |
| Global | `0x61528e3a7010` | Data |
| Static | `0x61528e3a7014` | Data |
| Heap | `0x6152b92c7010` | Heap |
| Stack | `0x7ffea080a09c` | Stack |

### Code/Text Segment

The code address is:

```text
0x61528e3a4209
```

The `/proc/4276/maps` file contains:

```text
61528e3a4000-61528e3a5000 r-xp 00001000 08:30 51796 /home/sreeja/Terminal-Temptation_OSSP/2520030219_Practical/Practical-07/Practical7
```

The `r-xp` permission means the region is readable and executable. This region contains the machine code of the program.

### Global and Static Data Segment

The global variable address is:

```text
0x61528e3a7010
```

The static variable address is:

```text
0x61528e3a7014
```

The `/proc/4276/maps` file contains:

```text
61528e3a7000-61528e3a8000 rw-p 00003000 08:30 51796 /home/sreeja/Terminal-Temptation_OSSP/2520030219_Practical/Practical-07/Practical7
```

Both addresses fall inside this range.

The `rw-p` permission means the region is readable and writable. Global and static variables with initialized values are stored in the data segment.

### Heap Segment

The heap address is:

```text
0x6152b92c7010
```

The `/proc/4276/maps` file contains:

```text
6152b92c7000-6152b92e8000 rw-p 00000000 00:00 0 [heap]
```

The heap is used for dynamic memory allocation. In the program, `malloc()` allocates memory from the heap.

### Stack Segment

The stack address is:

```text
0x7ffea080a09c
```

The `/proc/4276/maps` file contains:

```text
7ffea07eb000-7ffea080c000 rw-p 00000000 00:00 0 [stack]
```

The stack stores local variables, function calls, and other temporary data. The `stack_var` variable is stored in this region.

## 5. `/proc/<PID>/maps` Analysis

Command:

```text
cat /proc/4276/maps
```

Important mappings observed:

```text
61528e3a3000-61528e3a4000 r--p ... Practical7
61528e3a4000-61528e3a5000 r-xp ... Practical7
61528e3a5000-61528e3a6000 r--p ... Practical7
61528e3a6000-61528e3a7000 r--p ... Practical7
61528e3a7000-61528e3a8000 rw-p ... Practical7
6152b92c7000-6152b92e8000 rw-p ... [heap]
75cbf4800000-75cbf4828000 r--p ... libc.so.6
75cbf4828000-75cbf49c0000 r-xp ... libc.so.6
75cbf49c0000-75cbf4a0e000 r--p ... libc.so.6
7ffea07eb000-7ffea080c000 rw-p ... [stack]
```

The mappings show that a process is divided into different virtual memory regions. The executable, heap, shared libraries, and stack each have separate virtual address ranges.

## 6. Meaning of Memory Permissions

The `/proc/<PID>/maps` file shows permissions for each memory region.

- `r` – Read permission
- `w` – Write permission
- `x` – Execute permission
- `p` – Private mapping

For example:

```text
r-xp
```

means the region is readable and executable, while:

```text
rw-p
```

means the region is readable and writable.

## 7. Shared Libraries

The process also contains mappings for:

```text
libc.so.6
ld-linux-x86-64.so.2
```

`libc.so.6` provides standard C library functions such as `printf()`, `malloc()`, and `free()`.

`ld-linux-x86-64.so.2` is the dynamic linker that helps load shared libraries required by the program.

## 8. pmap Memory Analysis

Command:

```text
pmap 4276
```

Output:

```text
4276:   ./Practical7
000061528e3a3000      4K r---- Practical7
000061528e3a4000      4K r-x-- Practical7
000061528e3a5000      4K r---- Practical7
000061528e3a6000      4K r---- Practical7
000061528e3a7000      4K rw--- Practical7
00006152b92c7000    132K rw---   [ anon ]
000075cbf4800000    160K r---- libc.so.6
000075cbf4828000   1632K r-x-- libc.so.6
000075cbf49c0000    312K r---- libc.so.6
000075cbf4a0e000     16K r---- libc.so.6
000075cbf4a12000      8K rw--- libc.so.6
000075cbf4a14000     52K rw---   [ anon ]
000075cbf4b5c000     12K rw---   [ anon ]
000075cbf4b64000      8K rw---   [ anon ]
000075cbf4b66000     16K r----   [ anon ]
000075cbf4b6a000      8K r----   [ anon ]
000075cbf4b6c000      8K r-x--   [ anon ]
000075cbf4b6e000      4K r---- ld-linux-x86-64.so.2
000075cbf4b6f000    188K r-x-- ld-linux-x86-64.so.2
000075cbf4b9e000     44K r---- ld-linux-x86-64.so.2
000075cbf4ba9000      8K r---- ld-linux-x86-64.so.2
000075cbf4bab000      4K rw--- ld-linux-x86-64.so.2
00007ffea07eb000    132K rw---   [ stack ]
 total             2768K
```

The `pmap` output shows the memory regions of the running process and their sizes.

The total mapped memory reported by `pmap` was:

```text
2768K
```

## 9. Linux Process Address Space Layout

A simplified process memory layout is:

```text
High Addresses
+----------------------+
|        Stack         |
|        ↓             |
+----------------------+
| Shared Libraries     |
| libc, dynamic linker |
+----------------------+
|        Heap          |
|        ↑             |
+----------------------+
| Data Segment         |
| Global/Static        |
+----------------------+
| Code/Text Segment    |
| Program instructions |
+----------------------+
Low Addresses
```

The actual layout can vary because Linux uses virtual memory and address randomization.

## 10. Virtual Memory

Virtual memory gives each process its own virtual address space. The addresses printed by the program are virtual addresses rather than direct physical RAM addresses.

The `/proc/4276/maps` file shows how the virtual address space is divided into memory mappings. Each mapping has an address range, permissions, and sometimes a file or special region associated with it.

Linux can map program files, shared libraries, heap memory, stack memory, and other anonymous regions into the process address space.

## 11. Role of ASLR

Linux uses Address Space Layout Randomization (ASLR) to randomize the locations of memory regions. Therefore, the exact addresses may be different each time the program runs.

The important point is the relationship between an address and its memory segment, rather than the exact numeric address.

## 12. Result

The C program successfully displayed the addresses of code, global, static, heap, and stack variables.

The `/proc/4276/maps` file successfully showed the virtual memory mappings of the running process. The `pmap` command provided a readable summary of the memory regions and their sizes.

## 13. Conclusion

This practical demonstrated the organization of a Linux process address space. Code is stored in the text segment, global and static variables are stored in the data segment, dynamically allocated memory is stored in the heap, and local variables are stored in the stack.

The `/proc/<PID>/maps` file and `pmap` tool were used to observe these virtual memory mappings. The experiment also demonstrated memory permissions, shared libraries, virtual addresses, and the effect of ASLR on process memory layout.
