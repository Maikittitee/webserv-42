#include "Request.hpp"

Request::Request():
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

Request::Request(std::string request):
_lineIndex(0),
_path(""),
_http_version(""),
_body(""),
_query_string(""),
_method(NONE),
_reqErr(SUCESS_REQUEST),
write_fd(-1)
{
	request_v.clear();
	_method_map["GET"] = GET;
	_method_map["POST"] = POST;
	_method_map["DELETE"] = DELETE;
	_method_map["PUT"] = PUT;
	_method_map["HEAD"] = HEAD;
	if(!_collectRequestToVector(request))
		return (_reqErrMsg(_reqErr));
	if(!_readRequestLine())
		return (_reqErrMsg(_reqErr));
	// if(!_readRequestHeaderField())
	// 	return (_reqErrMsg(_reqErr));
	// if(!_readRequestMassageBody())
	// 	return (_reqErrMsg(_reqErr));
}

bool	Request::_collectRequestToVector(std::string &request)
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
	return true;
}

bool 	Request::_readRequestLine( void )
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
	_methodCheckNCollect(word_v[0]);
	_path = word_v[1];
	_httpVersionCheckNCollect(word_v[2]);
	lineIndex++;
	return true;
}

for (std::map<std::string, double>::iterator it = dataTable.begin(); it != dataTable.end(); ++it)
{
	int timestamp = dataToTimeStamp(it->first);
	int difference = std::abs(timestamp - targetTimestamp);
	if (difference < minDifference)
	{
		minDifference = difference;
		closestVal = it->second;
	}
}

bool	Request::_methodCheckNCollect(std::string methodInput)
{
	std::map<std::string, int>::iterator it = _method_map.find(methodInput);
	if (it != _method_map.end())
	{
		_method = _method_map[methodInput]
		return (true);
	}
	else
		_method = ELSE;
	_reqErr = METHOD_OUTOFRANGE;
	return (false);
}

// bool	Request::_readRequestHeaderField( void )
// {

// }

// bool	Request::_readRequestMassageBody( void )
// {

// }

// int		Request::_reqErrMsg( void )
// {

// }