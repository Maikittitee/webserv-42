#ifndef SERVER_HPP
#	define SERVER_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>

class Server{
	public:
		int client_fd;
		int server_fd;

		struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);


};

#endif