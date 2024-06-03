#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
// # include <stdio.h>
# include <sys/socket.h>	// Socket Programming
// # include <arpa/inet.h>	// inet_ntoa TODO : not allow to use
# include <sys/select.h>	
// # include "Server.hpp"
# include <netinet/in.h>
# include <netdb.h>
// # include <fcntl.h> 

class Client{
	public:
		Client();
		~Client();

		int fd;
		std::string			IPaddr;
		socklen_t			addrLen;
		struct sockaddr_in	addr;

};

#endif