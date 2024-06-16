#ifndef CGI_HPP
#	define CGI_HPP

#	include "Common.hpp"
#	include "Server.hpp"
#	include "Client.hpp"
#	include "Response.hpp"
#	include "Mime.hpp"

class Server;

class Client;

class Response;

class Mime;

class CGI{
	public:
		CGI(void);
		~CGI(void);
		
		Response response;
		Mime		_mime;

		int rout(Client &client, Server &server);
		Response& readfile(Client &client, Server &server, int return_code);
		std::string	get_response(void);

	// private:
		bool	_is_allow_method(t_method method, Location &location);
		Location* _select_location(Request & , Server &);
		Location* _compare_location(std::string str, std::map<std::string, Location> &conf);
		std::string _get_only_path(std::string path);
		bool _is_path(std::string path);
		int		_delete_method(Client &client);
};


#endif