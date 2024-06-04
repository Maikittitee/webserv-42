#ifndef REQUEST_HPP
# define REQUEST_HPP

#	include "Common.hpp"
#	include "Utils.hpp"




class Request{
	public:
		Request(std::string request){};
		Request( void ){};
		~Request( void ){};

		t_method _method;
		std::string _path;
		std::string _http_version;	
		std::string _body;
		std::string _query_string;
		int			write_fd;
};


# endif