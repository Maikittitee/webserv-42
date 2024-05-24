#ifndef RESPONSE_HPP
# define RESPONSE_HPP

// to encapsulate data and pass it as a param before create response text

# include <iostream>
# include <string>
# include <time.h>

class Request;

class Response{
	public:
		int _return_code;
		std::string _header;
		std::string _body;

		Response(int return_code, std::string body);
		std::string genarate_header();
		std::string status_def();
		std::string get_response_text();


};

#endif