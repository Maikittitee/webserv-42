#include "../include/Client.hpp"

Client::Client(void) {
	addrLen = sizeof(struct sockaddr_in);
	server_fd = 9;
	std::cout << "client constructor called" << std::endl;
}

Client::~Client(){

}