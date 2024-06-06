#include "../include/RequestHttp.hpp"

RequestHttp::RequestHttp():
_lineIndex(0),
_path(""),
_http_version(""),
_body(""),
_query_string(""),
_reqErr(SUCESS_REQUEST),
_method(NONE),
write_fd(-1)
{
	request_v.clear();
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;
}

RequestHttp::RequestHttp(std::string request):
_lineIndex(0),
_path(""),
_http_version(""),
_body(""),
_query_string(""),
_reqErr(SUCESS_REQUEST),
_method(NONE),
write_fd(-1)
{
	request_v.clear();
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;
	if(!_collectRequestToVector(request))
		_reqErrMsg(_reqErr);
	if(!_readRequestLine())
		_reqErrMsg(_reqErr);
	if(!_readRequestHeaderField())
		_reqErrMsg(_reqErr);
	_readRequestMassageBody()
}

bool	RequestHttp::_collectRequestToVector(std::string &request)
{
	std::istringstream	iss_request(request);
	std::string 		line;

	if (!request)
	{
		_reqErr = EMPTHY_REQUEST;
		return false;
	}
	while (std::getline(iss_request, line))
		request_v.push_back(line);
	_trimSpaceWordVector(request_v);
	return true;
}

bool 	RequestHttp::_readRequestLine( void )
{
	std::string					req_l;
	std::vector<std::string>	word_v;

	req_l = request_v[lineIndex];
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
	collectQuery(word_v[1]);
	if(_httpVersionCheckNCollect(word_v[2]))
		return (false);
	lineIndex++;
	return true;
}

bool	RequestHttp::_methodCheckNCollect(std::string &methodInput)
{
	std::map<std::string, int>::iterator it = _method_map.find(methodInput);
	if (it != _method_map.end())
	{
		_method = _method_map[methodInput];
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
		_reqErr = BAD_HTTPREQUEST
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

	while(lineIndex < request_v.size() && request_v[lineIndex] != "/n") 
	{
		header_l = request_v[lineIndex];
		word_v = splitToVector(header_l, ':');
		if (word_v.size() > 2)
		{
			_reqErr = BAD_HEADERFIELD;
			return false;
		}
		_trimSpaceWordVector(word_v);
		_headerField_map[word_v[0]] = word_v[1];
		lineIndex++;
	}
}

void	RequestHttp::_trimSpaceWordVector(std::vector<std::string> &word_v)
{
	for (std::string& word : word_v)
		trimTrailingSpaces(trimLeadingSpaces(word));
}

void	RequestHttp::_readRequestMassageBody( void )
{
	while(lineIndex < request_v.size()) 
	{
		_body +=  request_v[lineIndex];
		lineIndex++;
	}	
}

void	RequestHttp::collectQuery(std::string body_l)
{
	size_t start = body_l.find_first_not_of('?');
	if (start != std::string::npos)
		str = str.substr(start);
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
	std::cout << "SUCESS REQUEST" << std::endl;
	return (0);
}