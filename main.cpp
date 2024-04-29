#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 8080

int	main()
{
	struct sockaddr_in address;
	char buffer[1024];
    socklen_t addrlen = sizeof(address);

	// create a socket with domain local and type TCP socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket failed");
		exit(1);
	}

	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr*)&address, sizeof(address) < 0)){
		perror("bind failed");
		exit(1);
	}

	// waiting for client to make a connection with maximum queue is 3.
	if (listen(sockfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

	int new_socket;

	if ((new_socket = accept(sockfd, (struct sockaddr*)&address, &addrlen))< 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

	read(new_socket, buffer, 1024 - 1);

	printf("%s\n", buffer);
    send(new_socket, "hello", 5, 0);
    printf("Hello message sent\n");
 
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    close(sockfd);
    return 0;










	


}