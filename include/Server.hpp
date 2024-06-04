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

		class PortNotExist: public std::exception{
			char *what() const throw();
		};

		std::string rout(Request &request);
		std::string do_cgi(Request &request);
		Location& select_location(Request &request);
		std::string errorPage(int error_code);
		void send_response(const char *response, int client_fd);
};

#endif