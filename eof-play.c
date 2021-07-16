#include <stdio.h>

void main(){
    int c;

    printf("The value of EOF is %d\n", EOF);
    c = getchar() != EOF;
    printf("The avlue of c is %d\n", c);
}
