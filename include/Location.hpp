#ifndef LOCATION_HPP
#	define LOCATION_HPP

#	include <iostream>
#	include <string>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <stdio.h>
#	include <stdlib.h>
#	include <unistd.h>
#	include "Server.hpp"
#	include "Utils.hpp"
class Server;

int	parsing_config(int ac, char **av, char **env);
std::string	ft_trim(std::string line, char c);
bool	ft_check_extension(char	*file);
std::string	ft_getvalue(std::string key, std::string line);
std::string ft_getkey(std::string txt);
std::string	ft_trim_ispace(std::string line);
bool	ft_getlocate(std::string key, std::string value, std::string sp_line);
bool	ft_check_locate(std::string key);


// typedef struct parsing
// {

// } ps;

struct return_t {
	bool		have;	// if there is a return 1 (true)
	short int	code;	// Status Code
	std::string	text;	// Option
};

class Location{
	public:
		Location();
		Location(std::string name);
		std::string name;		
		std::string value_lc;		
		int	_client_max;	
		int	_listen;	

		bool						cgiPass;
		bool						autoIndex;
		std::vector<t_method>		allowMethod;
		uint64_t					cliBodySize;
		std::string					root;
		std::vector<std::string>	index;
		return_t					ret;
		int							port;

		Location(const Location &other);
		
		Location& operator= (const Location &rhs);


		// Overload the << operator to print Location objects
		friend std::ostream& operator<<(std::ostream& os, const Location& loc)
		{
			os << loc._client_max << std::endl ;
   		    return os;
    	}
		// std::ostream& operator<<(std::ostream& os, const Location& location)
		// {
		// 	os << "cgi: " << std::boolalpha << location.cgiPass << std::endl;
		// 	os << "autoIndex: " << std::boolalpha << location.autoIndex << std::endl;
		// 	os << "allowMethod: " << location.allowMethod << std::endl;
		// 	os << "cliBodySize: " << location.cliBodySize << std::endl;
		// 	os << "root: " << location.root << std::endl;
		// 	os << "index: " << location.index << std::endl;
		// 	if (!location.ret.have)
		// 		os << "no return" << std::endl;
		// 	else 
		// 		os << "return: " << location.ret.code << " " << location.ret.text << std::endl;
		// 	return (os);
};

#endif

