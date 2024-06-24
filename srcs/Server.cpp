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

std::string Server::status_code_validate(int status_code)
{
	switch (status_code) {
        case 100: return "100 Continue";
        case 101: return "101 Switching Protocols";
        case 200: return "200 OK";
        case 201: return "201 Created";
        case 202: return "202 Accepted";
        case 203: return "203 Non-Authoritative Information";
        case 204: return "204 No Content";
        case 205: return "205 Reset Content";
        case 206: return "206 Partial Content";
        case 300: return "300 Multiple Choices";
        case 301: return "301 Moved Permanently";
        case 302: return "302 Found";
        case 303: return "303 See Other";
        case 304: return "304 Not Modified";
        case 305: return "305 Use Proxy";
        case 307: return "307 Temporary Redirect";
        case 400: return "400 Bad Request";
        case 401: return "401 Unauthorized";
        case 402: return "402 Payment Required";
        case 403: return "403 Forbidden";
        case 404: return "404 Not Found";
        case 405: return "405 Method Not Allowed";
        case 406: return "406 Not Acceptable";
        case 407: return "407 Proxy Authentication Required";
        case 408: return "408 Request Timeout";
        case 409: return "409 Conflict";
        case 410: return "410 Gone";
        case 411: return "411 Length Required";
        case 412: return "412 Precondition Failed";
        case 413: return "413 Payload Too Large";
        case 414: return "414 URI Too Long";
        case 415: return "415 Unsupported Media Type";
        case 416: return "416 Range Not Satisfiable";
        case 417: return "417 Expectation Failed";
        case 426: return "426 Upgrade Required";
        case 500: return "500 Internal Server Error";
        case 501: return "501 Not Implemented";
        case 502: return "502 Bad Gateway";
        case 503: return "503 Service Unavailable";
        case 504: return "504 Gateway Timeout";
        case 505: return "505 HTTP Version Not Supported";
        default:  return "Unknown Status Code";
    }
}

Response& Server::errorPage(int error_code){ // return resposne
	Response *response = new Response;
	std::stringstream error_code_string;
	char buffer[BUFFERSIZE];
	int	fd;
	int len;

	error_code_string << error_code;
	std::string filename = _config["def"].root + "/" + error_page.back();

	std::cout << "error code: " << error_code_string.str() << std::endl;
	// if (std::count(error_page.begin(), error_page.end() - 1, error_code_string.str()) != 0){
	// 	fd = open(filename.c_str(), O_RDONLY);
	// 	if (fd < 0)
	// 		std::cerr << RED << "Can't open " << filename << RESET << std::endl;
	// 	std::cout << "bp1" << std::endl;
	// 	len = read(fd, buffer, BUFFERSIZE - 1);
	// 	buffer[len] = '\0';
	// 	response->_body.append(buffer, len);
	// 	std::cout << response->_body << std::endl;
	// }
	// else {
	// 	response->_return_code = error_code;
	// 	response->_body = status_code_validate(error_code);
	// }
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
