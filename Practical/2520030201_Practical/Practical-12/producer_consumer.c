#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define ITEMS 100000

int *buffer;
int buffer_size;

int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    for (int i = 0; i < ITEMS; i++)
    {
        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        in = (in + 1) % buffer_size;

        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg)
{
    long long sum = 0;

    for (int i = 0; i < ITEMS; i++)
    {
        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        sum += buffer[out];
        out = (out + 1) % buffer_size;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);
    }

    return NULL;
}

void run_test(int size)
{
    pthread_t producer_thread;
    pthread_t consumer_thread;

    buffer_size = size;
    buffer = malloc(buffer_size * sizeof(int));

    in = 0;
    out = 0;

    sem_init(&empty, 0, buffer_size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    clock_t start = clock();

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    clock_t end = clock();

    double time_taken =
        (double)(end - start) / CLOCKS_PER_SEC;

    double throughput = ITEMS / time_taken;

    printf("Buffer size: %d\n", buffer_size);
    printf("Items processed: %d\n", ITEMS);
    printf("Execution time: %.6f seconds\n", time_taken);
    printf("Throughput: %.2f items/second\n", throughput);
    printf("-----------------------------------\n");

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    free(buffer);
}

int main()
{
    printf("Producer-Consumer using POSIX Threads and Counting Semaphores\n");
    printf("=============================================================\n");

    run_test(5);
    run_test(10);
    run_test(20);
    run_test(50);

    return 0;
}
