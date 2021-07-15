#include<stdio.h>


int sum(int x, int y){
	return x + y;
}

int factor(int x, int y)
{
	return x * y;
}

int subtract(int x, int y)
{
	return x - y;
}

void printme(int (*fp)(int , int),int x, int y)
{
	int result;

	result = (*fp)(x , y);
	printf("Result is %d\n", result);
}


int main(void)
{
	int result;

	int (*fp)(int, int) = sum;
	printme(fp, 23 , 12);

	fp = &factor;
	printme(fp, 3, 2);

	fp = &subtract;
	printme(fp,23,12);

	return 0;
}

