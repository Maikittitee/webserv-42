# include "../include/CGI.hpp"

CGI::CGI(void){}

CGI::~CGI(void){}


bool CGI::rout(Client &client, Server &server)
{
	client.location = _select_location(*client.request, server);
	if (!_is_allow_method(client.request->_method, server))
		// method not allow 




	return (true);

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
		if (it->first == str)
			return (&(it->second));
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
		if (select_loc = _compare_location(only_path, server._config)){
			std::cout << YEL << "config match!" << RESET << std::endl;
			match = true;
			std::cout << *select_loc << std::endl;
		}
		else
			only_path = _get_only_path(only_path);

	}

}

bool	CGI::_is_allow_method(t_method method, Server &server)
{
	Location location = server._config["def"];

	return (true);
}