#include "../include/Response.hpp"

Response::Response(void): cgiPass(false) 
{

}

Response::~Response(void) 
{
	
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

void Response::genarate_header(void)
{
	std::stringstream header;

	if (cgiPass)
		std::cout << "response from CGI" << std::endl;
	else 
		std::cout << "response not CGI" << std::endl;
	header << "HTTP/1.1 ";
	header << _return_code;
	header << " ";
	header << status_code_validate(_return_code);
	header << "\r\n";
	header << "Date: "; 
	header << get_date();
	header << "\r\n";
	std::cout << "cgiPass in gen header: " <<std::boolalpha << cgiPass << std::endl;
	if (!cgiPass){
		header << "Content-Type: ";
		header << _content_type;
		header << "\r\n";
	}
	if (_body.size()){
		header << "Content-Length: ";
		if (!cgiPass)
			header << _body.size();
		else 
			header << (_body.size() - _get_content_type_from_cgi_body(_body).size() - 2);
		header << "\r\n";

	}
	this->_header = header.str();
}

std::string Response::_get_content_type_from_cgi_body(std::string body)
{
	std::string ret;
	std::vector<std::string> vec;

	vec = splitToVector(body, '\n');
	for (int i = 0; i < vec.size(); i++){
		if (vec[i].find("Content-Type") != std::string::npos)
			return (vec[i]);
		if (vec[i].find("content-type") != std::string::npos)
			return (vec[i]);
		if (vec[i].find("Content-type") != std::string::npos)
			return (vec[i]);
		if (vec[i].find("content-Type") != std::string::npos)
			return (vec[i]);

	}
	return ("");
}

std::string Response::get_response_text(void)
{
	std::string response;

	genarate_header();
	response += _header;
	if (!cgiPass)
		response += "\r\n";
	response += _body;

	return (response);
}