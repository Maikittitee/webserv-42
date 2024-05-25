#include "../include/Server.hpp"

Server::Server(int port){
	if (port < 0 || port > 65535)
		throw PortNotExist();
	else
		_server_port = port;
	_address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(_server_port);
	_addrlen = sizeof(_address);
}

Server::~Server (void) {
	close(_client_fd);
	close(_server_fd);
}

bool Server::run_server(void)
{
	_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_fd < 0){
		perror("socket failed");
	}

	if (bind(_server_fd, (struct sockaddr*)&_address, sizeof(_address)) < 0){
		perror("bind failed");
	}

	if (listen(_server_fd, 3) < 0){
		perror("listen failed");
	}

	_client_fd = accept(_server_fd, (struct sockaddr*)&_address, &_addrlen);
	if (_client_fd < 0){
		perror("accept failed");
	}
	return (true);
}

void Server::send_response(const char *response, int client_fd)
{
	send(client_fd, response, strlen(response), 0);
}

char *Server::PortNotExist::what() const throw(){
	return ("Your port is not in range of 0 - 65535");
}
std::string Server::errorPage(int error_code)
{
	std::string body;

	switch (error_code){
		case 404:
			readFile(body, "docs/error.html");
		case 405:
			readFile(body, "docs/error.html");
	}
	return (body);
}

std::string Server::do_cgi(Request &request)
{
	// pass
	return ("cgiiiiii");
}

std::string Server::rout(Request &request)
{
	Response response;

	// find config;

	// 	หา config location ของ request (ถ้าไม่มีส่ง default config ไป)

	// send request and target config to response;
	response.receive_request(request, /* mock -> */ _config.begin()->second);
	if (response._return_code >= 400) // incase error => redirect to error file
		response.set_body(errorPage(response._return_code));
	if (response._return_code < 0) // incase cgi => redirect to do cgi
		response.set_body(do_cgi(request));
	response.genarate_header();
	return (response.get_response_text());	
}