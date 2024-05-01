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
		int _client_fd;
		int _server_fd;
		struct sockaddr_in _address;
    	socklen_t _addrlen;
		int _server_port;

		Server(int port);

		class PortNotExist: public std::exception{
			char *what() const throw();
		};

};

#endif