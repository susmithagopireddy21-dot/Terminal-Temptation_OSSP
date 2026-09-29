# Practical-11: Multithreaded Counter and Race Condition

## Objective

To develop a multithreaded counter application using POSIX threads and demonstrate a race condition when multiple threads update a shared variable concurrently.

The program is then modified using mutex locks to synchronize access to the shared variable and compare the results.

---

## Part 1: Race Condition

### Concepts Used

- POSIX threads using `pthread_create()`
- Waiting for threads using `pthread_join()`
- Shared global variable
- Concurrent access without synchronization
- Race condition

### Program

The program creates 5 threads. Each thread increments the shared `counter` 100000 times.

Since all threads access the same variable without a mutex, multiple threads can read and update the variable at the same time.

### Compilation

```bash
gcc race_condition.c -o race_condition -pthread
