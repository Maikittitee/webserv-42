#include "../include/WebServer.hpp"

WebServer::WebServer(){}

WebServer::~WebServer(){}

bool	WebServer::_setSockAddr(struct addrinfo & sockAddr, Server & serv) {
	int	status;
	struct addrinfo	hints;
	struct addrinfo	*sockAddrTemp;

	memset(&hints, 0, sizeof(hints));	// Set all member to empty
	hints.ai_family = AF_INET;			// Allow IPv4 Protocol
	hints.ai_socktype = SOCK_STREAM;	// Stream socket are socket type for support TCP or SCTP
	hints.ai_protocol = IPPROTO_TCP;	// TCP Protocol
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	_timeOut.tv_sec = 5;
	_timeOut.tv_usec = 0;
	status = getaddrinfo(serv.ipAddr.c_str(), serv.port.c_str(), &hints, &sockAddrTemp);
	if (status != 0) {
		return false;
	}
	sockAddr = *sockAddrTemp;
	freeaddrinfo(sockAddrTemp);
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
	struct addrinfo	sockAddr;
	for (int i = 0; i < servers.size(); i++){
		if (_setSockAddr(sockAddr, servers[i]) == 0)
			std::cerr << "setup socket failed" << std::endl;
		servers[i]._server_fd = socket(sockAddr.ai_family, sockAddr.ai_socktype, sockAddr.ai_protocol);
		if (servers[i]._server_fd < 0)
			std::cerr << "create socket failed" << std::endl;
		if (fcntl(servers[i]._server_fd, F_SETFL, O_NONBLOCK) < 0)
			std::cout << "non-blocking failed" << std::endl;
		if (_setOptSock(servers[i]._server_fd) == 0)
			std::cerr << "setup socket option failed" << std::endl;
		// Bind the socket to the specified address and port
		if (bind(servers[i]._server_fd, sockAddr.ai_addr, sockAddr.ai_addrlen) < 0)
			std::cerr << "bilded failed" << std::endl;
		// Prepare socket for incoming connection
		if (listen(servers[i]._server_fd, 3) < 0)
			std::cerr << "listen failded" << std::endl;
		// Logger::isLog(INFO) && Logger::log(GRN, "Success to create server fd: ", servs[i].sockFd);
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
		FD_SET(iter_fd, &_read_fds); // server's connection fd -add-into-> read fd set
		if (iter_fd > _max_fd)
			_max_fd = iter_fd; // update max fd
	}

}

bool WebServer::runServer(void)
{
	fd_set tmp_read_fds;
	fd_set tmp_write_fds;

	_init_fds();
	while (true)
	{
		tmp_read_fds = _read_fds;
		tmp_write_fds = _write_fds;
		// select 
		int status = select(_max_fd + 1, &tmp_read_fds, &tmp_write_fds, NULL, &_timeOut);
		if (status == 0)
			std::cout << "Time out" << std::endl;
		else if (status == -1){
			std::cerr << "select error " << std::endl;
			return (false);
		}
		for (int fd = 0; fd < _max_fd; fd++){
			if (FD_ISSET(fd, &_read_fds))
			{
				if (fd == _servers.begin()->_server_fd)
					
					std::cout << "accept" << std::endl;
				else
					std::cout << "not match " << std::endl;

			}
		}
		
		// if time out -> 
		// if select error ->

		// loop every fd
		// if read 
		// 		if new connection -> accept
		// 		else -> parsing request
		// else if write
		//		send response

	}
	return (true);

}