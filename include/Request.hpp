#ifndef REQUEST_HPP
# define REQUEST_HPP

#	include <fstream>
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

typedef enum e_requestStatusCode{
			IN_REQUEST_LINE,
			IN_HEADER_LINE,
			IN_CRLF_LINE,
			IN_BODY_LINE,
			END_REQUEST_MSG
} t_reqStatus;

class Request{

	private:
		size_t						_lineIndex;
		size_t						_bodyIndex;
		t_reqStatus					_status;
		int							write_fd;
	
		std::map<std::string, int>	_method_map;
		std::map<std::string, std::string>	_headerField_map;

		// Method
		bool		_collectRequestToVector(std::string request);
		bool		_readRequestLine( void );
		bool		_readRequestHeaderField( void );
		bool		_httpVersionCheckNCollect(std::string word);
		bool		_methodCheckNCollect(std::string &methodInput);
		int			_reqErrMsg( void );
		void		_collectQuery(std::string body_l);
		void		_trimSpaceWordVector(std::vector<std::string> &word_v);
		void		_readRequestMassageBody( void );
		void		_intiRequestStatus(std::string request);
		void		_updateRequestToVector(std::string &request);
		void		_updateFromRequestLine( void );
		void		_updateFromHeaderLine( void );
		void		_updateAfterHeaderLine( void );


	public:
		// Attribute
		t_reqErr	_reqErr;
		t_method	_method;
		std::string	_path;
		t_version	_http_version;
		std::string	_host;
		std::string	_body;
		std::string	_query_string;
		bool		_isEndRecv;
		std::vector<std::string>	request_v;

		// Constructor and Destructor
		Request( void );
		Request(std::string request);
		~Request( void ) {}

		// Getter
		std::map<std::string, std::string>	getHeaderFieldMap ( void ) const
		{
			return _headerField_map;
		}
		t_reqStatus	getStatus( void )
		{
			return _status;
		}


		// Public Method
		void		updateRequest(std::string request);
		void		updateStatus(t_reqStatus status)
		{
			_status = status;
		}
};

std::ostream &operator <<(std::ostream &os, const Request &req);

# endif