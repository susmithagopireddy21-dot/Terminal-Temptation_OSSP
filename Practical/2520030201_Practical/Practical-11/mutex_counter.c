#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5
#define INCREMENTS 100000

int counter = 0;

pthread_mutex_t lock;

void *increment_counter(void *arg)
{
    for (int i = 0; i < INCREMENTS; i++)
    {
        pthread_mutex_lock(&lock);

        counter++;

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);

    printf("Starting mutex-synchronized program...\n");

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

    pthread_mutex_destroy(&lock);

    return 0;
}
