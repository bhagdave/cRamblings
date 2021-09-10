#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char** argv)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *servinfo;
    int status = getaddrinfo("dave-gill.co.uk", "80", &hints, &servinfo);
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);

    char header[] = "GET /test.php HTTP/1.1\r\nHost:date-gill.co.uk\r\n\r\n";
    int n = write(sockfd, header, strlen(header));
    char buffer[16384];
    n = read(sockfd, buffer, 16384);
    printf("%s", buffer);
    return (EXIT_SUCCESS);
}
