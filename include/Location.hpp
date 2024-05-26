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
		bool						cgiPass;
		bool						autoIndex;
		std::vector<t_method>		allowMethod;
		uint64_t					cliBodySize;
		std::string					root;
		std::vector<std::string>	index;
		return_t					ret;

		Location(const Location &other):cgiPass(other.cgiPass), autoIndex(other.autoIndex), allowMethod(other.allowMethod), cliBodySize(other.cliBodySize), root(other.root), index(other.index), ret(other.ret){}
		
		Location operator= (const Location &rhs){
			if (this == &rhs)
				return *this;
			cgiPass = rhs.cgiPass;
			autoIndex = rhs.autoIndex;
			allowMethod = rhs.allowMethod;
			cliBodySize = rhs.cliBodySize;
			root = rhs.root ;
			index = rhs.index;
			ret = rhs.ret;
			return *this;
		}

};

#endif