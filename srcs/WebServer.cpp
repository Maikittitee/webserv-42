#include "../include/WebServer.hpp"

WebServer::WebServer(){
	buffer = new char[BUFFERSIZE];
}

WebServer::~WebServer(){
	delete[] buffer;
}

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

		std::cout << BLU "create server success fd: " << servers[i]._server_fd << RESET << std::endl;
		this->_servers.push_back(servers[i]);
	}
	return (true);
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
		
		int status = select(_max_fd + 1, &tmp_read_fds, &tmp_write_fds, NULL, NULL);
		if (status == -1){
			std::cerr << RED << "select error " << RESET << std::endl;
			return (false);
		}
		for (int fd = 0; fd <= _max_fd; fd++){
			if (FD_ISSET(fd, &tmp_read_fds))
			{
				if (_is_match_server(fd)) 	// is match listen fd of server (handshake)
					_accept_connection(fd);
				else
					_parsing_request(fd);
			}
			else if (FD_ISSET(fd, &tmp_write_fds))
				_send_response(fd);
			continue;
		}
	}
	return (true);

}

bool	WebServer::_send_response(int fd)
{
	Client *client = _get_client(fd);
	Server *server = client->server;

	std::string msg = server->rout(*client->request);
	// CGI work here

	std::cout << BLU << "sending response:" << RESET << std::endl;
	std::cout << YEL << msg << RESET << std::endl;
	write(fd, msg.c_str(), msg.size());
	close(fd);
	_clear_fd(fd, _write_fds);
	_clients.erase(fd);
	return (true);

}

bool	WebServer::_is_match_server(int fd)
{
	for (int i = 0; i < _servers.size(); i++){
		if (_servers[i]._server_fd == fd)
			return (true);
	}
	return (false);
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

bool	WebServer::_clear_fd(int fd, fd_set &set) {
	FD_CLR(fd, &set);
	if (fd == _max_fd)
		_max_fd--;
	return (true);
}

Server *WebServer::_get_server(int fd)
{
	for (int i = 0; i < _servers.size(); i++){
		if (_servers[i]._server_fd == fd)
			return (&(_servers[i]));
	}
	return (NULL);
}

bool	WebServer::_accept_connection(int server_fd)
{
	Client new_client;

	new_client.fd = accept(server_fd, (sockaddr *)&new_client.addr, &new_client.addrLen);
	if (new_client.fd < 0){
		std::cerr << RED << "cannot accept connection." << RESET << std::endl;
		return (false);
	}
	_clients.insert(std::pair<int, Client>(new_client.fd, new_client));
	new_client.server = _get_server(server_fd);
	if (!new_client.server){
		std::cerr << RED << "server not found" << RESET << std::endl;
		return (false);
	}
	std::cout << BLU << "Accept connection (server<-client): " << server_fd << "<-" << new_client.fd << RESET << std::endl;
	_set_fd(new_client.fd, _read_fds);
	return (true);
}

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

bool WebServer::_parsing_request(int client_fd)
{
	Client *client = _get_client(client_fd);
	Server *server = client->server;

	read(client_fd, buffer, BUFFERSIZE);
	std::cout << GRN << buffer << RESET << std::endl;

	Request *request = mock_file_request(); // change to p'tew parsing request na krab
	client->request = request;

	_clear_fd(client_fd, _read_fds);
	_set_fd(client_fd, _write_fds);
	return (true);
}

Client* WebServer::_get_client(int fd)
{
	if (!_clients.count(fd))
		return (NULL);
	return (&_clients[fd]);
}