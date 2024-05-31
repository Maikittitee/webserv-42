#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <iostream>
# include <stdio.h>
# include <sys/socket.h>	// Socket Programming
# include <arpa/inet.h>	// inet_ntoa TODO : not allow to use
# include <sys/select.h>	
# include "Server.hpp"
# include <netinet/in.h>
# include <netdb.h>
# include <fcntl.h> 

class Server;

class WebServer{
	public:
		WebServer();
		~WebServer();
		bool	initServer(std::vector<Server> &servers);
		bool	runServer(void);
		bool	downServer(void);

		bool	_setSockAddr(struct addrinfo & sockAddr, Server & serv);
		bool	_setOptSock(int &sockFd);
		std::vector<Server> _servers;					



};

#endif