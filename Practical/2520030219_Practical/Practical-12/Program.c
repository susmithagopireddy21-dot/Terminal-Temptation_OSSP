
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define ITEMS 100000

int *buffer;
int size;
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg)
{
(void)arg;
    for (int i = 0; i < ITEMS; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        in = (in + 1) % size;

        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg)
{
(void)arg;
    for (int i = 0; i < ITEMS; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        (void)item;
        out = (out + 1) % size;

        sem_post(&mutex);
        sem_post(&empty);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || atoi(argv[1]) <= 0)
    {
        printf("Usage: %s <buffer_size>\n", argv[0]);
        return 1;
    }

    size = atoi(argv[1]);
    buffer = malloc(size * sizeof(int));

    if (buffer == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    pthread_t p, c;

    sem_init(&empty, 0, size);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Buffer size: %d\n", size);
    printf("Items produced and consumed: %d\n", ITEMS);
    printf("Time taken: %.6f seconds\n", elapsed);
    printf("Throughput: %.0f items/second\n", ITEMS / elapsed);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    free(buffer);

    return 0;
}
