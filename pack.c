#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pack.h"

int main(int argc, char *argv[]){
	FILE 	*ifp, *ofp;
	int 	i = 0;
	char 	c;
	char 	byte[4];
	int	packed,j;

	if (argc != 2){
		printf("Usage: %s filename\n",argv[0]);
		exit(1);
	}
	ifp = fopen(argv[1],"r");
	strcat(argv[1],".packed");
	ofp = fopen(argv[1],"wb");
	while((c=getc(ifp)) !=EOF){
		byte[i] = c;
		i++;
		if ( i == 4){
			packed = pack(byte[0],byte[1],byte[2],byte[3]);
			i = 0;
			fwrite(&packed,sizeof(packed),1,ofp);
		}
	}
	// deal with the overhang
	if (i > 0){
		for (j = 3; j >= i; --j )
			byte[j]=0;
		packed = pack(byte[0],byte[1],byte[2],byte[3]);
		printf("Byte %s Packed:%d\n",byte,packed);
		i = 0;
		fwrite(&packed,sizeof(packed),1,ofp);
	}


	fclose(ifp);
	fclose(ofp);

	return 0;
}
