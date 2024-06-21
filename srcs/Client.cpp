#include "../include/Client.hpp"

Client::Client(void) {
	addrLen = sizeof(struct sockaddr_in);
	std::cout << "client constructor called" << std::endl;
}

Client::~Client(){

}