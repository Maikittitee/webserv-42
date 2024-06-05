#ifndef REQUEST_HPP
# define REQUEST_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include <vector>
#	include <map>
#	include "Utils.hpp"

typedef enum e_requestErrorCode{
			SUCESS_REQUEST,
			EMPTHY_REQUEST,
			INVALID_METHOD,
			BAD_REQUESTLINE,
			METHOD_OUTOFRANGE,
			BAD_HEADERFIELD,
			BAD_HTTPREQUEST
} t_reqErr;

class RequestHttp{
	public:

		// Constructor and Destructor
		RequestHttp( void );
		RequestHttp(std::string request);
		~RequestHttp( void )
		{
			
		}

		// Getter
		t_method	getMethod( void )
		{
			return _method;
		}
		std::string	getPath( void )
		{
			return _path;
		}
		t_version	getHttpVersion( void )
		{
			return _http_version;
		}
		std::string	getBody( void )
		{
			return _body;
		}
		std::string	getQueryString( void )
		{
			return _query_string;
		}

	private:

		// Attribute
		size_t		lineIndex;
		t_reqErr	_reqErr;
		t_method	_method;
		std::string	_path;
		t_version	_http_version;
		std::string	_host;
		std::string	_body;
		std::string	_query_string;

		std::vector<std::string> request_v;

		int			write_fd;
	
		std::map<std::string, int>	_method_map;
		std::map<std::string, std::string>	_headerField_map;

		// Method
		bool		_collectRequestToVector(std::string &request);
		bool		_readRequestLine( void );
		bool		_readRequestHeaderField( void );
		void		_readRequestMassageBody( void );
		int			_reqErrMsg( void );

};


# endif