#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define	KEYSIZE 16

void merge(int *, int *, int *, int , int );
void mergesort(int *, int);

int main(void){
	int i, key[] = {4,3,1,67,55,8,0,4,-5,37,7,4,2,9,1,-1};

	mergesort(key,KEYSIZE);
	printf("After mergesort.\n");
	for( i =0; i < KEYSIZE; ++i)
		printf("%4d", key[i]);
	putchar('\n');
	return 0;
}


void mergesort(int key[], int n){
	int j, k, m , *w;
	for (m=1; m < n; m*=2)
		;
	if (m != n){
		printf("ERROR: Array size is not a power of 2 - bye!\n");
		exit(1);
	}
	w = calloc(n, sizeof(int));
	assert(w != NULL);
	for (k = 1; k < n; k *= 2){
		for (j = 0; j < n - k ; j += 2 * k)
			merge(key +j, key + j + k, w + j, k ,k);
		for (j = 0; j < n; ++j)
			key[j] = w[j];
	}
	free(w);
}



void merge(int a[], int b[], int c[], int m, int n){
	int i=0, j=0, k=0;
	while(i < m && j < n)
		if (a[i] < b[j])
			c[k++] = a[i++];
		else
			c[k++] = b[j++];
	while ( i < m )
		c[k++] = a[i++];
	while ( j < n )
		c[k++] = b[j++];
}
