#ifndef RESPONSE_HPP
# define RESPONSE_HPP

// to encapsulate data and pass it as a param before create response text
# include "Common.hpp"
# include "Mime.hpp"
# include "Request.hpp"
# include "Location.hpp"

// class Request;

// class Location;


class Response{
	public:
		int _return_code;
		std::string _header;
		std::string _body;
		std::string _content_type;
		bool		cgiPass;

		Response();
		~Response();
		std::string get_date();


};

#endif