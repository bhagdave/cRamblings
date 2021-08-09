/*
 * A very simple service
 *
 * requires libystsemd-dev
 * compiles with gcc simplervice.c -lsystemd
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <systemd/sd-daemon.h>

int main(int argc, char** argv)
{
    sd_notify(0,"READY=1");
    printf("Hello systemd world \n");
    fflush(NULL);
    sleep(rand()%7+1);

    return(EXIT_SUCCESS);
}
