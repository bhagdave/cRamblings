/*
 * Simple threading example
 *
 * Needs to be compiled withe -lpthread
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * threadFunction(void *p)
{
    printf("Thread running\n");
}

int main(int argc, char** argv)
{
    pthread_attr_t threadAttr;
    pthread_t pthread;

    int param = 0;

    pthread_attr_init(&threadAttr);
    pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

    int id = pthread_create(&pthread, &threadAttr , threadFunction, &param);
    printf("Thread id:%d\n", id);
    pthread_exit(NULL);
}

