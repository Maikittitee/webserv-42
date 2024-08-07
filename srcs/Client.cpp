#include "../include/Client.hpp"

Client::Client(void): 
fd(-1),
pipe_available(false),
child_pid(-1),
IPaddr(""),
buffer(""),
rawReqMsg(""),
bufSize(0),
server(NULL),
request(NULL),
location(NULL)
{
	updateTime();
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	pipe_fd_out[0] = -1;
	pipe_fd_out[1] = -1;
	std::cout << "client constructor called" << std::endl;
}

Client::~Client(){
	delete request;
	request = NULL;

	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (pipe_fd_out[0] != -1)
		close(pipe_fd_out[0]);
	if (pipe_fd_out[1] != -1)
		close(pipe_fd_out[1]);
}

void	Client::updateTime(void) {
	std::time(&lastTimeConnected);		// get current time.
	lastTimeConnected += KEEPALIVETIME;
}