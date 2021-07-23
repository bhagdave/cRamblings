#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int sig) 
{
    printf("You called?\n");
}

int main(int argc, char** argv)
{
    int sig = SIGRTMIN + 1; // Our signal num
    sigset_t mask; // to stop our interrupt handler getting interrupted
    sigemptyset(&mask);
    sigaddset(&mask, sig);
    struct sigaction psa={0};
    psa.sa_handler = signalHandler; // set our signalHandler
    psa.sa_mask = mask;
    sigaction(sig, &psa, NULL);
    pause();
    return(EXIT_SUCCESS);
}
