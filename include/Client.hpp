#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Common.hpp"
# include "Server.hpp"
# include "Request.hpp"

class Server;

class Request;

class Client{
	public:
		Client();
		~Client();

		int 				fd;
		std::string			IPaddr;
		socklen_t			addrLen;
		struct sockaddr_in	addr;
		Server 				*server;
		Request				*request;
		Location			*location;

};

#endif