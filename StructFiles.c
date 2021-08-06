#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATAFILE "contacts.dat"

struct contact{
    int id;
    char fname[30];
    char lname[30];
};

int main()
{
    FILE *outfile;
    FILE *infile;
    struct contact input;

    outfile = fopen(DATAFILE, "wb");
    if (outfile == NULL){
        fprintf(stderr, "\nError opening file.\n");
        exit(1);
    }
    
    struct contact input1 = {1, "Dave", "Gill"};
    struct contact input2 = {2, "Eileen", "Gill"};

    fwrite(&input1, sizeof(struct contact), 1, outfile);
    fwrite(&input2, sizeof(struct contact), 1, outfile);

    fclose(outfile);

    infile = fopen(DATAFILE, "rb");
    if (infile == NULL){
        fprintf(stderr, "\nError opening file.\n");
        exit(1);
    }

    while(fread(&input, sizeof(struct contact), 1, infile))
        printf("id = %d name = %s %s\n", input.id, input.fname, input.lname);

    fclose(infile);

    return 0;
}

