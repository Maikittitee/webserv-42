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
	ret->_method = GET;
	// ret->_path = "/cgi-bin/hello.py";
	ret->_path = "/test.html";
	ret->_http_version = "HTTP/1.1";

	ret->_body = "";
	return (ret);

}

std::map<std::string, Location> mock_location(void)
{
	Location def;
	def.cliBodySize = 2000;
	def.root = "docs";
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
	cgi_bin.cgiPass = true;
	cgi_bin.cliBodySize = 5000;

	std::map<std::string, Location> ret;

	ret.insert(std::pair<std::string, Location>("def", def));	
	ret.insert(std::pair<std::string, Location>("/", r));	
	ret.insert(std::pair<std::string, Location>("/redir/", redir));	
	ret.insert(std::pair<std::string, Location>("/blog/", blog));	
	ret.insert(std::pair<std::string, Location>("/images/", images));	
	ret.insert(std::pair<std::string, Location>("/cgi-bin/", cgi_bin));	

	return (ret);

}



<<<<<<< HEAD
// int	main()
// {
// 	Server server(8384);
// 	Request *req = mock_file_request();
// 	Location *loc = mock_location();

// 	server.classify_request(*req, *loc);
// 	// std::cout << "bp2\n";


// }

// int	main(int ac, char **av)
// {
	// Server server(8384);
	// char buffer[1024];
	// Request *req = mock_file_request();
	// Location *loc = mock_location();
	// char *msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\nContent-Length: 214\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Hello World</title>\n</head>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>\n\0";
=======
int	main(int ac, char **av, char **env)
{
	Server server(8384, env);
	char buffer[1024];
	Request *req = mock_file_request();
	server._config = mock_location();
>>>>>>> c69c8bf033e6cc4b41c283586de6e42f285f1806

	std::cout << "bp1" << std::endl;
	// parsing config here
	// parsing_config(server , ac, av);
	// server.run_server();
	// read(server._client_fd, buffer, 1024 - 1);

<<<<<<< HEAD
	// // parsing request here
=======
	if (server.run_server())
		std::cout << "run server ok" << std::endl;
	std::cout << "ye mae" << std::endl;
	read(server._client_fd, buffer, 1024 - 1);
>>>>>>> c69c8bf033e6cc4b41c283586de6e42f285f1806

	// printf("this is request message\n");
	// printf("%s\n", buffer);

	// // cgi & responce here
	// std::string response = server.classify_request(*req, *loc);
	// server.send_response(response.c_str(), server._client_fd);
	// printf("send response\n");

<<<<<<< HEAD
    // return 0;
// }
=======
	// cgi & responce here
	std::string response = server.rout(*req);
	std::cout << "----------------" << std::endl;
	std::cout << response << std::endl;
	server.send_response(response.c_str(), server._client_fd);
	// printf("send response\n");

    return 0;
}
>>>>>>> c69c8bf033e6cc4b41c283586de6e42f285f1806
