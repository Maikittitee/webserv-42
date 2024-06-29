#include "../include/Client.hpp"

Client::Client(void): 
fd(-1),
pipe_available(false),
child_pid(-1),
pipe_fd{-1, -1},
pipe_fd_out{-1, -1},
IPaddr(""),
addrLen(0),
buffer(""),
rawReqMsg(""),
bufSize(0),
server(nullptr),
request(nullptr),
location(nullptr)
{
	addrLen = sizeof(struct sockaddr_in);
	std::cout << "client constructor called" << std::endl;
}

Client::~Client(){
	delete request;
}