#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define ITEMS 10000
#define NUM_TESTS 3

int buffer_size;
int *buffer;

int in = 0;
int out = 0;
int produced_count = 0;
int consumed_count = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    for (int i = 1; i <= ITEMS; i++)
    {
        sem_wait(&empty);

        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        in = (in + 1) % buffer_size;
        produced_count++;

        pthread_mutex_unlock(&mutex);

        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 1; i <= ITEMS; i++)
    {
        sem_wait(&full);

        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        out = (out + 1) % buffer_size;
        consumed_count++;

        pthread_mutex_unlock(&mutex);

        sem_post(&empty);

        (void)item;
    }

    return NULL;
}

void run_test(int size)
{
    pthread_t producer_thread;
    pthread_t consumer_thread;

    buffer_size = size;
    buffer = malloc(buffer_size * sizeof(int));

    if (buffer == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    in = 0;
    out = 0;
    produced_count = 0;
    consumed_count = 0;

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

    printf("\nBuffer Size: %d\n", buffer_size);
    printf("Produced Items: %d\n", produced_count);
    printf("Consumed Items: %d\n", consumed_count);
    printf("Execution Time: %.6f seconds\n", time_taken);
    printf("Throughput: %.2f items/second\n", throughput);

    if (produced_count == ITEMS && consumed_count == ITEMS)
        printf("Synchronization Correctness: PASS\n");
    else
        printf("Synchronization Correctness: FAIL\n");

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    free(buffer);
}

int main()
{
    int buffer_sizes[NUM_TESTS] = {3, 5, 10};

    printf("========================================\n");
    printf("Producer-Consumer Synchronization Test\n");
    printf("Items Produced/Consumed: %d\n", ITEMS);
    printf("========================================\n");

    for (int i = 0; i < NUM_TESTS; i++)
    {
        run_test(buffer_sizes[i]);
    }

    return 0;
}
