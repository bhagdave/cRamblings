#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	NCALLS	10000
#define	NCOLS	9
#define	NLINES	5

int main(void){
	int 	i,val;
	long	begin, diff, end;

	begin=time(NULL);
	srand(time(NULL));
	printf("TIMING TEST: %d calls to rand()\n", NCALLS);
	for (i=0; i< NCALLS; ++i){
		val = rand();
		if (i < NCOLS * NLINES){
			if (i % NCOLS ==0)
				putchar('\n');
			printf("%12d",val);
		}
		if (i == NCOLS * NLINES)
			printf("\n%12s\n\n",".......");
	}
	end=time(NULL);
	diff = end - begin;
	printf("%s%ld\n%s%ld\n%s%ld\n%s%.10f\n",
		"          end time: ", end,
		"        begin time: ", begin,
		"      elapsed time: ", diff,
		"time for each call:",(double) diff/NCALLS);

	return 0;
}
