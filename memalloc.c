#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill_array(int *a, int n);
void prn_array(int *a, int n);
int sum_array(int *a, int n);

int main(void){
	int *a, n;

	srand(time(NULL));
	printf("Builds and break array.\n");
	for( ; ; ){
		printf("Input n: ");
		scanf("%d", &n);
		if (n < 1){
			printf("\nBye!\n\n");
			exit(1);
		}
		putchar('\n');
		a = calloc(n, sizeof(int));
		fill_array(a,n);
		prn_array(a,n);
		printf("Sum of the elements = %d\n\n", sum_array(a,n));
		free(a);
	}
	return 0;
}

void fill_array(int *a, int n){
	int i;
	for (i =0; i < n; ++i){
		a[i] = rand() % 19 -9;
	}
}

void prn_array(int *a, int n){
	int i;
	printf("a = [");
	for(i=0; i < n-1; ++i)
		printf("%d,  ", a[i]);
	printf("%d]\n",a[n-1]);
}

int sum_array(int *a, int n){
	int i, sum = 0;
	for(i=0;i<n;++i){
		sum += a[i];
	}
	return sum;
}
