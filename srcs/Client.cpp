#include "../include/Client.hpp"

Client::Client(void) {
	addrLen = sizeof(struct sockaddr_in);
	std::cout << "client constructor called" << std::endl;
}

Client::~Client(){
	delete request;
}

void	Client::updateTime(void) {
	std::time(&lastTimeConnected);		// get current time.
	lastTimeConnected += KEEPALIVETIME;
}