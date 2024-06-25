#include "../include/Server.hpp"

Server::Server(void)
{
	server_name = "localhost"; //? server_name
	ipAddr = "0.0.0.0"; //? listen could be ip address or port
	listen = 80;
	error_page.push_back("400");
	error_page.push_back("403");
	error_page.push_back("404");
	error_page.push_back("405");
	error_page.push_back("error.html");

}

Server::Server(int port, char **env){
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

Response& Server::errorPage(int error_code){ // return resposne
	Response *response = new Response;
	std::stringstream error_code_string;
	char buffer[BUFFERSIZE];
	int	fd;
	int len;

	error_code_string << error_code;
	std::string filename = error_page.back();

	std::cout << "error filename: " << filename << std::endl;
	std::cout << "error code: " << error_code_string.str() << std::endl;
	if (count_promax(error_page, error_code_string.str())){
		fd = open(filename.c_str(), O_RDONLY);
		if (fd < 0)
			std::cerr << RED << "Can't open " << filename << RESET << std::endl;
		std::cout << "bp1" << std::endl;
		len = read(fd, buffer, BUFFERSIZE - 1);
		buffer[len] = '\0';
		response->_body.append(buffer, len);
		std::cout << response->_body << std::endl;
	}
	else {
		response->_return_code = error_code;
		response->_body.append(error_code_string.str());
		response->_body.append(" ");
		response->_body.append(status_code_validate(error_code));

	}
	response->_content_type = "text/html";
	return (*response);


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