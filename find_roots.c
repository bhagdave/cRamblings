#include <stdio.h>
#include <math.h>
#include "root.h"

#define	N	3

typedef double (*PFDD)(double);

double f1(double x);
double f2(double x);
double f3(double x);

int cnt =0;

int main(void){
	PFDD	g[N] = {&f1, &f2, &f3};
	int 	i;
	int	begin_cnt;
	double	x0;

	for (i =0; i < N; ++i){
		begin_cnt = cnt;
		x0 = root(g[i], -100.0, +100.0);
		printf("For g[%d] (x) an aproximate root"
			" is x0 = %.16f\n", i, x0);
		printf("Fct evaluation at the root"
			" g[%d] (x0) = %.16f\n",i,g[i](x0));
		printf("Number of function calls"
			" to root() = %3d\n\n", cnt - begin_cnt);
	}
	return 0;
}

double f1(double x){
	return (x*x*x - x*x + 2.0*x - 2.0);
}
double f2(double x){
	return (sin(x) - 0.7*x*x*x + 3.0);
}
double f3(double x){
	return (exp(0.13*x) - x*x*x);
}
