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
	ret.insert(std::pair<std::string, Location>("/redir", redir));	
	ret.insert(std::pair<std::string, Location>("/blog", blog));	
	ret.insert(std::pair<std::string, Location>("/images", images));	
	ret.insert(std::pair<std::string, Location>("/cgi-bin", cgi_bin));	

	return (ret);

}


Server *mock_server(void)
{
	Server *serv = new Server();
	serv->name = "localhost";
	serv->ipAddr = "0.0.0.0";
	serv->port = 6969;
	serv->_config = mock_location();

	// std::cout << serv->_config << std::endl;
	return (serv);

}


int	main(int ac, char **av, char **env)
{
	std::vector<Server> servs;
	servs.push_back(*mock_server());

	WebServer webserver(servs);
	webserver.runServer();
	// std::cout << *webserver._cgi._select_location(request, servs[0]);

    return 0;
}

