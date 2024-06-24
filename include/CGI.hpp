#ifndef CGI_HPP
#	define CGI_HPP

#	include "Common.hpp"
#	include "Server.hpp"
#	include "Client.hpp"
#	include "Response.hpp"
#	include "Mime.hpp"

class Server;

class Client;

class Response;

class Mime;

typedef enum e_res_type{
	STATUS_CODE_RES, 
	FORKING_RES,
	DELETE_RES,
	AUTO_INDEX_RES,
	HEAD_RES
} t_res_type;

typedef struct s_cgi_return{
	t_res_type type;
	int			status_code;

} t_cgi_return;

class CGI{
	public:
		CGI(void);
		~CGI(void);
		
		Response response;
		Mime		_mime;

		t_cgi_return rout(Client &client, Server &server);
		Response& readfile(Client &client, Server &server, t_cgi_return cgi_return);
		std::string	get_response(void);

	// private:
		bool	_is_allow_method(t_method method, Location &location);
		Location* _select_location(Request & , Server &);
		Location* _compare_location(std::string str, std::map<std::string, Location> &conf);
		std::string _get_only_path(std::string path);
		bool _is_path(std::string path);
		Response&	_delete_method(Client &client);
		Response&	_auto_indexing(Client &client, Server &server);
};

std::ostream& operator <<(std::ostream &os, const t_res_type &res_type);

std::ostream& operator <<(std::ostream &os, const t_cgi_return &cgi_ret);

#endif