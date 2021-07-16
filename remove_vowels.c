#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	FILE *ifp, *ofp;
	char c;
	if (argc != 3){
		printf("\n%s%s%s\n\n%s\n%s\n\n",
			"Usage: ", "remove_vowels", " infile outfile",
			"Vowels will be removed."
			"The results will be written in outfile.");
		exit(1);
	}
	ifp = fopen(argv[1],"r");
	ofp = fopen(argv[2],"w");
	while((c=getc(ifp)) !=EOF)
		switch (c){
			case 'a':
			case 'A':
			case 'E':
			case 'e':
			case 'i':
			case 'I':
			case 'o':
			case 'O':
			case 'u':
			case 'U':
				break;
			default:
				printf("%c",c);
				putc(c,ofp);

		}
	fclose(ifp);
	fclose(ofp);
	return 0;
}
