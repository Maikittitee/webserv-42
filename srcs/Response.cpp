#include "../include/Response.hpp"

Response::Response(void) {}

Response::~Response(void) {}

void	Response::receive_request(Request &request, Location &conf) // for body and return code
{
	std::string body;

	_return_code = 200;
	
	// is allow mathod => N:405
	
	//	is path => add index
	
	//	is access file => N:404
	if (access(request._path.c_str(), F_OK) < 0){
		_return_code = 404;
	}
	//is cgi => y:do cgi
	if (conf.cgiPass){
		_return_code = -1;
	}
	else{
		std::cout << "readfile" << std::endl;;
		set_body(request._path);
	}
	if (strlen(body.c_str()) > conf.cliBodySize){
		_return_code = 413;
	}
}

void Response::genarate_header(void)
{
	std::stringstream header;

	header << "HTTP/1.1 ";
	header << _return_code;
	header << " ";
	header << status_def();
	header << "\r\n";
	header <<  "Content-Type: ";
	header << _content_type;
	header << "\r\n";
	header << "Date: "; 
	header << get_date();
	header << "\r\n";
	header << "Content-Length: ";
	header << strlen(_body.c_str());
	header << "\r\n";

	this->_header = header.str();


}

std::string Response::status_def(void)
{
	if (_return_code == 200)
		return ("OK");
	return ("ERROR");

}

std::string Response::get_response_text(void)
{
	std::stringstream response;

	response << _header;
	response << "\r\n";
	response << _body;

	return (response.str());

}


std::string Response::get_date(void)
{
	char buf[1000];
	std::string ret = "";
	time_t now = time(0);
	struct tm tm = *gmtime(&now);
	strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);

	int i = 0;
	while (buf[i])
		ret += buf[i++];
	return (ret);
}

void		Response::set_body(std::string filename)
{
	std::string body;
	
	readFile(body, filename.c_str());
	replace_str(body, "\n", "\r\n");

	_body = body;
}

void		Response::set_body(char *content)
{
	// pass
}