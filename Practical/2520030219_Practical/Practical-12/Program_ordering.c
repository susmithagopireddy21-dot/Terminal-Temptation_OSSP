
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t resource[2] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

void *work(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&resource[0]);
    pthread_mutex_lock(&resource[1]);

    printf("Thread %d acquired both resources\n", id);

    pthread_mutex_unlock(&resource[1]);
    pthread_mutex_unlock(&resource[0]);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    pthread_create(&t1, NULL, work, &id1);
    pthread_create(&t2, NULL, work, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&resource[0]);
    pthread_mutex_destroy(&resource[1]);

    printf("Deadlock prevented using resource ordering\n");

    return 0;
}
