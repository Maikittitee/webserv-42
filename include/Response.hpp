#ifndef RESPONSE_HPP
# define RESPONSE_HPP

// to encapsulate data and pass it as a param before create response text

# include <iostream>
# include <string>
# include <time.h>
# include <sstream>
# include "Mime.hpp"

class Request;

class Response{
	public:
		int _return_code;
		std::string _header;
		std::string _body;
		std::string _content_type;

		Response(int return_code, std::string body);
		void genarate_header();
		std::string status_def();
		std::string get_response_text();
		std::string get_date();


};

#endif