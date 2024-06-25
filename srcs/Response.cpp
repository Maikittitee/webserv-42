#include "../include/Response.hpp"

Response::Response(void): cgiPass(false) {}

Response::~Response(void) {}

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

void Response::genarate_header(void)
{
	std::stringstream header;

	header << "HTTP/1.1 ";
	header << _return_code;
	header << " ";
	header << status_code_validate(_return_code);
	header << "\r\n";
	header << "Date: "; 
	header << get_date();
	header << "\r\n";
	if (!cgiPass){
		header << "Content-Type: ";
		header << _content_type;
		header << "\r\n";
	}
	if (_body.size()){
		header << "Content-Length: ";
		header << _body.size();
		header << "\r\n";
	}

	this->_header = header.str();
}

std::string Response::get_response_text(void)
{
	std::string response;

	response += _header;
	if (!cgiPass)
		response += "\r\n";
	response += _body;

	return (response);

}