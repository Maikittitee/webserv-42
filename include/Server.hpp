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
		int					_server_fd;
		std::string			ipAddr; //? listen could be ip address or port

		u_int64_t			listen;
		std::string			server_name;
		std::vector<std::string>	error_page;
		std::map<std::string, Location> _config;
		Mime				_mime;
		char				**_env;
		Server();
		
		~Server();

		bool errorPage(int error_code, Response &response);
};

std::ostream &operator<<(std::ostream &os, std::map<std::string, Location>map);

#endif
