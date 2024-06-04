#include "../include/WebServer.hpp"

WebServer::WebServer(){}

WebServer::~WebServer(){}

bool	WebServer::_setSockAddr(struct sockaddr_in &addr, Server &serv) {
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(serv.port);
	return true;
}

bool	WebServer::_setOptSock(int &sockFd) {
	int	optval = 1;
	// Allows binding the same address and port without waiting for the operating system to release the bound address and port
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		return false;
	// Enables sending of keep-alive messages on the TCP socket
	if (setsockopt(sockFd, IPPROTO_TCP, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
		return false;
	return true;
}

bool WebServer::initServer(std::vector<Server> &servers)
{
	struct sockaddr_in	sockAddr;
	socklen_t addr_len = sizeof(sockAddr);
	for (int i = 0; i < servers.size(); i++){
		if (_setSockAddr(sockAddr, servers[i]) == 0)
			std::cerr << "setup socket failed" << std::endl;

		// get server fd
		servers[i]._server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (servers[i]._server_fd < 0)
			std::cerr << "create socket failed" << std::endl;

		// set non blocking	
		if (fcntl(servers[i]._server_fd, F_SETFL, O_NONBLOCK) < 0)
			std::cout << "non-blocking failed" << std::endl;
		
		if (_setOptSock(servers[i]._server_fd) == 0)
			std::cerr << "setup socket option failed" << std::endl;
		
		// Bind the socket to the specified address and port
		if (bind(servers[i]._server_fd, (sockaddr *)&sockAddr, addr_len) < 0)
			std::cerr << "bilded failed" << std::endl;
		
		// Prepare socket for incoming connection
		if (listen(servers[i]._server_fd, 512) < 0)
			std::cout << "listen failded" << std::endl;

		std::cout << "create server success fd: " << servers[i]._server_fd << std::endl;
		this->_servers.push_back(servers[i]);
	}
	return (true);
}

void	WebServer::_init_fds(void)
{
	int	iter_fd;

	_max_fd = 0;
	FD_ZERO(&_read_fds);
	FD_ZERO(&_write_fds);
	for (size_t i = 0; i < _servers.size(); i++) {
		iter_fd = _servers[i]._server_fd; 
		_set_fd(iter_fd, _read_fds);
	}

}

bool WebServer::_set_fd(int fd, fd_set &set)
{
	FD_SET(fd, &set);
	if (fd > _max_fd)
		_max_fd =  fd;

	return (true);

}

bool WebServer::runServer(void)
{
	
	fd_set tmp_read_fds;
	char buffer[1024];
	// fd_set tmp_write_fds;

	_init_fds();
	while (true)
	{
		tmp_read_fds = _read_fds;
		// tmp_write_fds = _write_fds;
		// select 
		int status = select(_max_fd + 1, &tmp_read_fds, NULL, NULL, NULL);
		if (status == -1){
			std::cerr << "select error " << std::endl;
			return (false);
		}
		for (int fd = 0; fd <= _max_fd; fd++){
			if (FD_ISSET(fd, &tmp_read_fds))
			{
				if (fd == _servers.begin()->_server_fd) // is match listen fd of server (handshake)
				{
					// accept connection (server keep client obj, keep fd of data transfer)
					Client client;
					client.fd = accept(fd, (sockaddr *)&client.addr, &client.addrLen);
					_clients.insert(std::pair<int, Client>(client.fd, client));
					_set_fd(client.fd, _read_fds);
				}
				else
				{
					// parsing request here
					// pasing only header and keep open fd
					read(fd, buffer, 1024);
					std::cout << buffer << std::endl;
					FD_CLR(fd, &_read_fds);
				}
			}
		}
	}
	return (true);

}