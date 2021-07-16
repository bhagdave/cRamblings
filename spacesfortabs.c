#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	FILE *ifp, *ofp;
	char c;
	int i;
	if (argc != 3){
		printf("\n%s%s%s\n\n%s\n%s\n\n",
			"Usage: ", argv[0], " infile outfile",
			"Tabs will be replaced by tabs."
			"The results will be written in outfile.");
		exit(1);
	}
	ifp = fopen(argv[1],"r");
	ofp = fopen(argv[2],"w");
	while((c=getc(ifp)) !=EOF)
		switch (c){
			case '\t':
				for (i=0;i<4;++i)
					putc(' ',ofp);
				break;
			default:
				putc(c,ofp);

		}
	fclose(ifp);
	fclose(ofp);
	return 0;
}
