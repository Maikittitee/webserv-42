#include "../include/Response.hpp"

Response::Response(int return_code, std::string body): _return_code(return_code), _body(body){
	std::cout << "response instant was created" << std::endl;
}



void Response::genarate_header(void)
{
	std::stringstream header;

	header << "HTTP/1.1 ";
	header << "200 OK\r\n";
	header <<  "Content-Type: text/html\r\n";
	// response += "Date: " + get_date() + "\r\n";
	header << "Content-Length: ";
	header << strlen(_body.c_str());
	header << "\r\n";

	_header = header.str();


}

std::string Response::status_def(void)
{

}

std::string Response::get_response_text(void)
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
	{
		ret += buf[i];
		i++;
	}
	return (ret);
}