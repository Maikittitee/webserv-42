#ifndef SERVER_HPP
#	define SERVER_HPP

<<<<<<< HEAD
#	include <iostream>
#	include <vector>
#	include <string>
#	include <string.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <map>
#	include <stdlib.h>
#	include <unistd.h>
=======
#	include "Common.hpp"
>>>>>>> 12e46af436804ed8672743987dc786f438bb9bf8
#	include "Location.hpp"
#	include "Request.hpp"
#	include "Mime.hpp"
#	include "Response.hpp"

class Mime;

class Request;

class Location;

typedef struct s_dfconf
{
	uint64_t	cliBodySize;
	uint64_t	listen;
	std::string	server_name;
	std::string	root;
		
	std::vector<std::string> index;
	std::vector<std::string> error_page;
} t_dfconf ;

class Server{
	public:
		int					_client_fd;
		int					_server_fd;
		struct sockaddr_in	_address;
    	socklen_t			_addrlen;

		u_int64_t			listen;
		std::string			server_name;
		std::vector<std::string>	error_page;
		
		std::map<std::string, Location> _config;
		Mime				_mime;
		char				**_env;
		Server();
		Server(int port, char **env);
		~Server();

		std::string errorPage(int error_code);
};

std::ostream &operator<<(std::ostream &os, std::map<std::string, Location>map);

#endif