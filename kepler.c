#include <stdio.h>
#include <math.h>
#include "root.h"

#define	E	0.5
#define	M	2.2

double kepler(double x);

int main (void){
	double	x;
	x = root(kepler, -100.0, +100.0);
	printf("%s%.16f\n%s%.16f\n",
		"Aproximate root: ", x,
		" Function value:", kepler(x));
	return 0;
}
double kepler(double x){
	return (x - E * sin(x) - M);
}
