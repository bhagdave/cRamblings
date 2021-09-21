#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

volatile int i;
volatile int j;
volatile int k;
volatile int l;

void * threadOne(void *p)
{
	for (i = 0;; i++){
	}
}

void * threadTwo(void *p)
{
	for (j = 0;; j++){
	}
}

void * threadThree(void *p)
{
	for (k = 0;; k++){
	}
}

void * threadFour(void *p)
{
	for (l = 0;; l++){
	}
}

int main (int argc, char **argv)
{
	cpu_set_t cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(1, &cpuset);

	pthread_t pthreadOne;
	pthread_create(&pthreadOne, NULL, threadOne, NULL);
	pthread_setaffinity_np(pthreadOne, sizeof(cpu_set_t), &cpuset);

	CPU_ZERO(&cpuset);
	CPU_SET(2, &cpuset);

	pthread_t pthreadTwo;
	pthread_create(&pthreadTwo, NULL, threadTwo, NULL);
	pthread_setaffinity_np(pthreadTwo, sizeof(cpu_set_t), &cpuset);

	CPU_ZERO(&cpuset);
	CPU_SET(3, &cpuset);

	pthread_t pthreadThree;
	pthread_create(&pthreadThree, NULL, threadThree, NULL);
	pthread_setaffinity_np(pthreadThree, sizeof(cpu_set_t), &cpuset);

	CPU_ZERO(&cpuset);
	CPU_SET(4, &cpuset);

	pthread_t pthreadFour;
	pthread_create(&pthreadFour, NULL, threadFour, NULL);
	pthread_setaffinity_np(pthreadFour, sizeof(cpu_set_t), &cpuset);

	sleep(5);
	printf("Thread1:%d Thread2:%d Thread3:%d Thread4:%d\n", i, j, k, l);
	return(EXIT_SUCCESS);

}

