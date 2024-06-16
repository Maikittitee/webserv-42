#include "../include/Server.hpp"

Server::Server(void)
{
	server_name = "localhost"; //? server_name
	ipAddr = "0.0.0.0"; //? listen could be ip address or port
	listen = 80;

}

Server::Server(int port, char **env){
	_env = env;
}

Server::~Server (void) {
	close(_server_fd);
}

Response& Server::errorPage(int error_code){
	Response response;

	if (std::count(error_page.begin(), error_page.end() - 1, error_code));
}

std::ostream &operator<<(std::ostream &os, std::map<std::string, Location>map)
{
	std::map<std::string, Location>::const_iterator it;
	for (it = map.begin(); it != map.end(); it++)
	{
		os << it->first << std::endl;
		os << it->second << std::endl;
	}
	return (os);
}