#include <limits.h>
#include <stdio.h>

void bit_print(int);

int main(void){
	bit_print(45692);
	printf("\n");
	return 0;
}

void bit_print(int a){
	int i;
	int n = sizeof(int) * CHAR_BIT;
	int mask = 1 << (n - 1);

	for (i = 1; i <= n; ++i){
		putchar(((a & mask) == 0) ? '0' : '1');
		a <<= 1;
		if (i % CHAR_BIT == 0 && i < n)
			putchar(' ');
	}
}
