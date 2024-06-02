#include "RequestHttp.hpp"

RequestHttp::RequestHttp():
_lineIndex(0),
_reqErr(SUCESS_REQUEST),
_method(NONE),
_path(""),
_http_version(HTTP00),
_body(""),
_query_string(""),
write_fd(-1)
{
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;
}

RequestHttp::RequestHttp(std::string request):
_lineIndex(0),
_reqErr(SUCESS_REQUEST),
_method(NONE),
_path(""),
_http_version(HTTP00),
_body(""),
_query_string(""),
write_fd(-1)
{
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;
	if(!_collectRequestToVector(request))
		_reqErrMsg();
	if(!_readRequestLine())
		_reqErrMsg();
	if(!_readRequestHeaderField())
		_reqErrMsg();
	_readRequestMassageBody();
}

bool	RequestHttp::_collectRequestToVector(std::string &request)
{
	std::string 		line;

	if (request.empty())
	{
		_reqErr = EMPTHY_REQUEST;
		return false;
	}
	request_v = lineToVector(request);
    std::vector<std::string>::iterator it;
	return true;
}

bool 	RequestHttp::_readRequestLine( void )
{
	std::string					req_l;
	std::vector<std::string>	word_v;

	req_l = request_v[_lineIndex];
	word_v = splitToVector(req_l, ' ');
	if (word_v.size() != 3)
	{
		_reqErr = BAD_REQUESTLINE;
		return false;
	}
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

bool	RequestHttp::_methodCheckNCollect(std::string &methodInput)
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

bool	RequestHttp::_httpVersionCheckNCollect(std::string word)
{
	std::vector<std::string>	version_v;

	version_v = splitToVector(word, '/');
	_trimSpaceWordVector(version_v);
	if(version_v[0] != "HTTP")
	{
		_reqErr = BAD_HTTPREQUEST;
		return (false);
	}
	if(version_v[1] == "0.9")
		_http_version = HTTP09;
	else if(version_v[1] == "1.0")
		_http_version = HTTP10;
	else if(version_v[1] == "1.1")
		_http_version = HTTP11;
	else
		_http_version = HTTP00;
	return (true);
}

bool	RequestHttp::_readRequestHeaderField( void )
{
	std::string					header_l;
	std::vector<std::string>	word_v;

	while(_lineIndex < request_v.size() && request_v[_lineIndex] != "\n") 
	{
		header_l = request_v[_lineIndex];
		word_v = splitToVector(header_l, ':');
		if (word_v.size() > 2)
		{
			_reqErr = BAD_HEADERFIELD;
			return false;
		}
		_trimSpaceWordVector(word_v);
		_headerField_map[word_v[0]] = word_v[1];
		_lineIndex++;
	}
	_lineIndex++;
	return true;
}

void	RequestHttp::_trimSpaceWordVector(std::vector<std::string> &word_v)
{
    for (std::vector<std::string>::iterator it = word_v.begin(); it != word_v.end(); ++it)
    {
        std::string &word = *it;
		trimLeadingSpaces(word);
        trimTrailingSpaces(word);
    }
}

void	RequestHttp::_readRequestMassageBody( void )
{
	while(_lineIndex < request_v.size()) 
	{
		_body +=  request_v[_lineIndex];
		_lineIndex++;
	}	
}

void	RequestHttp::_collectQuery(std::string path_l)
{
	size_t 		start = path_l.find('?', 0) + 1;

	std::cout << "start = " << start << "\n";
	if (start != std::string::npos)
		_query_string = path_l.substr(start, path_l.length());
}

int		RequestHttp::_reqErrMsg( void )
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