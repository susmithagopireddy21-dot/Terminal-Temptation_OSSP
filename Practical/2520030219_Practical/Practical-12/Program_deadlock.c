
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t r1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t r2 = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

void *thread1(void *arg)
{
    (void)arg;
    pthread_mutex_lock(&r1);

    printf("Thread 1 acquired Resource 1\n");
    fflush(stdout);

    pthread_barrier_wait(&barrier);

    printf("Thread 1 waiting for Resource 2\n");
    fflush(stdout);

    pthread_mutex_lock(&r2);

    printf("Thread 1 acquired both resources\n");
    pthread_mutex_unlock(&r2);
    pthread_mutex_unlock(&r1);

    return NULL;
}

void *thread2(void *arg)
{
    (void)arg;
    pthread_mutex_lock(&r2);

    printf("Thread 2 acquired Resource 2\n");
    fflush(stdout);

    pthread_barrier_wait(&barrier);

    printf("Thread 2 waiting for Resource 1\n");
    fflush(stdout);

    pthread_mutex_lock(&r1);

    printf("Thread 2 acquired both resources\n");
    pthread_mutex_unlock(&r1);
    pthread_mutex_unlock(&r2);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_barrier_init(&barrier, NULL, 2);

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_barrier_destroy(&barrier);
    return 0;
}
