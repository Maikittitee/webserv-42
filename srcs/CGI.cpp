# include "../include/CGI.hpp"

CGI::CGI(void){}

CGI::~CGI(void){}




int CGI::rout(Client &client, Server &server)
{
	client.location = _select_location(*client.request, server);
	if (!client.location)
		std::cout << RED << "can't find matching location" << RESET << std::endl;
	else {
		std::cout << client.location;
	}
	if (false && !_is_allow_method(client.request->_method, *client.location)) {
		return (403);
		//method not allow 
	}
	if (client.location->ret.have){
		// redirect
		client.request->_path = client.location->ret.text;
		return (client.location->ret.code);
	}
	if (client.request->_method == DELETE){
		// delete file 
	}
	client.request->_path = client.location->root + client.request->_path;
	if (!client.location->autoIndex && _is_path(client.request->_path)){
		std::string tmp_file;
		for (int i = 0; i < client.location->index.size(); i++){
			tmp_file = client.request->_path + client.location->index[i];
			if (access(tmp_file.c_str(), F_OK) == 0){
				client.request->_path = tmp_file;
				break;
			}
		}
	}
	// check access
	if (access(client.request->_path.c_str(), F_OK) != 0)
		return (404);
	if (client.location->autoIndex){
		// maybe send 1000
		return (1000);
	}
	if (client.location->cgiPass) { // <=============== HELLO PTEW
		// cgi

		// is end file ? N: fork -> read ต่อ -> รัน cgi file -> 
		// send fd
		// return (fd child)
	}
	return (200);

}

std::string CGI::readfile(std::string filename, Server &server, int return_code)
{
	Response response;

	if (return_code >= 400)
		// check in error list and read error file

	std::cout << "path read is " << filename << std::endl;
	response._body = response.get_body_from_file(filename);
	response.genarate_header();
	return (response.get_response_text());
	

}
		
std::string CGI::readfile(int fd) // fd of child (cgi) process <=============== HELLOOOOO PTEW
{
	// อ่าน fd ของ child process แล้วเก็๋บไว้ใน buffer 
	// response.body = buffer
	// genate_header()
	// return (response txt)
	// close fd
	return ("READFILE FROM FD");
}

bool CGI::_is_path(std::string path)
{
	if (path[path.size() - 1] == '/')
		return (true);
	return (false);
}

std::string CGI::_get_only_path(std::string path)
{
	std::size_t found;
	std::string str;

	found = path.find_last_of("/\\");
	str = path.substr(0, found);
	std::cout << "cut " << str << std::endl;
	return (str);
}

Location* CGI::_compare_location(std::string str, std::map<std::string, Location> &conf)
{
	std::map<std::string, Location>::iterator it;

	std::cout << conf;
	for (it = conf.begin(); it != conf.end(); it++){
		if (it->first == str){
			std::cout << YEL << "checked with " << it->first << RESET << std::endl;
			return (&(it->second));
		}
	}
	std::cout << "not match any location" << std::endl;
	return (NULL);
}

Location* CGI::_select_location(Request &request, Server &server)
{
	bool match = false;
	Location *select_loc;
	

	std::cout << YEL << "request path is " << request._path << RESET << std::endl;
	std::cout << YEL << "[ expect format: \"haha/eiei/index.html\" ]" << RESET << std::endl;;

	std::string only_path = "/" + _get_only_path(request._path);
	while (!match){
		if ((select_loc = _compare_location(only_path, server._config)) != NULL){
			std::cout << YEL << "config match!" << RESET << std::endl;
			match = true;
			// std::cout << *select_loc << std::endl;
		}
		else
		{
			only_path = _get_only_path(only_path);

		}
		if (only_path == ""){
			std::cout << "get / location" << std::endl;
			select_loc = &server._config["/"];
			break;
		}

	}
	return (select_loc);
}

bool	CGI::_is_allow_method(t_method method, Location &location)
{
	for (int i = 0; i < location.allowMethod.size(); i++){
		if (method == location.allowMethod[i])
			return (true);
	}
	return (false);
}