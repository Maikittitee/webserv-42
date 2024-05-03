#ifndef REQUEST_HPP
# define REQUEST_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>

class Request{
	public:
		Request(std::string request);
		~Request( void );


		enum _method{
			ELSE,
			GET,
			POST,
			DELETE,
			HEAD,
		};
		std::string _path;
		enum _version{
			HTTP09, // HTTP/0.9
			HTTP10, // HTTP/1.0
			HTTP11, // HTTP/1.1
			HTTP00, // else
		};
		std::vector<std::string> _accept;
		int _content_length;
};


# endif