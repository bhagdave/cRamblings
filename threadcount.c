#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int i;
pthread_mutex_t counterMutex=PTHREAD_MUTEX_INITIALIZER;

void * counter(void *p) 
{
    for (int j =0; j < 500000; j++){
        pthread_mutex_lock(&counterMutex);
        i++;
        pthread_mutex_unlock(&counterMutex);
    }
    return &i;
}

int main(int argc, char** argv)
{
    pthread_t pthread1;
    pthread_t pthread2;

    int threadId1 = pthread_create(&pthread1, NULL, &counter, NULL);
    int threadId2 = pthread_create(&pthread2, NULL, &counter, NULL);

    void *return1;
    void *return2;

    pthread_join(pthread1, &return1);
    pthread_join(pthread2, &return2);

    printf("%d\n", *(int *) return1);
    printf("%d\n", *(int *) return2);

    return (EXIT_SUCCESS);
}
