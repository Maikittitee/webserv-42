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

	std::map<std::string, Location> ret;

	ret.insert(std::pair<std::string, Location>("def", def));	
	ret.insert(std::pair<std::string, Location>("/", r));	
	ret.insert(std::pair<std::string, Location>("/redir", redir));	
	ret.insert(std::pair<std::string, Location>("/blog", blog));	
	ret.insert(std::pair<std::string, Location>("/images", images));	
	ret.insert(std::pair<std::string, Location>("/cgi-bin", cgi_bin));	

	return (ret);

}



int	main(int ac, char **av, char **env)
{
	Server server(8384, env);
	// char buffer[1024];
	// Request *req = mock_file_request();
	server._config = mock_location();

	// std::cout << server._config.begin()->first;
	for(std::map<std::string, Location >::const_iterator it = server._config.begin(); it != server._config.end(); ++it){
		// std::cout << "bp1" << std::endl; 
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
	// parsing config here

	// server.run_server();
	// read(server._client_fd, buffer, 1024 - 1);

	// parsing request here

	// printf("this is request message\n");
	// printf("%s\n", buffer);

	// cgi & responce here
	// std::string response = server.rout(*req);
	// server.send_response(response.c_str(), server._client_fd);
	// printf("send response\n");

    return 0;
}
