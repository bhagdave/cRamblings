#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int sig) 
{
    printf("SIGTERM\n");
}

int main(int argc, char** argv)
{
    sigset_t mask; // to stop our interrupt handler getting interrupted
    sigfillset(&mask);
    struct sigaction psa={0};
    psa.sa_handler = signalHandler; // set our signalHandler
    psa.sa_mask = mask;
    sigaction(SIGTERM, &psa, NULL);
    for (;;) {
    }
    return(EXIT_SUCCESS);
}
