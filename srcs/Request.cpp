#include "../include/Request.hpp"

Request::Request():
_lineIndex(0),
_bodyIndex(0),
_contentLength(0),
_status(IN_REQUEST_LINE),
_reqErr(SUCESS_REQUEST),
_method(NONE),
_path(""),
_http_version(HTTP00),
_body(""),
_query_string("")
{
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;
}

Request::Request(const std::string request):
_lineIndex(0),
_bodyIndex(0),
_contentLength(0),
_status(IN_REQUEST_LINE),
_reqErr(SUCESS_REQUEST),
_method(NONE),
_path(""),
_http_version(HTTP00),
_body(""),
_query_string("")
{
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;

	_collectRequestToVector(request);
	_intiRequestStatus();
	std::cout << "status after init = " << _status << std::endl;
	if(_status > IN_REQUEST_LINE)
		_readRequestLine();
	if(_status >= IN_HEADER_LINE)
		_readRequestHeaderField();
	if(_status >= IN_CRLF_LINE)
		_lineIndex++;
	if(_status > IN_CRLF_LINE)
		_readRequestMassageBody();
	if(_isEndRead())
	{
		std::cout << "request constructor call" << std::endl;
		_status = END_REQUEST_MSG;
	}
}

bool Request::_isEndRead( void )
{
	if (_contentLength == 0)
	{
		std::map<std::string, std::string>::iterator it = _headerField_map.find("Content-Length");
		if (it != _headerField_map.end())
		{
			std::istringstream iss(_headerField_map["Content-Length"].c_str());
			size_t contentLength;
			iss >> contentLength;
			if (iss.fail())
			{
				std::cerr << "Conversion failed" << std::endl;
				return (false);
			}
			_contentLength = contentLength;
		}
	}
	if (_contentLength <= _body.size())
		return (true);
	return (false);
}

void Request::_intiRequestStatus( void )
{
	for (std::vector<std::string>::iterator it = request_v.begin(); it != request_v.end(); ++it)
	{
		if (it == request_v.begin()
			&& _status == IN_REQUEST_LINE \
			&& ((*it).find('\n', (*it).size()- 1) != std::string::npos))
		{
				_status = IN_HEADER_LINE;
		}
		else if (_status == IN_HEADER_LINE)
		{
			if ((*it) == "\n" || (*it) == "\r\n" || (*it) == "\r")
			{
				_status = IN_CRLF_LINE;
			}
		}
		else if (_status == IN_CRLF_LINE)
		{
			if(it != request_v.end())
			{
				_status = IN_BODY_LINE;
			}
		}
	}
}



bool	Request::_collectRequestToVector(std::string request)
{
	std::string 		line;

	if (request.empty())
	{
		_reqErr = EMPTHY_REQUEST;
		return false;
	}
	request_v = lineToVector(request);
	return true;
}

bool 	Request::_readRequestLine( void )
{
	std::string					req_l;
	std::vector<std::string>	word_v;

	req_l = request_v[_lineIndex];
	word_v = splitToVector(req_l, ' ');
	if (word_v.size() != 3)
		return false;
	_trimSpaceWordVector(word_v);
	if(!_methodCheckNCollect(word_v[0]))
		return (false);
	_path = word_v[1];
	_collectQuery(word_v[1]);
	if(!_httpVersionCheckNCollect(word_v[2]))
		return (false);
	_lineIndex++;
	return true;
}

bool	Request::_methodCheckNCollect(std::string &methodInput)
{
	std::map<std::string, int>::iterator it = _method_map.find(methodInput);
	if (it != _method_map.end())
	{
		_method = static_cast<t_method>(_method_map[methodInput]);
		return (true);
	}
	else
		_method = ELSE;
	_reqErr = METHOD_OUTOFRANGE;
	return (false);
}

bool	Request::_httpVersionCheckNCollect(std::string word)
{
	std::vector<std::string>	version_v;

	trimNewline(word);
	version_v = splitToVector(word, '/');
	_trimSpaceWordVector(version_v);
	if(version_v[0] != "HTTP")
	{
		_reqErr = BAD_HTTPREQUEST;
		return (false);
	}
	if(version_v[1] == "0.9")
	{
		_http_version = HTTP09;
	}
	else if(version_v[1] == "1.0")
	{
		_http_version = HTTP10;
	}
	else if(version_v[1] == "1.1")
	{
		_http_version = HTTP11;
	}
	else
	{
		_http_version = HTTP00;
	}
	return (true);
}

bool	Request::_readRequestHeaderField( void )
{
	std::string					header_l;
	std::vector<std::string>	word_v;

	while(_lineIndex < request_v.size() \
		&& request_v[_lineIndex] != "\n" \
		&& request_v[_lineIndex] != "\r\n" \
		&& request_v[_lineIndex] != "\r") 
	{
		if (request_v[_lineIndex].find('\n', 0) == std::string::npos \
			&& request_v[_lineIndex].find(':', 0) == std::string::npos)
			return true;
		header_l = request_v[_lineIndex];
		word_v = headerSplit(header_l, ':');
		if (word_v.size() > 2)
			return false;
		_trimSpaceWordVector(word_v);
		trimNewline(word_v[1]);
		_headerField_map[word_v[0]] = word_v[1];
		// if (request_v[_lineIndex].find("\n\r", 0))
		// 	std::cout << "request_v[" << _lineIndex << "] rn\n";
		// else if (request_v[_lineIndex].find("\n", 0))
		// 	std::cout << "request_v[" << _lineIndex << "] n\n";
		// else if (request_v[_lineIndex].find("\r", 0))
		// 	std::cout << "request_v[" << _lineIndex << "] r\n";
		_lineIndex++;
	}
	return true;
}

void	Request::_trimSpaceWordVector(std::vector<std::string> &word_v)
{
    for (std::vector<std::string>::iterator it = word_v.begin(); it != word_v.end(); ++it)
    {
        std::string &word = *it;
		trimLeadingSpaces(word);
        trimTrailingSpaces(word);
    }
}

void	Request::_readRequestMassageBody( void )
{
	while(_lineIndex < request_v.size()) 
	{
		_body +=  request_v[_lineIndex];
		_lineIndex++;
	}
}

void	Request::_collectQuery(std::string path_l)
{
	size_t 		start = path_l.find('?', 0);

	if (start != std::string::npos)
	{
		start = start + 1;
		_query_string = path_l.substr(start, path_l.length());
	}
}

void	Request::updateRequest(std::string request)
{
	_updateRequestToVector(request);
	if (_status == IN_REQUEST_LINE)
		_updateFromRequestLine();
	if (_status == IN_HEADER_LINE)
		_updateFromHeaderLine();
	if (_status == IN_CRLF_LINE)
	{
		_lineIndex++;
		_bodyIndex = _lineIndex;
		_status = IN_BODY_LINE;
	}
	if (_status == IN_BODY_LINE)
		_updateAfterHeaderLine();
	if(_isEndRead())
	{
		std::cout << "update request call" << std::endl;
		std::cout << "_contentLength = " << _contentLength << std::endl; 
		_status = END_REQUEST_MSG; 
	}
}

void	Request::_updateRequestToVector(std::string &request)
{
    std::string::size_type		end = 0;
	std::string::size_type		start = 0;
	std::vector<std::string>	updateReq;
	std::string					lessReq;

	if (request_v.back().find('\n', 0) != std::string::npos)
	{
		updateReq = lineToVector(request);
		vectorPlueVector(request_v, updateReq);
	}
	else
	{
		if ((end = request.find('\n', 0)) != std::string::npos)
		{
			request_v.back() += request.substr(0, end + 1);
			start = end + 1;
			lessReq = request.substr(start, request.size() - end);
			updateReq = lineToVector(lessReq);
			vectorPlueVector(request_v, updateReq);
		}
		else
		{
			request_v.back() += request;
		}
	}
}

void	Request::_updateFromRequestLine( void )
{
	std::string					req_l;
	std::vector<std::string>	word_v;

	if (request_v[_lineIndex].find('\n', 0) == std::string::npos)
		return;
	req_l = request_v[_lineIndex];
	word_v = splitToVector(req_l, ' ');
	if (word_v.size() != 3)
	{
		_reqErr = BAD_REQUESTLINE;
		return ;
	}
	_trimSpaceWordVector(word_v);
	if(!_methodCheckNCollect(word_v[0]))
		return ;
	_path = word_v[1];
	_collectQuery(word_v[1]);
	if(!_httpVersionCheckNCollect(word_v[2]))
		return ;
	_lineIndex++;
	_status = IN_HEADER_LINE;
	return ;
}

void	Request::_updateFromHeaderLine( void )
{
	std::string					header_l;
	std::vector<std::string>	word_v;

	if (_lineIndex >= request_v.size())
		return ;
	while(_lineIndex < request_v.size() \
		&& request_v[_lineIndex] != "\n" \
		&& request_v[_lineIndex] != "\r\n" \
		&& request_v[_lineIndex] != "\r") 
	{
		if (request_v[_lineIndex].find('\n', 0) == std::string::npos \
		&& request_v[_lineIndex].find(':', 0) == std::string::npos)
			return ;
		header_l = request_v[_lineIndex];
		word_v = headerSplit(header_l, ':');
		if (word_v.size() != 2)
			return ;
		_trimSpaceWordVector(word_v);
		trimNewline(word_v[1]);
		_headerField_map[word_v[0]] = word_v[1];
		_lineIndex++;
	}
	if (request_v[_lineIndex - 1].find('\n', 0) == std::string::npos)
		_lineIndex--;
	if (_lineIndex < request_v.size() && (request_v[_lineIndex] == "\n" \
		|| request_v[_lineIndex] == "\r\n" \
		|| request_v[_lineIndex] == "\r"))
		_status = IN_CRLF_LINE;
}

void	Request::_updateAfterHeaderLine( void )
{
    std::string::size_type end = _body.size();
    while (end > 0 && (_body[end - 1] == '\n'))
        --end;
    if (end > 0 && end < _body.size())
	{
        _body = _body.substr(0, end);
    }
	else if (end == 0)
		_body = "";
	while(_lineIndex < request_v.size()) 
	{
		_body +=  request_v[_lineIndex];
		if (request_v[_lineIndex].find('\n', 0) != std::string::npos)
		{
			_lineIndex++;
		}
		else
			break;
	}
}

int		Request::_reqErrMsg( void )
{
	if (_reqErr == EMPTHY_REQUEST)
	{
		std::cout << "ERROR: REQUEST IS EMPTHY" << std::endl;
		return (1);
	}
	else if (_reqErr == INVALID_METHOD)
	{
		std::cout << "ERROR: INVALID METHOD" << std::endl;
		return (1);
	}
	else if (_reqErr == BAD_REQUESTLINE)
	{
		std::cout << "ERROR: BAD REQUEST LINE" << std::endl;
		return (1);
	}
	else if (_reqErr == METHOD_OUTOFRANGE)
	{
		std::cout << "ERROR: METHOD OUT OF RANGE" << std::endl;
		return (1);
	}
	else if (_reqErr == BAD_HEADERFIELD)
	{
		std::cout << "ERROR: BAD HEADER FIELD" << std::endl;
		return (1);
	}
	return (0);
}

std::ostream &operator <<(std::ostream &os, const Request &req)
{
	    os << std::endl;
        os << "Method: " << req._method << std::endl;
        os << "Path: " << req._path << std::endl;
        os << "Query: " << req._query_string << std::endl;
        os << "Version: " << req._http_version << std::endl;
        std::map<std::string, std::string> header = req.getHeaderFieldMap();
        std::map<std::string, std::string>::iterator it;
        for (it = header.begin(); it != header.end(); ++it) 
        {
            os << "Key: " << it->first << ", Value: " << it->second << std::endl;
        }
        os << "Body: " << req._body << std::endl;
		os << "Status: " << req.getStatus() << std::endl;
		return (os);
}