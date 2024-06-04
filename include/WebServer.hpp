#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include "Common.hpp"
# include "Server.hpp"
# include "Client.hpp" 

class Server;

class Client;

class WebServer{
	public:
		WebServer();
		~WebServer();
		bool	initServer(std::vector<Server> &servers);
		bool	runServer(void);
		bool	downServer(void);
		bool	_setSockAddr(struct sockaddr_in &addr, Server & serv);
		bool	_setOptSock(int &sockFd);
		void	_init_fds(void);
		bool	_set_fd(int fd, fd_set &set);
		bool	_clear_fd(int fd, fd_set &set);

		char *buffer;
		std::vector<Server> _servers;
		std::map<int, Client> _clients;
		fd_set 	_read_fds;
		fd_set	_write_fds;
		int		_max_fd;
		struct timeval			_timeOut;



};

#endif