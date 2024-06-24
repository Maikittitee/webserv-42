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
#include "../include/WebServer.hpp"
#include "../include/Config.hpp"


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
	images.index.insert(images.index.end(), "usa.jpg");
	images.index.insert(images.index.end(), "test.png");

	Location cgi_bin(def);
	cgi_bin.cgiPass = true;
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


Server *mock_server(void)
{
	Server *serv = new Server();
	serv->server_name = "localhost";
	serv->ipAddr = "0.0.0.0";
	serv->listen = 6969;
	serv->_config = mock_location();

	std::cout << serv->_config << std::endl;
	return (serv);

}

int main(int ac, char **av, char **env)
{
	std::vector<Server> sv;

	if (parsing_config(ac, av, sv) == false)
	{
		std::cerr << RED << "Error File" << RESET << std::endl;
		return(1);
	}

	for (int i = 0; i < sv.size(); i++)
	{
		ft_prt_server(sv[i]);
		ft_prt_location(sv[i]._config);
	}
	return (0);	
}

// int	main(int ac, char **av)
// {
	// Server server(8384);
	// char buffer[1024];
	// Request *req = mock_file_request();
	// Location *loc = mock_location();
	// char *msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\nContent-Length: 214\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Hello World</title>\n</head>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>\n\0";

	// std::cout << "bp1" << std::endl;
	// parsing config here
	// parsing_config(server , ac, av);
	// server.run_server();
	// read(server._client_fd, buffer, 1024 - 1);

	// // parsing request here

	// printf("this is request message\n");
	// printf("%s\n", buffer);

	// // cgi & responce here
	// std::string response = server.classify_request(*req, *loc);
	// server.send_response(response.c_str(), server._client_fd);
	// printf("send response\n");

    // return 0;
// }


// int main(int ac, char **av, char **env)
// {
// 	// parsing_config(ac, av, env);	
// 	// Server ();
// 	Location location;

// 	std::map<std::string, Location> _config;

// 	_config = mock_location(); 

// 	// location.port = 80;
// 	// _config.insert(std::pair<std::string, Location>("key", location));

// 	std::map<std::string, Location>::iterator it;
// 	for (it = _config.begin(); it != _config.end(); it++)
// 	{
// 		std::cout << it->first << std::endl;
// 		std::cout <<  it->second << std::endl;
// 		// std::cout << "[test_print] client_max : " << it->second._client_max << std::endl;
// 	}
// 	return (0);	
// }
