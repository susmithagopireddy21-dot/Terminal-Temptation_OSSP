# Practical 11: Multithreaded Counter Using POSIX Threads

## Aim
To demonstrate race conditions using POSIX threads and prevent them using mutex locks.

## Concepts
- `pthread_create()` creates threads.
- `pthread_join()` waits for threads to finish.
- `pthread_mutex_lock()` locks the critical section.
- `pthread_mutex_unlock()` releases the lock.

## Execution
Compile using GCC with the `-pthread` option.

```bash
gcc -O0 Program.c -o counter_race -pthread
./counter_race

gcc -O0 Program_mutex.c -o counter_mutex -pthread
./counter_mutex
```

## Output Analysis
Without mutex, the counter value was 1881476 instead of 4000000 because concurrent updates were lost.

With mutex, the counter reached 4000000 because only one thread could update the shared counter at a time.

## Result
The multithreaded counter was implemented successfully. Mutex synchronization prevented race conditions and ensured the correct final counter value.
