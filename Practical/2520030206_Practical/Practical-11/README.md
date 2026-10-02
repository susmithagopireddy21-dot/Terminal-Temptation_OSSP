# Practical-11: Multithreaded Counter Application and Synchronization Using POSIX Threads

## 1. Aim

To develop a multithreaded counter application using POSIX threads and demonstrate a race condition when multiple threads update a shared variable concurrently.

The program is then modified using mutex locks to synchronize access to the shared variable. The outputs of both versions are compared and the impact of synchronization is analyzed.

---

## 2. Objectives

The objectives of this practical are:

- To understand POSIX threads.
- To create threads using `pthread_create()`.
- To wait for threads using `pthread_join()`.
- To understand shared data in a multithreaded program.
- To demonstrate a race condition.
- To synchronize shared data using a mutex.
- To use `pthread_mutex_lock()`.
- To use `pthread_mutex_unlock()`.
- To compare synchronized and unsynchronized execution.
- To analyze the effect of synchronization on correctness and performance.

---

## 3. Requirements

### Software Requirements

- Ubuntu / Linux
- GCC compiler
- POSIX Threads library
- Terminal

### Header Files Used

```c
#include <stdio.h>
#include <pthread.h>

4. Introduction

A thread is a lightweight unit of execution within a process. Multiple threads belonging to the same process can execute concurrently and share resources such as global variables and memory.

POSIX Threads, commonly called pthreads, provide functions for creating and managing threads in Linux.

In this practical, four threads are created. Each thread increments a shared counter 100,000 times.

Therefore, the expected final value is:

Number of threads × Increments per thread

4 × 100000 = 400000

The first program does not use synchronization, which demonstrates a race condition.

The second program uses a mutex to ensure that only one thread updates the shared counter at a time.

5. Part A – Race Condition
5.1 Description

In the first program, four threads access the same global variable:

int counter = 0;

Each thread performs:

counter++;

100,000 times.

Since there is no synchronization mechanism, multiple threads may access and modify the counter simultaneously.

This can result in lost updates.

The expected value is:

400000

However, the actual value may be less than the expected value depending on how the threads are scheduled.

This situation is called a race condition.

5.2 Source Code
File: q11.c
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 100000

int counter = 0;

void *increment_counter(void *arg)
{
    for (int i = 0; i < INCREMENTS; i++)
    {
        counter++;
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    printf("Race Condition Demonstration\n");
    printf("Number of threads: %d\n", NUM_THREADS);
    printf("Increments per thread: %d\n", INCREMENTS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %d\n",
           NUM_THREADS * INCREMENTS);

    printf("Actual counter value: %d\n", counter);

    return 0;
}
5.3 Explanation of the Program
Global Counter
int counter = 0;

The counter is shared by all threads.

Thread Function
void *increment_counter(void *arg)

This function is executed by each thread.

Counter Increment
counter++;

Each thread increments the shared counter 100,000 times.

Thread Creation
pthread_create(&threads[i], NULL, increment_counter, NULL);

This creates the threads.

Thread Joining
pthread_join(threads[i], NULL);

This makes the main program wait until each thread completes.

5.4 Compilation

The program is compiled using:

gcc q11.c -o q11 -pthread
5.5 Execution

Run the program using:

./q11

Expected output format:

Race Condition Demonstration
Number of threads: 4
Increments per thread: 100000
Expected counter value: 400000
Actual counter value: <actual value>
Screenshot 1 – Race Condition Program

6. Understanding the Race Condition

The statement:

counter++;

looks like a single operation, but conceptually it involves several steps:

Read the current value of counter.
Add one to the value.
Store the updated value back into counter.

When two threads perform these operations at the same time, they may read the same value.

For example:

Initial counter = 100

Thread 1 reads counter = 100
Thread 2 reads counter = 100

Thread 1 calculates 101
Thread 2 calculates 101

Thread 1 writes 101
Thread 2 writes 101

Two increments were attempted, but the counter increased only once.

This is called a lost update.

7. Repeated Race Condition Test

The race-condition program can be executed multiple times:

./q11
./q11
./q11

The actual result may vary because thread execution order depends on scheduling.

Screenshot 3 – Repeated Race Condition Execution

8. Part B – Mutex Synchronization
8.1 Description

The race condition can be prevented by using a mutex.

A mutex, or mutual exclusion lock, allows only one thread at a time to enter a protected critical section.

In this program, the counter update is protected using:

pthread_mutex_lock(&mutex);

and:

pthread_mutex_unlock(&mutex);

The critical section is:

pthread_mutex_lock(&mutex);

counter++;

pthread_mutex_unlock(&mutex);

Therefore, only one thread can modify the counter at a time.

9. Mutex Program Source Code
File: q11_mutex.c
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTS 100000

int counter = 0;
pthread_mutex_t mutex;

void *increment_counter(void *arg)
{
    for (int i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(&mutex);

        counter++;

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    printf("Mutex Synchronization Demonstration\n");
    printf("Number of threads: %d\n", NUM_THREADS);
    printf("Increments per thread: %d\n", INCREMENTS);

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %d\n",
           NUM_THREADS * INCREMENTS);

    printf("Actual counter value: %d\n", counter);

    pthread_mutex_destroy(&mutex);

    return 0;
}
10. Explanation of the Mutex Program
10.1 Mutex Declaration
pthread_mutex_t mutex;

This declares the mutex used for synchronization.

10.2 Mutex Initialization
pthread_mutex_init(&mutex, NULL);

This initializes the mutex before it is used.

10.3 Locking the Critical Section
pthread_mutex_lock(&mutex);

A thread must acquire the mutex before modifying the shared counter.

If another thread already owns the mutex, the current thread waits.

10.4 Updating the Counter
counter++;

The counter is modified while the mutex is locked.

This prevents another thread from simultaneously modifying the same variable.

10.5 Unlocking the Mutex
pthread_mutex_unlock(&mutex);

After modifying the counter, the thread releases the mutex.

Another waiting thread can then acquire the mutex.

10.6 Destroying the Mutex
pthread_mutex_destroy(&mutex);

The mutex is destroyed after all threads have completed and it is no longer needed.

11. Compilation of Mutex Program

Compile the program using:

gcc q11_mutex.c -o q11_mutex -pthread
12. Execution of Mutex Program

Run:

./q11_mutex

Expected output:

Mutex Synchronization Demonstration
Number of threads: 4
Increments per thread: 100000
Expected counter value: 400000
Actual counter value: 400000
Screenshot 2 – Mutex Program Output

13. Final Mutex Execution

The mutex program can also be executed again to verify that the final result remains consistent.

Screenshot 4 – Final Mutex Execution

14. Comparison Between Both Programs
Feature	Race Condition Version	Mutex Version
Number of threads	4	4
Increments per thread	100000	100000
Expected value	400000	400000
Shared counter	Yes	Yes
Mutex used	No	Yes
pthread_create()	Yes	Yes
pthread_join()	Yes	Yes
pthread_mutex_lock()	No	Yes
pthread_mutex_unlock()	No	Yes
Race condition	Possible	Prevented
Lost updates	Possible	Prevented
Result	May be less than expected	Expected value
Synchronization overhead	None	Present
Program complexity	Lower	Slightly higher
15. Difference in Execution
Race Condition Version
Thread 1 ──┐
Thread 2 ──┤
Thread 3 ──┼──> Shared Counter
Thread 4 ──┘

All threads can access the counter without any protection.

This can cause multiple threads to read and update the same value simultaneously.

Mutex Version
Thread 1 ──> Lock ──> Update ──> Unlock
                                  |
Thread 2 ──> Wait ────────────────┘
              |
              └──> Lock ──> Update ──> Unlock

Only one thread can access the critical section at a time.

16. Impact of Synchronization

Synchronization has an important effect on the correctness of a multithreaded program.

Without Mutex
Threads can access shared data simultaneously.
Race conditions can occur.
Updates can be lost.
The final result may be incorrect.
There is no locking overhead.
With Mutex
Access to the shared variable is controlled.
Race conditions are prevented for the protected operation.
Lost updates are prevented.
The expected result is obtained.
Lock and unlock operations introduce some overhead.
17. Performance Consideration

The race-condition program does not perform mutex operations, so there is no locking overhead.

However, it cannot safely update shared data concurrently.

The mutex version performs additional operations:

pthread_mutex_lock()
pthread_mutex_unlock()

These operations introduce synchronization overhead.

Therefore, synchronization can increase the execution overhead, but it provides correct access to shared data.

In multithreaded applications, protecting shared data is important when multiple threads modify the same resource.

18. Important POSIX Thread Functions
pthread_create()

Creates a new thread.

pthread_create(&threads[i], NULL, increment_counter, NULL);
pthread_join()

Waits for a thread to finish execution.

pthread_join(threads[i], NULL);
pthread_mutex_init()

Initializes a mutex.

pthread_mutex_init(&mutex, NULL);
pthread_mutex_lock()

Locks the mutex.

pthread_mutex_lock(&mutex);
pthread_mutex_unlock()

Unlocks the mutex.

pthread_mutex_unlock(&mutex);
pthread_mutex_destroy()

Destroys the mutex.

pthread_mutex_destroy(&mutex);
19. Output Analysis
Race Condition Program

The expected result is:

400000

The actual result may be lower than 400000 because some increments can be lost due to concurrent access.

Mutex Program

The expected result is:

400000

The actual result should be:

400000

because the counter update is protected by the mutex.

20. Experimental Observation
Observation	Race Condition	Mutex
Threads execute concurrently	Yes	Yes
Shared variable used	Yes	Yes
Critical section protected	No	Yes
Race condition possible	Yes	No for the protected counter update
Lost updates possible	Yes	No
Expected value	400000	400000
Actual value	May vary	400000
Synchronization overhead	No	Yes
21. Conclusion

This practical demonstrates the use of POSIX threads for concurrent programming.

The first program uses pthread_create() and pthread_join() to create and manage multiple threads. Since all threads modify the same counter without synchronization, a race condition can occur and some updates may be lost.

The second program uses a mutex with pthread_mutex_lock() and pthread_mutex_unlock() to protect the shared counter. This ensures that only one thread modifies the counter at a time.

The comparison demonstrates that synchronization improves the correctness and consistency of shared data access, while introducing some additional execution overhead.

Therefore, mutex locks are an important mechanism for safely handling shared resources in multithreaded applications.

22. Practical-11 File Structure
Practical-11/
│
├── README.md
├── q11.c
├── q11_mutex.c
├── Screenshot1.png
├── Screenshot2.png
├── Screenshot3.png
└── Screenshot4.png
23. Commands Used
Create the Practical Directory
mkdir -p Practical-11
cd Practical-11
Compile Race Condition Program
gcc q11.c -o q11 -pthread
Run Race Condition Program
./q11
Compile Mutex Program
gcc q11_mutex.c -o q11_mutex -pthread
Run Mutex Program
./q11_mutex
Run Race Condition Program Multiple Times
./q11
./q11
./q11
24. Final Result

The practical successfully demonstrates:

POSIX thread creation using pthread_create().
Thread synchronization using pthread_join().
A race condition caused by concurrent access to a shared variable.
Mutex initialization using pthread_mutex_init().
Mutual exclusion using pthread_mutex_lock().
Mutex release using pthread_mutex_unlock().
Mutex cleanup using pthread_mutex_destroy().
The difference between unsynchronized and synchronized access.
The impact of synchronization on correctness and execution overhead.
