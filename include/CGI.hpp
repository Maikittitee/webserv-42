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

		bool rout(Client &client, Server &server);
		std::string	get_response(void);

	private:
		bool	_is_allow_method(t_method method, Server &server);
};


#endif