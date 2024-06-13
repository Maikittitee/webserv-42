#include "../include/Response.hpp"

Response::Response(void) {}

Response::~Response(void) {}

static bool is_allow_method(t_method method, Location &conf)
{
	int i = 0;
	while (i < conf.allowMethod.size()){
		if (method == conf.allowMethod[i])
			return (true);
		i++;
	}
	return (false);
}

void	Response::receive_request(Request &request, Location &conf) // for body and return code
{
	std::string body;

	_return_code = 200;
	request._path = conf.root + request._path;
	replace_str(request._path, "//", "/");
	std::cout << "request path: " << request._path << std::endl;
	std::cout << "location: " << std::endl;
	std::cout << conf;
	
	// is allow mathod => N:405
	if (!is_allow_method(request._method, conf))
		_return_code = 405;

	//	is path => add index
	if (request._path[request._path.size() - 1] == '/'){
		std::string tmp_file;
		for (int i = 0; i < conf.index.size(); i++){
			tmp_file = request._path + conf.index[i];
			if (access(tmp_file.c_str(), F_OK) == 0){
				request._path = tmp_file;
				break;
			}
		}
	}
	
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
		set_body(get_body_from_file(request._path));
	}
	if (strlen(body.c_str()) > conf.cliBodySize){
		_return_code = 413;
	}
}

void Response::genarate_header()
{
	std::stringstream header;

	header << "HTTP/1.1 ";
	header << _return_code;
	header << " ";
	header << status_def();
	header << "\r\n";
	header << "Date: "; 
	header << get_date();
	header << "\r\n";
	if (!cgiPass){
		header <<  "Content-Type: ";
		header << _content_type;
		header << "\r\n";
	}
	// header << "Content-Length: ";
	// header << strlen(_body.c_str());
	// header << "\r\n";

	this->_header = header.str();


}

std::string Response::status_def(void)
{
	if (_return_code == 200)
		return ("OK");
	if (_return_code == 404)
		return ("NOT FOUND");
	if (_return_code == 405)
		return ("Method Not Allowed");
	if (_return_code == 403)
		return ("Forbidden");
	
	return ("ERROR");

}

std::string Response::get_response_text(void)
{
	std::stringstream response;

	response << _header;
	if (!cgiPass)
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

std::string Response::get_body_from_file(std::string filename)
{
	std::string body;
	
	readFile(body, filename.c_str());
	replace_str(body, "\n", "\r\n");

	return (body);

}

void		Response::set_body(std::string content)
{
	_body = content;
}
