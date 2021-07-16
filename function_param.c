#include <stdio.h>
#include <math.h>

double f(double);
double sin(double);
double sum_square(double (*)(double), int, int);

int main(void){
	printf("%s%.7f\n%s%.7f\n",
		" First computation: ", sum_square(sin, 2,13),
		"Second Computation: ", sum_square(f,1,1000));
	return 0;
}
double sum_square(double (*f)(double), int m, int n){
	int k;
	double sum = 0.0;

	for (k = m; k <= n; ++k)
		sum += f(k) * f(k);
	return sum;
}

double f(double x){
	return 1.0 / x;
}
