#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if (fork() == 0)
        printf("Hello from child\n");
    else
        printf("Hello from parent\n");
    return(EXIT_SUCCESS);
}
