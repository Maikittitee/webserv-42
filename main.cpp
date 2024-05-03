#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Server.hpp"

int	main()
{
	Server server(8384);
	char buffer[1024];
	char *msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\nContent-Length: 214\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Hello World</title>\n</head>\n<body>\n<h1>Hello, World!</h1>\n</body>\n</html>\n\0";

	// parsing config here

	server.run_server();


	read(server._client_fd, buffer, 1024 - 1);

	// parsing request here

	printf("this is request message\n");
	printf("%s\n", buffer);

	// cgi & responce here

	server.send_response(msg, server._client_fd);
	printf("send response\n");

    return 0;
}