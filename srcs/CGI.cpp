# include "../include/CGI.hpp"

CGI::CGI(void){}

CGI::~CGI(void){}




int CGI::rout(Client &client, Server &server)
{
	client.location = _select_location(*client.request, server);
	if (!_is_allow_method(client.request->_method, *client.location)) {
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
	if (client.location->autoIndex){
		// auto index
	}
	if (client.location->cgiPass){
		// cgi
	}


	





	return (true);

}

bool _is_path(std::string path)
{
	if (path[path.size() - 1] == '/')
		return (true);
	return (false);
}

std::string CGI::_get_only_path(std::string path)
{
	std::size_t found;

	found = path.find_last_of("/\\");
	return (path.substr(0, found));
}

Location* CGI::_compare_location(std::string str, std::map<std::string, Location> &conf)
{
	std::map<std::string, Location>::iterator it;

	for (it = conf.begin(); it != conf.end(); it++){
		if (it->first == str){
			std::cout << YEL << "checked with " << it->first << RESET << std::endl;
			return (&(it->second));

		}
	}
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
		std::cout << YEL << "only_path is " <<  only_path << RESET << std::endl;
		if ((select_loc = _compare_location(only_path, server._config)) != NULL){
			std::cout << YEL << "config match!" << RESET << std::endl;
			match = true;
			// std::cout << *select_loc << std::endl;
		}
		else
			only_path = _get_only_path(only_path);
		if (only_path == ""){
			std::cout << "/ ja" << std::endl;
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