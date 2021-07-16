#include <stdio.h>
#include "pack.h"

int main(void){
	int x;
	printf("Dave = ");
	x = pack('D', 'a','v','e');
	bit_print(x);
	printf("\n And the value is:%d\n",x);
	return 0;
}
