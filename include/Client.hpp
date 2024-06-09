#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Common.hpp"
# include "Server.hpp"
# include "Request.hpp"

class Server;
class Request;

class Client
{
	public:
		Client();
		~Client();

		int 				fd;
		socklen_t			addrLen;
		struct sockaddr_in	addr;
	
		char				buffer[BUFFERSIZE];

		std::string			rawReqMsg;
		std::string			IPaddr;

		ssize_t				bufSize;

		Server 				*server;
		Request				*request;
};

#endif