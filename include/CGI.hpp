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

		Response &rout(Client &client, Server &server);
};


#endif