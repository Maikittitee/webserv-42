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
		bool				pipe_available;
		int 				child_pid;
		int 				pipe_fd[2];
		std::string			IPaddr;
		socklen_t			addrLen;
		struct sockaddr_in	addr;
	
		char				buffer[BUFFERSIZE];

		std::string			rawReqMsg;

		ssize_t				bufSize;

		Server 				*server;
		Request				*request;
		Location			*location;


};

#endif