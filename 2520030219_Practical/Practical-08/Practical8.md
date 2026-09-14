# Practical-08 – Dynamic Memory Allocation and Copy-on-Write

## Objective

1. Develop a C program using `malloc()`, `calloc()`, `realloc()`, and `free()`.
2. Identify memory leaks using Valgrind.
3. Demonstrate Copy-on-Write behavior after `fork()`.
4. Analyze memory usage before and after modifying data in the child process.

---

## Part 1 – Dynamic Memory Allocation

### Program

The program demonstrates the use of:

- `malloc()` – allocates memory without initialization.
- `calloc()` – allocates memory and initializes it to zero.
- `realloc()` – changes the size of previously allocated memory.
- `free()` – releases dynamically allocated memory.

### File: memory.c

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;

    printf("===== Dynamic Memory Allocation =====\n\n");

    // malloc()
    int *a = malloc(5 * sizeof(int));

    for (i = 0; i < 5; i++)
        a[i] = i + 1;

    printf("malloc(): ");
    for (i = 0; i < 5; i++)
        printf("%d ", a[i]);
    printf("\n");

    // calloc()
    int *b = calloc(5, sizeof(int));

    printf("calloc(): ");
    for (i = 0; i < 5; i++)
        printf("%d ", b[i]);
    printf("\n");

    // realloc()
    a = realloc(a, 10 * sizeof(int));

    for (i = 5; i < 10; i++)
        a[i] = i + 1;

    printf("realloc(): ");
    for (i = 0; i < 10; i++)
        printf("%d ", a[i]);
    printf("\n");

    // free()
    free(a);
    free(b);

    printf("free(): Memory released\n");

    return 0;
}
c```


###Compilation
gcc memory.c -o memory

###Output
===== Dynamic Memory Allocation =====

malloc(): 1 2 3 4 5
calloc(): 0 0 0 0 0
realloc(): 1 2 3 4 5 6 7 8 9 10
free(): Memory released


###Valgrind Analysis

The program was checked using:

valgrind --leak-check=full ./memory
Actual Valgrind Result
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 4 allocs, 4 frees, 1,104 bytes allocated

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts
Analysis

Valgrind reported:

4 memory allocations.
4 memory releases.
0 bytes remaining at program exit.
0 memory leaks.
0 memory errors.

Therefore, all dynamically allocated memory was correctly released using free().


## Part 2 – Copy-on-Write using fork()

### Program

The program allocates a large array and initializes it before calling fork().

After fork():

Parent and child initially share the same physical memory pages.
The child modifies data[0].
The operating system creates a private copy of the modified page for the child.
The parent's value remains unchanged.

File: cow.c
c```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1000000

int main()
{
    int *data;
    pid_t pid;

    data = malloc(SIZE * sizeof(int));

    for (int i = 0; i < SIZE; i++)
        data[i] = 10;

    printf("Parent PID: %d\n", getpid());
    printf("Before fork: data[0] = %d\n", data[0]);

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild PID: %d\n", getpid());
        printf("Before modification: data[0] = %d\n", data[0]);

        printf("Child paused before modification...\n");
        sleep(30);

        data[0] = 99;

        printf("After modification: data[0] = %d\n", data[0]);
        printf("Child has its own copy of the modified page\n");

        printf("Child paused after modification...\n");
        sleep(30);

        free(data);
        exit(0);
    }
    else
    {
        wait(NULL);

        printf("\nParent after child modification: data[0] = %d\n", data[0]);
        printf("Parent data is unchanged\n");

        free(data);
    }

    return 0;
}
c```

### Compilation
gcc cow.c -o cow

### Actual Output
Parent PID: 5982
Before fork: data[0] = 10

Child PID: 5983
Before modification: data[0] = 10
Child paused before modification...
After modification: data[0] = 99
Child has its own copy of the modified page
Child paused after modification...

Parent after child modification: data[0] = 10
Parent data is unchanged

### Memory Analysis

The child process was inspected using the /proc/<PID>/status file.

Command Used
grep -E "VmSize|VmRSS|VmData" /proc/5983/status
Before Child Modification
VmSize:     6676 kB
VmRSS:      4912 kB
VmData:     4132 kB
After Child Modification
VmSize:     6676 kB
VmRSS:      4912 kB
VmData:     4132 kB
Analysis

The VmSize, VmRSS, and VmData values did not show an overall increase in the captured snapshots.

This does not mean that Copy-on-Write did not occur. Copy-on-Write works at the memory-page level.

Initially, the parent and child share the same physical memory pages. When the child modifies data[0], the operating system creates a private copy of the affected page for the child.

The virtual memory size can remain the same because the child still uses the same virtual address.

The main evidence of Copy-on-Write is:

Child before modification: data[0] = 10
Child after modification:  data[0] = 99
Parent after modification: data[0] = 10

Therefore, the child's modification does not affect the parent's data.

## Result

The program successfully demonstrated dynamic memory allocation using malloc(), calloc(), realloc(), and free().

Valgrind confirmed that there were no memory leaks or memory errors.

The Copy-on-Write program successfully demonstrated that after fork(), the child can modify its memory without changing the parent's data.

The /proc/<PID>/status file was used to observe the memory usage of the child process before and after modification.

Thus, both dynamic memory management and Copy-on-Write behavior were successfully demonstrated.
