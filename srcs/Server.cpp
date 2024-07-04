#include "../include/Server.hpp"

Server::Server(void):
_server_fd(0),
ipAddr("0.0.0.0"),
listen(80),
server_name("localhost"),
error_page{"400", "403", "404", "405", "error.html"},
_config(),
_mime(),
_env(nullptr)
{

}

Server::Server(int port, char **env):
_server_fd(0),
ipAddr("0.0.0.0"),
listen(80),
server_name("localhost"),
error_page{"400", "403", "404", "405", "error.html"},
_config(),
_mime() 
{
	_env = env;
}

Server::~Server (void) {
	close(_server_fd);
}

bool count_promax(std::vector<std::string> vec, std::string target)
{
	for (int i = 0; i < vec.size(); i++){
		if (vec[i] == target)
			return (true);
	}
	return (false);
}

bool Server::errorPage(int error_code, Response &response){ // return resposne
	std::stringstream error_code_string;
	char buffer[BUFFERSIZE];
	int	fd;
	int len;

	response._body = "";
	error_code_string << error_code;
	std::string filename = error_page.back();

	std::cout << "error filename: " << filename << std::endl;
	std::cout << "error code: " << error_code_string.str() << std::endl;
	if (count_promax(error_page, error_code_string.str())){
		fd = open(filename.c_str(), O_RDONLY);
		if (fd > 0){
			len = read(fd, buffer, BUFFERSIZE - 1);
			buffer[len] = '\0';
			response._body.append(buffer, len);
			std::cout << response._body << std::endl;
			response._content_type = "text/html";
			return (true);
		}
	}

	response._return_code = error_code;
	response._body.append(error_code_string.str());
	response._body.append(" ");
	response._body.append(status_code_validate(error_code));
	response._content_type = "text/html";
	return (false);

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
