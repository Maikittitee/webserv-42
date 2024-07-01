#include "../include/WebServer.hpp"

WebServer::WebServer(){
	buffer = new char[BUFFERSIZE];
}

WebServer::WebServer(std::vector<Server> &servers)
{
	buffer = new char[BUFFERSIZE];
	struct sockaddr_in	sockAddr;
	socklen_t addr_len = sizeof(sockAddr);
	for (int i = 0; i < servers.size(); i++){
		if (_setSockAddr(sockAddr, servers[i]) == 0)
			std::cerr << "setup socket failed" << std::endl;

		// get server fd
		servers[i]._server_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (servers[i]._server_fd <= 0)
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

}

WebServer::~WebServer(){
	delete[] buffer;
}

bool	WebServer::_setSockAddr(struct sockaddr_in &addr, Server &serv) {
	
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	// std::cout << "serv listen is " << serv.listen << std::endl;
	addr.sin_port = htons(serv.listen);
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
	g_state = true;
	while (g_state)
	{
		tmp_read_fds = _read_fds;
		tmp_write_fds = _write_fds;
		
		int status = select(_max_fd + 1, &tmp_read_fds, &tmp_write_fds, NULL, NULL);
		if (status == -1){
			// std::cerr << RED << "select error " << RESET << std::endl;
			perror("select");
			return (false);
		}
		for (int fd = 0; fd <= _max_fd; fd++){
			if (FD_ISSET(fd, &tmp_read_fds))
			{
				if (_is_match_server(fd)) // is match listen fd of server (handshake)
				{
					if (_accept_connection(fd))
						continue;
				}
				else
				{
					std::cout << YEL << "receiving request... from: " << fd << RESET << std::endl;
					_parsing_request(fd);
				}
			}

			else if (FD_ISSET(fd, &tmp_write_fds))
			{
				std::cout << YEL << "sending..." << RESET << std::endl;
				_send_response(fd);

			}
			continue;
		}
	}
	std::cout << "Hi Tiew9" << std::endl;
	return (true);

}
bool	WebServer::downServer(void)
{
	// free every client
	_disconnectAllClienets();	
	return (true);
}

bool	WebServer::_send_response(int fd) // write fd
{
	Client *client = _get_client(fd);
	Server *server = client->server;
	Response response;
	t_cgi_return cgi_return;	
	if (!client)
		std::cerr << RED << "can't find client" << RESET << std::endl;
	if (!server)
		std::cerr << RED << "can't find server" << RESET << std::endl;
	if (client->request->_method == POST && client->request->getStatus() != END_REQUEST_MSG)
		return (false);
	
	std::cout << BLU << *client->request << RESET << std::endl;
	
	// CGI work here
	cgi_return = _cgi.rout(*client, *server);
	std::cout << BLU << "cgi return: " << cgi_return << RESET << std::endl;

	// Get resource
	response = _cgi.readfile(*client, *server, cgi_return); 

	// check client body size
	if (response._body.size() > client->location->cliBodySize){
		server->errorPage(413, response);
	}


	std::string msg = response.get_response_text();
	// delete &response;
	std::cout << BLU << "sending response:" << RESET << std::endl;
	std::cout << YEL << msg << RESET << std::endl;
	write(fd, msg.c_str(), msg.size());
	_disconnectClienet(fd);
	std::cout << "finish send response" << std::endl;
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
	Client *new_client = new Client;

	new_client->fd = accept(server_fd, (sockaddr *)&new_client->addr, &new_client->addrLen);
	if (new_client->fd < 0){
		std::cerr << RED << "cannot accept connection." << RESET << std::endl;
		return (false);
	}
	_clients[new_client->fd] = new_client;
	new_client->server = _get_server(server_fd);
	if (!new_client->server){
		std::cerr << RED << "server not found" << RESET << std::endl;
		return (false);
	}
	std::cout << BLU << "Accept connection (server<-client): " << server_fd << "<-" << new_client->fd << RESET << std::endl;
	_set_fd(new_client->fd, _read_fds);
	return (true);
}

bool WebServer::_parsing_request(int client_fd)
{
	static int i;
	Client *client = _get_client(client_fd);
	Server *server = client->server;

	i += 1;
	client->bufSize = recv(client->fd, client->buffer, BUFFERSIZE, MSG_DONTWAIT);
	// mai's 
	// client->request = my_request_parser(client->buffer);
	// _clear_fd(client_fd, _read_fds);
	// _set_fd(client_fd, _write_fds);	
	// return (true);
	std::cout << BLU << "current clients: " << _clients.size() << std::endl;
	if (client->bufSize > 0)
		client->buffer[client->bufSize] = '\0';
	else
	{
		std::cerr << RED << "Handle With recv error, do somethings!" << RESET << std::endl;
		// clear client
		_disconnectClienet(client_fd);
		return false;
		
	}
	std::cout << GRN << client->buffer << RESET << std::endl;
	if (!client->request)
	{
		std::cout << YEL << "new client" << RESET << std::endl;
		client->request = new Request(client->buffer);	
	}
    if (client->bufSize < BUFFERSIZE)
    {
        client->request->_isEndRecv = true;
	}
	// for end parsing reqeust
	if (client->request->_method != POST \
			&& client->request->getStatus() >= IN_CRLF_LINE)
	{
		std::cout << RED << "end of GET method" << RESET << std::endl;	
		_clear_fd(client_fd, _read_fds);
		_set_fd(client_fd, _write_fds);
	}
	else if (client->request->_method == POST \
			&& client->request->getStatus() >= END_REQUEST_MSG)
	{
		std::cout << RED << "end of POST method" << RESET << std::endl;	
		std::cout << "status: " << client->request->getStatus() << std::endl;
		_clear_fd(client_fd, _read_fds);
		_set_fd(client_fd, _write_fds);	
	}
	else if (client->request->getStatus() < END_REQUEST_MSG)
	{
		client->request->updateRequest(client->buffer);
	}
	std::cout << YEL << *client->request << RESET << std::endl;
	// if (i == 11)
	// 	exit(0);
	return (true);
}

Client* WebServer::_get_client(int fd)
{
	if (!_clients.count(fd))
		return (NULL);
	return (_clients[fd]);
}

bool WebServer::_disconnectClienet(int fd)
{
	if (!_clients.count(fd))
		return (false);
	std::map<int, Client *>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++){
		if (it->first == fd){
			std::cout << RED << "disconnect client: " << fd << RESET << std::endl;
			_clients.erase(fd);
			delete it->second;
			if (FD_ISSET(fd, &_read_fds))
				_clear_fd(fd, _read_fds);
			else if (FD_ISSET(fd, &_write_fds))
				_clear_fd(fd, _write_fds);
			close(fd);
			return (true);
		}
	}
	return (false);
	

	
}

bool	WebServer::_disconnectAllClienets( void )
{

	// neet fix
		std::map<int, Client *>::iterator it;

		for (it = _clients.begin(); it != _clients.end(); it++){
			std::cout << RED << "disconnect client: " << it->first << RESET << std::endl;
			// _clients.erase(it->first);
			delete it->second;
			close(it->first);
			if (FD_ISSET(it->first, &_read_fds))
				_clear_fd(it->first, _read_fds);
			else if (FD_ISSET(it->first, &_write_fds))
				_clear_fd(it->first, _write_fds);

		}
		_clients.clear();
		return (true);
}
