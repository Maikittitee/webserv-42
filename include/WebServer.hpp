#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include "Common.hpp"
# include "Server.hpp"
# include "Client.hpp" 
# include "CGI.hpp"

class Server;

class Client;

class CGI;

class WebServer{
	public:
		WebServer();
		WebServer(std::vector<Server> &servers);
		~WebServer();
		bool	initServer(std::vector<Server> &servers);
		bool	runServer(void);
		bool	downServer(void);
	
	private:
		bool	_setSockAddr(struct sockaddr_in &addr, Server & serv);
		bool	_setOptSock(int &sockFd);
		void	_init_fds(void);
		bool	_set_fd(int fd, fd_set &set);
		bool	_clear_fd(int fd, fd_set &set);
		bool	_is_match_server(int fd);
		bool	_accept_connection(int server_fd);
		Server*	_get_server(int fd);
		bool	_parsing_request(int read_fd);
		Client* _get_client(int fd);
		bool	_send_response(int fd);
		bool	_disconnectClienet(int fd);
		bool	_disconnectAllClienets( void );
		bool	_checkTimeout( void );

		std::map<int, Client *>	_clients;
		std::vector<Server> 	_servers;
		struct timeval			_timeOut;
		fd_set 					_read_fds;
		fd_set					_write_fds;
		char					*buffer;
		int						_max_fd;
		CGI						_cgi;



};

#endif