# include "../include/CGI.hpp"

CGI::CGI(void){}

CGI::~CGI(void){}


bool CGI::rout(Client &client, Server &server)
{
	if (!_is_allow_method(client.request->_method, server))
		// method not allow 




	return (true);

}

bool	CGI::_is_allow_method(t_method method, Server &server)
{
	Location location = server._config["def"];
}