#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include  <netinet/in.h>

int main(){
	int network_socket;
	int connect_result;
	char server_response [256];

	network_socket = socket(AF_INET,SOCK_STREAM,0);
	printf("Socket is:%d\n",network_socket);

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	connect_result = connect(network_socket,(struct sockaddr *) &server_address,sizeof(server_address));
	if (connect_result == -1){
		printf("Error connecting.\n");
		return connect_result;
	}

	recv(network_socket, &server_response,sizeof(server_response),0);
	printf("Data Received back from sever\n%s\n",
		server_response);
	close(network_socket);
	return 0;
}
