#ifndef SERVER_HPP
#	define SERVER_HPP

#	include "Common.hpp"
#	include "Location.hpp"
#	include "Request.hpp"
#	include "Mime.hpp"
#	include "Response.hpp"

class Mime;

class Request;

class Location;

class Server{
	public:
		int _server_fd;
		std::string							name; //? server_name
		std::string							ipAddr; //? listen could be ip address or port
		int									port; //? listen
		
		std::map<std::string, Location> _config; 
		Mime _mime;
		char **_env;
		Server();
		Server(int port, char **env);
		~Server();

		std::string errorPage(int error_code);
};

std::ostream &operator<<(std::ostream &os, std::map<std::string, Location>map);

#endif