#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Common.hpp"

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