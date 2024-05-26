#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/Server.hpp"
#include "../include/Location.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"

Request* mock_file_request(void)
{
	Request *ret = new Request();

	// for example
	// GET /docs/test.html HTTP/1.1
	ret->_method = GET;
	ret->_path = "docs/test.html";
	ret->_http_version = "HTTP/1.1";

	ret->_body = "";
	return (ret);

}

std::map<std::string, Location> mock_location(void)
{
	Location def;
	def.cliBodySize = 2000;
	def.root = "docs/myPage";
	def.index.insert(def.index.end(), "index.html");
	def.index.insert(def.index.end(), "index.htm");
	def.allowMethod.insert(def.allowMethod.end(), GET);
	def.allowMethod.insert(def.allowMethod.end(), POST);
	def.allowMethod.insert(def.allowMethod.end(), DELETE);
	def.autoIndex = false;
	def.cgiPass = false;
	def.ret.have = false;

	
	Location r(def);
	Location redir(def);
	
	redir.ret = (return_t){true, 301, "/sample.html"};
	
	Location blog(def);
	blog.autoIndex = true;

	Location images(def);
	images.index.clear();
	images.index.insert(images.index.end(), "Cat03.jpg");
	images.index.insert(images.index.end(), "test.png");

	Location cgi_bin(def);
	cgi_bin.autoIndex = true;
	cgi_bin.cliBodySize = 5000;





}



// int	main()
// {
// 	Server server(8384);
// 	Request *req = mock_file_request();
// 	Location *loc = mock_location();

// 	server.classify_request(*req, *loc);
// 	// std::cout << "bp2\n";


// }

int	main()
{
	Server server(8384);
	char buffer[1024];
	Request *req = mock_file_request();
	Location *loc = mock_location();
	server._config.insert(std::pair<std::string, Location>("docs/test.html", *loc));
	// char *msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\nContent-Length: 214\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Hello World</title>\n</head>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>\n\0";

	// parsing config here

	server.run_server();
	read(server._client_fd, buffer, 1024 - 1);

	// parsing request here

	printf("this is request message\n");
	printf("%s\n", buffer);

	// cgi & responce here
	std::string response = server.rout(*req);
	server.send_response(response.c_str(), server._client_fd);
	printf("send response\n");

    return 0;
}
