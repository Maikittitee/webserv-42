#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <iostream>
# include <string>
# include <time.h>

class Request;

class Response{
	public:
		std::string	_http_version;
		int return_code;
		std::string content_type;
		std::string date_time;
		std::string body;

		Response(Request request);
		std::string generate_header();


};

#endif