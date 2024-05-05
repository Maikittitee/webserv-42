#ifndef SERVER_HPP
#	define SERVER_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include "Location.hpp"
#	include "Request.hpp"

class Request;

class Location;

class Server{
	public:
		int _client_fd;
		int _server_fd;
		struct sockaddr_in _address;
    	socklen_t _addrlen;
		int _server_port;

		Server(int port);
		~Server();

		class PortNotExist: public std::exception{
			char *what() const throw();
		};

		bool run_server();
		std::string classify_request(Request &request, Location &location);
		void send_response(char *response, int client_fd);
		

		std::string method_get(Request &request)
};

#endif