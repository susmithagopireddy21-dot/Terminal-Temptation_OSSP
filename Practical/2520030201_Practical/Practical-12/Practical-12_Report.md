# Practical-12: Producer-Consumer and Deadlock Handling

## Objective

1. Implement the Producer-Consumer problem using POSIX threads and counting semaphores.
2. Evaluate synchronization correctness and throughput for different buffer sizes.
3. Design and demonstrate a deadlock scenario involving multiple threads and shared resources.
4. Identify the four necessary conditions for deadlock.
5. Prevent deadlock using resource ordering.

---

## Part 1: Producer-Consumer Problem

### Implementation

The Producer-Consumer problem was implemented using POSIX threads and counting semaphores.

The program uses:

- `pthread_create()` to create producer and consumer threads.
- `pthread_join()` to wait for both threads.
- `sem_wait()` to wait for available buffer slots/items.
- `sem_post()` to signal available buffer slots/items.
- `pthread_mutex_lock()` and `pthread_mutex_unlock()` to protect shared buffer indexes.
- Circular buffer implementation for storing produced items.

The producer generates 100,000 items and the consumer processes all 100,000 items.

### Synchronization

Two counting semaphores are used:

- `empty` - represents the number of empty buffer slots.
- `full` - represents the number of filled buffer slots.

A mutex protects the shared `in` and `out` indexes.

This prevents simultaneous modification of shared buffer data and ensures correct synchronization between producer and consumer threads.

### Throughput Results

| Buffer Size | Items Processed | Execution Time (seconds) | Throughput (items/second) |
|-------------:|----------------:|-------------------------:|--------------------------:|
| 5 | 100000 | 0.907713 | 110166.98 |
| 10 | 100000 | 0.401760 | 248904.82 |
| 20 | 100000 | 0.162678 | 614711.27 |
| 50 | 100000 | 0.068884 | 1451715.93 |

### Analysis

The results show that throughput increased as the buffer size increased in this experiment.

A small buffer causes the producer and consumer to wait more frequently because the buffer becomes full or empty more quickly. Increasing the buffer provides more space for items and can reduce the frequency of blocking.

The measured execution time and throughput can vary between runs because of operating-system scheduling and system load.

---

## Part 2: Deadlock Demonstration

### Implementation

Two POSIX threads were created with two shared mutex resources:

- Resource 1
- Resource 2

Thread 1 locks Resource 1 and then waits for Resource 2.

Thread 2 locks Resource 2 and then waits for Resource 1.

This creates a circular wait.

### Deadlock Output

```text
Deadlock demonstration
======================
Thread 1: locking Resource 1...
Thread 1: Resource 1 locked.
Thread 2: locking Resource 2...
Thread 2: Resource 2 locked.
Thread 1: waiting for Resource 2...
Thread 2: waiting for Resource 1...
