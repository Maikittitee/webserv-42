#ifndef SERVER_HPP
#	define SERVER_HPP

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
#	include "Location.hpp"
#	include "Request.hpp"
#	include "Mime.hpp"
#	include "Response.hpp"
#	include <time.h>

// struct dfconf;
// typedef struct t_dfconf s_dfconf;

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
	std::vector<std::string> limit_except;
	std::vector<std::string> error_page;
	// int			locate;  // true false
} t_dfconf ;

class Server{
	public:
		int					_client_fd;
		int					_server_fd;
		struct sockaddr_in	_address;
    	socklen_t			_addrlen;
		std::vector<int>	_server_port;
		

		// keep key and value of default conf
		t_dfconf df;
		// t_dfconf df;

		// std::map<std::string, t_test > tmp;
		

		//Default
		// std::map<std::string, dfconf> df_config;
		
		//Location
		std::map<std::string, Location> _config;
		// p_dfconf			df; 
		Mime				_mime;
		char				**_env;
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