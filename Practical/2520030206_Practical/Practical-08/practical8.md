# Practical 8 - Dynamic Memory Allocation and Copy-on-Write

## Aim

1. Develop a program using `malloc()`, `calloc()`, `realloc()`, and `free()`.
2. Monitor memory allocation behavior and identify memory leaks using Valgrind.
3. Develop a program that demonstrates Copy-on-Write behavior after a `fork()`.
4. Analyze memory usage before and after modifying data in the child process.

---

# Part A - Dynamic Memory Allocation

## Objective

To demonstrate the use of `malloc()`, `calloc()`, `realloc()`, and `free()` in C and check the program for memory leaks using Valgrind.

## Program

File name: `malloc_calloc_realloc.c`

The program demonstrates:

- `malloc()` - allocates memory without initialization.
- `calloc()` - allocates memory and initializes it to zero.
- `realloc()` - changes the size of previously allocated memory.
- `free()` - releases dynamically allocated memory.

## Compilation

```bash
gcc malloc_calloc_realloc.c -o malloc_calloc_realloc
