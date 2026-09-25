# Practical 8 - Dynamic Memory Allocation and Copy-on-Write

## Aim

1. Develop a program using `malloc()`, `calloc()`, `realloc()`, and `free()`.
2. Monitor memory allocation behavior and identify memory leaks using Valgrind.
3. Develop a program to demonstrate Copy-on-Write behavior after `fork()`.
4. Analyze memory usage before and after modifying data in the child process.

## Files

- `malloc_calloc_realloc.c` - Demonstrates dynamic memory allocation.
- `copy_on_write.c` - Demonstrates Copy-on-Write using `fork()`.
- `practical8.md` - Practical-08 documentation and observations.
- `Screenshot1.png` - Dynamic memory allocation program output.
- `Screenshot2.png` - Valgrind memory leak analysis.
- `Screenshot3.png` - Copy-on-Write program output.
- `Screenshot4.png` - Copy-on-Write child process waiting for memory inspection.

## Tools Used

- GCC
- Linux / Ubuntu
- Valgrind
- `fork()`
- `pmap`

## Valgrind Result

The dynamic memory allocation program was checked using Valgrind.

- Heap blocks in use at exit: 0
- Memory leaks: No leaks
- Errors: 0

## Copy-on-Write Observation

After `fork()`, the parent and child initially have the same virtual memory address for the allocated data. The child changes its value from `100` to `200`, while the parent continues to see `100`. This demonstrates Copy-on-Write behavior.

## Conclusion

The practical demonstrates dynamic memory allocation using `malloc()`, `calloc()`, `realloc()`, and `free()`, memory leak detection using Valgrind, and Copy-on-Write behavior after `fork()`.
