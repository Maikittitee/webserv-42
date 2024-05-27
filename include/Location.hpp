#ifndef LOCATION_HPP
#	define LOCATION_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include "Utils.hpp"

struct return_t {
	bool		have;	// if there is a return 1 (true)
	short int	code;	// Status Code
	std::string	text;	// Option
};


class Location{
	public:
		Location(void);
		bool						cgiPass;
		bool						autoIndex;
		std::vector<t_method>		allowMethod;
		uint64_t					cliBodySize;
		std::string					root;
		std::vector<std::string>	index;
		return_t					ret;

		Location(const Location &other);
		
		Location& operator= (const Location &rhs);

};

std::ostream& operator<<(std::ostream &os, const std::vector<t_method>& eiei);
std::ostream& operator<<(std::ostream &os, const std::vector<std::string>& eiei);


std::ostream& operator<<(std::ostream& os, const Location& location);

#endif