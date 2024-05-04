#ifndef REQUEST_HPP
# define REQUEST_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <tuple>
#	include <stdlib.h>
#	include <unistd.h>
#	include "Utils.hpp"




class Request{
	public:
		Request(std::string request){};
		Request( void ){};
		~Request( void ){};

		t_method _method;
		std::string _path;
		t_version _http_version;	
		std::vector<std::tuple <float, std::string > > _accept; // accept type ex. text/html

		std::string _body;
};


# endif