#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t threadMutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  threadCondition = PTHREAD_COND_INITIALIZER;

int threadId = 0;
int counter;

void * threadFunction1(void *p) 
{
    int top = rand() % 10;
    pthread_mutex_lock(&threadMutex);
    threadId = 1;
    for (int j =0; j < top; j++){
        counter++;
        sleep(rand() % 5);
    }
    pthread_cond_signal(&threadCondition);
    pthread_mutex_unlock(&threadMutex);
}


void * threadFunction2(void *p) 
{
    int top = rand() % 10;
    pthread_mutex_lock(&threadMutex);
    threadId = 2;
    for (int j =0; j < top; j++){
        counter++;
        sleep(rand() % 5);
    }
    pthread_cond_signal(&threadCondition);
    pthread_mutex_unlock(&threadMutex);
}

void * threadFunction3(void *p) 
{
    int top = rand() % 10;
    pthread_mutex_lock(&threadMutex);
    threadId = 3;
    for (int j =0; j < top; j++){
        counter++;
        sleep(rand() % 5);
    }
    pthread_cond_signal(&threadCondition);
    pthread_mutex_unlock(&threadMutex);
}

int main(int argc, char** argv)
{
    srand(time(0));
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_t pthread3;

    pthread_create(&pthread1, NULL, threadFunction1, NULL);
    pthread_create(&pthread2, NULL, threadFunction2, NULL);
    pthread_create(&pthread3, NULL, threadFunction3, NULL);

    pthread_mutex_lock(&threadMutex);
    while (threadId == 0) pthread_cond_wait(&threadCondition, &threadMutex);

    printf("First Thread:%d Counter:%d\n", threadId, counter);
    pthread_mutex_unlock(&threadMutex);
    return(EXIT_SUCCESS);
}
