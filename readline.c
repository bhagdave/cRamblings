#include <ctype.h>
#include <stdio.h>
#include "readline.h"

int read_line(char string[], int n)
{
    int key, i = 0;

    while(isspace(key = getchar()))
        ;

    while(key != '\n'){
        if (i < n)
            string[i++] = key
        key = getchar();
    }
    string[i] = '\0'; // dont forget the terminator
    return i; // send back the number of keys entered
}
