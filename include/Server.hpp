#ifndef SERVER_HPP
#	define SERVER_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <map>
#	include <stdlib.h>
#	include <unistd.h>
#	include "Location.hpp"
#	include "Request.hpp"
#	include "Mime.hpp"
#	include "Response.hpp"
#	include <time.h>

class Mime;

class Request;

class Location;

class Server{
	public:
		int _client_fd;
		int _server_fd;
		struct sockaddr_in _address;
    	socklen_t _addrlen;
		int _server_port;

		std::map<std::string, Location> _config; 
		
		Mime _mime;

		Server(int port);
		~Server();

		class PortNotExist: public std::exception{
			char *what() const throw();
		};

		bool run_server();
		std::string classify_request(Request &request);
		std::string get_body(Request &request, Location &conf, int &return_code);
		std::string do_cgi(Request &request);
			
		std::string errorPage(int error_code);




		void send_response(const char *response, int client_fd);
		

		std::string method_get(Request &request);
};

#endif