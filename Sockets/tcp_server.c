#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include  <netinet/in.h>

int main(){
	char server_message[256] = "You have reached the dave server";
	int server_socket;
	int client_socket;
	char client_response [256];

	server_socket = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket is:%d\n",server_socket);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
	listen(server_socket,5);

	client_socket = accept(server_socket, NULL, NULL);

	recv(client_socket, &client_response,sizeof(client_response),0);
	printf("Data Received back from client\n%s\n",
		client_response);
	send(client_socket,server_message,sizeof(server_message),0);
	close(server_socket);

	return 0;
}
