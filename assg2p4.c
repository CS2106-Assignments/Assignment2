#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int glob;
pthread_t thread[10];
pthread_barrier_t barrier;
void *child(void *t)
{
    // Increment glob by 1, wait for 1 second, then increment by 1
    // again.
    printf("Child %d entering. Glob is currently %d\n", t, glob);
    pthread_mutex_lock(&mutex);
    glob++;
    sleep(1);
    glob++;
    pthread_mutex_unlock(&mutex);
    printf("Child %d exiting. Glob is currently %d\n", t, glob);
    pthread_barrier_wait(&barrier); 
}
int main()
{
    int i;
    glob=0;
    pthread_barrier_init(&barrier, NULL, 11);
    for(i=0; i<10; i++) {
        pthread_create(&thread[i], NULL, child, (void *) i);
    }
    pthread_barrier_wait(&barrier);
    printf("Final value of glob is %d\n", glob);
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    return 0;
}
