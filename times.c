#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
	int i;
	long j = strtol(argv[1],NULL,10);
	for (i=1;i<13;++i){
		printf("%d times %ld is %ld\n",i,j,i*j);
	}
}
