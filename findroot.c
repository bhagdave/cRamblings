#include <stdio.h>
#include "root.h"

double p(double);

int main(void){
	double x;
	x = root(p,2.0,3.0);

	printf("%s%.16f\n%s%.16f\n",
		"Aproximate root:", x,
		" Function value: ", p(x));
	return 0;
}

double p(double x){
	return(x * x * x * x * x - 7.0 * x - 3.0);
}
