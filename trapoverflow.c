#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <limits.h>
#include <setjmp.h>

/*
 * Needs to be compiled on GCC with -ftrapv
*/

static jmp_buf jumpBuffer;

void signalHandler(int sig)
{
    printf("Overflow detected\n");
    siglongjmp(jumpBuffer, 1);
}

int main(int argc, char ** argv){
    sigset_t mask;
    sigfillset(&mask);
    struct sigaction psa={0};
    psa.sa_handler = signalHandler;
    psa.sa_mask = mask;

    int a = INT_MAX;
    int b = INT_MAX;
    if (sigsetjmp(jumpBuffer, 0)){
        printf("Overflow\n");
        printf("%d \n", a);
    } else {
        sigaction(SIGABRT, &psa, NULL);
        int result = a + b;
        printf("%d \n", result);
    }
    return (EXIT_SUCCESS);
}
