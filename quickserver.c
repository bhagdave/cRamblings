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
    struct addrinfo hints, *servinfo;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, "2047", &hints, &servinfo);
    int sockfd = socket(servinfo->ai_family, servinfo->ai_socktype | SOCK_NONBLOCK, servinfo->ai_protocol);

    bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    listen(sockfd, 10);
    struct sockaddr_storage client_addr;
    socklen_t addr_size = sizeof client_addr;
    char buffer[2048];

    char headers[] = "HTTP/1.0 200 OK\r\nServer:XXX\r\nContent-type: text/html\r\n\r\n";
    char html[] = "<html><head><title>Dave Gill</title></head><body><h1>Dave Gill</h1><p>Welcome</p></body></html>\r\n";
    char data[2048] = {0};
    snprintf(data, sizeof data, "%s %s", headers, html);
    for (;;) {
	    int client_fd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_size);
	    if (client_fd > 0){
		    int n = read(client_fd, buffer, 2048);
		    printf("%s", buffer);
		    fflush(stdout);
		    n = write(client_fd, data, strlen(data));
		    close(client_fd);
	    }
    }

    return (EXIT_SUCCESS);
}
