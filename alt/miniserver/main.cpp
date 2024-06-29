#include "../../include/Common.hpp"

bool	_setOptSock(int &sockFd) {
	int	optval = 1;
	// Allows binding the same address and port without waiting for the operating system to release the bound address and port
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
		return false;
	// Enables sending of keep-alive messages on the TCP socket
	if (setsockopt(sockFd, IPPROTO_TCP, SO_KEEPALIVE, &optval, sizeof(optval)) < 0)
		return false;
	return true;
}

int main(int ac, char **av, char **env)
{
    sockaddr_in addr, cliaddr;
    int listen_fd;
    socklen_t addlen = sizeof(addr);

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        perror("socket failed");
    
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(6969);

    if (bind(listen_fd, (sockaddr *)&addr, sizeof(addr)) < 0)
        perror("bind failed");

        if (fcntl(listen_fd, F_SETFL, O_NONBLOCK) < 0)
            std::cout << "non-blocking failed" << std::endl;
        if (_setOptSock(listen_fd) == 0)
            std::cerr << "setup socket option failed" << std::endl;

    if (listen(listen_fd, 3) < 0)
        perror("listen failed");
    std::cout << "listen done" << std::endl;


    fd_set current, ready;
    char buffer[1024];

    FD_ZERO(&current);
    FD_SET(listen_fd, &current);
    
    while (true)
    {
        ready = current;
        if (select(FD_SETSIZE, &ready, NULL, NULL, NULL) < 0){
            std::cerr << "select fail" << std::endl;
        }
        for (int fd = 0; fd < FD_SETSIZE; fd++){
            if (FD_ISSET(fd, &ready)){
                if (fd == listen_fd){
                    int cli = accept(listen_fd, (sockaddr *)&cliaddr, &addlen);
                    if (cli < 0){
                        std::cerr << "accept failed" << std::endl;
                        exit(1);
                    }
                    FD_SET(cli, &current);
                }
                else {
                    read(fd, buffer, 1024);
                    std::cout << buffer << std::endl;
                    FD_CLR(fd, &current);
					FD_SET(fd, )
                }
            }

        }
    }
}