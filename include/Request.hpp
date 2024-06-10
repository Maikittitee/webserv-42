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
#	include <sstream> 
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

class Request{

	private:

		std::vector<std::string> request_v;

		int			write_fd;
	
		std::map<std::string, int>	_method_map;
		std::map<std::string, std::string>	_headerField_map;

		// Method
		bool		_collectRequestToVector(std::string &request);
		bool		_readRequestLine( void );
		bool		_readRequestHeaderField( void );
		bool		_httpVersionCheckNCollect(std::string word);
		bool		_methodCheckNCollect(std::string &methodInput);
		int			_reqErrMsg( void );
		void		_collectQuery(std::string body_l);
		void		_trimSpaceWordVector(std::vector<std::string> &word_v);
		void		_readRequestMassageBody( void );

	public:
		// Attribute
		size_t		_lineIndex;
		t_reqErr	_reqErr;
		t_method	_method;
		std::string	_path;
		t_version	_http_version;
		std::string	_host;
		std::string	_body;
		std::string	_query_string;

		// Constructor and Destructor
		Request( void );
		Request(std::string request);
		~Request( void ) {}

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

		std::map<std::string, std::string>	getHeaderFieldMap ( void )
		{
			return _headerField_map;
		}
};


# endif