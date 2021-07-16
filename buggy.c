#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char global[5];

int main(void){
	char *dyn;
	char local[5];

	/* first overwrite a buffer just a little bit */
	dyn = malloc(5);
	strcpy(dyn,"12345");
	printf("1: %s\n",dyn);
	free(dyn);

	/* Now overwrite the buffer a lot */
	dyn=malloc(5);
	strcpy(dyn, "12345678");
	printf("2: %s\n", dyn);

	/*Walk pas the beginning of  amalloced local buffer */
	*(dyn -1) = '\0';
	printf("3: %s\n",dyn);

	/*Now gor for a local variable*/
	strcpy(local,"12345");
	printf("4: %s\n", local);
	local[-1]  = '\0';
	printf("5: %s\n", local);

	/*Finally attack global data space*/
	strcpy(global, "12345");
	printf("6: %s\n", global);

	/*aND WRITE OVER THE SPACE BEFORE THE GLOBAL BUFFER*/
	global[-1] = '\0';
	printf("7: %s\n", global);

	return 0;
}
