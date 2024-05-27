#ifndef RESPONSE_HPP
# define RESPONSE_HPP

// to encapsulate data and pass it as a param before create response text

# include <iostream>
# include <string>
# include <time.h>
# include <sstream>
#include <unistd.h>
# include "Mime.hpp"
# include "Request.hpp"
# include "Location.hpp"

class Request;

class Location;

class Response{
	public:
		int _return_code;
		std::string _header;
		std::string _body;
		std::string _content_type;

		Response();
		~Response();
		void		receive_request(Request &request, Location &config);
		void		set_body(std::string filename);
		std::string		get_body_from_file(std::string filename);
		void		genarate_header(void);
		std::string status_def();
		std::string get_response_text();
		std::string get_date();


};

#endif