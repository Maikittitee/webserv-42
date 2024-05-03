#ifndef LOCATION_HPP
#	define LOCATION_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>

struct return_t {
	bool		have;	// if there is a return 1 (true)
	short int	code;	// Status Code
	std::string	text;	// Option
};

typedef enum e_method{
			ELSE,
			GET,
			POST,
			DELETE,
			HEAD,
} t_method;

class Location{
	public:
		bool						cgiPass;
		bool						autoIndex;
		std::vector<t_method>		allowMethod;
		uint64_t					cliBodySize;
		std::string					path;	// path
		std::string					root;
		std::vector<std::string>	index;
		return_t					ret;

};

#endif