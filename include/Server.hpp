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
		std::vector<int> _server_port;
		std::map<std::string, Location> _config; 
		Mime _mime;
		char **_env;
		Server(int port, char **env);
		~Server();

		class PortNotExist: public std::exception{
			char *what() const throw();
		};

		bool run_server();
		std::string rout(Request &request);
		std::string do_cgi(Request &request);
		Location& select_location(Request &request);
		std::string errorPage(int error_code);
		void send_response(const char *response, int client_fd);
		std::string method_get(Request &request);
};

#endif