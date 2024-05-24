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
	
}

std::string Server::get_body(Request &request, Location &conf, int &return_code)
{
	std::string body;
	
	// is allow mathod => N:405
	
	//	is path => add index
	
	//	is access file => N:404
	if (access(request._path.c_str(), F_OK) < 0){
		return_code = 404;
		return (errorPage(404));
	}


	//is cgi => y:do cgi
	if (conf.cgiPass)
		body = do_cgi(request);
	else{
		std::cout << "readfile" << std::endl;;
		readFile(body, request._path.c_str());
	}
	replace_str(body, "\n", "\r\n");
	if (strlen(body.c_str()) > conf.cliBodySize){
		return_code = 413;
		return (errorPage(413));
	}
	return_code = 200;	
	return (body);
}

std::string Server::classify_request(Request &request)
{
	// std::string response;
	std::string body;
	int			return_code;
	
	// find config associate with the request
	auto conf = _config.find(request._path);

	// is_path match in config; => N:404
	if (conf == _config.end()){
		body = errorPage(404);
		return_code = 404;
	}
	else
		body = get_body(request, conf->second, return_code);

	Response response = Response(return_code, body);
	response.genarate_header();
	// response = create_response(body, request, conf->second);
	return (response.get_response_text());	
}


// should be on Response
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
std::string Server::get_date(void)
{
	char buf[1000];
	std::string ret = "";
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);

	int i = 0;
	while (buf[i])
	{
		ret += buf[i];
		i++;
	}
	std::cout << "Now time is " << buf << std::endl;
	return (ret);


}
// mocking up
std::string Server::create_response(std::string body, Request &request, Location &location)
{
	int content_length = strlen(body.c_str());
	std::string content_type = _mime.get_mime_type(request._path);
	std::string response;
	
	response = request._http_version + " " + std::to_string(location.ret.code) + " " + location.ret.text + "\r\n";
	response += "Content-Type: " + content_type + "\r\n";
	response += "Date: " + get_date() + "\r\n";
	response += "Content-Length: " + std::to_string(content_length) + "\r\n";

	
	response += "\r\n";
	response += body;

	std::cout << "+-+-+-" << std::endl;
	std::cout << response;

	return (response);
}