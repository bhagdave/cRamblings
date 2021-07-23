#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int sig = SIGRTMIN + 1; // Our signal num
    sigset_t mask; // to stop our interrupt handler getting interrupted
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    
    sigemptyset(&mask);
    sigaddset(&mask, sig);

    int signo;
    for(;;){
        sigwait(&mask, &signo);
        printf("Ok I am done. Received %d\n", signo);
    }
    return(EXIT_SUCCESS);
}
