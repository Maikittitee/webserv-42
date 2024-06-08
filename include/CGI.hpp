#ifndef CGI_HPP
#	define CGI_HPP

#	include "Common.hpp"
#	include "Server.hpp"
#	include "Client.hpp"
#	include "Response.hpp"

class Server;

class Client;

class Response;


class CGI{
	public:
		CGI(void);
		~CGI(void);
		
		Response response;

		int rout(Client &client, Server &server);
		std::string readfile(std::string filename);
		std::string readfile(int fd);
		std::string	get_response(void);

	// private:
		bool	_is_allow_method(t_method method, Location &location);
		Location* _select_location(Request & , Server &);
		Location* _compare_location(std::string str, std::map<std::string, Location> &conf);
		std::string _get_only_path(std::string path);
};


#endif