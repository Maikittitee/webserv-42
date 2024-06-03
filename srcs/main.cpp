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


Server *mock_server(void)
{
	Server *serv = new Server();
	serv->name = "localhost";
	serv->ipAddr = "0.0.0.0";
	serv->port = "6969";
	serv->_config = mock_location();

	return (serv);

}


// int	main(int ac, char **av, char **env)
// {
// 	std::vector<Server> servs;
// 	servs.push_back(*mock_server());

// 	WebServer webserver;

// 	webserver.initServer(servs);
// 	webserver.runServer();


			

//     return 0;
// }

bool	_setOptSock(int &sockFd) {
	int	optval = 1;
	// Allows binding the same address and port without waiting for the operating system to release the bound address and port
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		return false;
	// Enables sending of keep-alive messages on the TCP socket
	if (setsockopt(sockFd, IPPROTO_TCP, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
		return false;
	return true;
}

int main(int ac, char **av, char **env)
{
	sockaddr_in addr, cliaddr;
	int listen_fd;
	socklen_t addlen = sizeof(addr);

	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		perror("socket failed");
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(6969);

	if (bind(listen_fd, (sockaddr *)&addr, sizeof(addr)) < 0)
		perror("bind failed");

		if (fcntl(listen_fd, F_SETFL, O_NONBLOCK) < 0)
			std::cout << "non-blocking failed" << std::endl;
		if (_setOptSock(listen_fd) == 0)
			std::cerr << "setup socket option failed" << std::endl;

	if (listen(listen_fd, 3) < 0)
		perror("listen failed");
	std::cout << "listen done" << std::endl;


	fd_set current, ready;
	char buffer[1024];

	FD_ZERO(&current);
	FD_SET(listen_fd, &current);
	
	while (true)
	{
		ready = current;
		if (select(FD_SETSIZE, &ready, NULL, NULL, NULL) < 0){
			std::cerr << "select fail" << std::endl;
		}
		for (int fd = 0; fd < FD_SETSIZE; fd++){
			if (FD_ISSET(fd, &ready)){
				if (fd == listen_fd){
					int cli = accept(listen_fd, (sockaddr *)&cliaddr, &addlen);
					if (cli < 0){
						std::cerr << "accept failed" << std::endl;
						exit(1);
					}
					FD_SET(cli, &current);
				}
				else {
					read(fd, buffer, 1024);
					std::cout << buffer << std::endl;
					FD_CLR(fd, &current);

				}
			}

		}

		
	}





	



}