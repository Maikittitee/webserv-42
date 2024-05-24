#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <iostream>
# include <string>
# include <time.h>

class Request;

class Response{
	public:
		int _return_code;
		std::string _header;
		std::string _body;

		Response(int return_code, std::string header, std::string body);
		std::string get_status_text();


};

#endif