#include "Server.hpp"

Server::Server(int port){
	if (port < 0 || port > 65535)
		throw PortNotExist();
	else
		_server_port = port;
	_address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_server_port);

}