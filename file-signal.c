#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>

int main(int argc, char** argv)
{
    sigset_t mask; // to stop our interrupt handler getting interrupted
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    int count;
    int fd=signalfd(-1,&mask,0);
    struct signalfd_siginfo buffer[10];
    for(;;){
        count = read(fd, &buffer, 10*sizeof(struct signalfd_siginfo));
        printf("SIGINT %d\n", count);
    }
    return(EXIT_SUCCESS);
}
