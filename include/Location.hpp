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

enum
{
	DEFAULT1,
	LOCATION,
	
};

class Server;

int	parsing_config(int ac, char **av, char **env);
std::string	ft_trim(std::string line, char c);
bool	ft_check_extension(char	*file);
std::string	ft_getvalue(std::string key, std::string line);
std::string ft_getkey(std::string txt);
std::string	ft_trim_ispace(std::string line);
bool	ft_getlocate(std::string key, std::string value, std::string sp_line);
bool	ft_check_locate(std::string key);

// count line that it doesn't have new line -> fill data
typedef struct s_test
{
	std::string key;
	std::string value;
	int			locate;  // true false
} t_test;


// typedef struct s_dfconf
// {
// 	uint64_t	cliBodySize;
// 	uint64_t	listen;
// 	std::string	server_name;
// 	std::string	root;

// 	// std::string key;
// 	// std::string value;
// 	// int			locate;  // true false
// } t_dfconf;

// struct dfconf
// {
// 	uint64_t	cliBodySize;
// 	uint64_t	listen;
// 	std::string	server_name;
// 	std::string	root;

// 	// std::string key;
// 	// std::string value;
// 	// int			locate;  // true false
// } ;

// class Dfconf
// {
// 	public:
// 		Dfconf();
// 		~Dfconf();

// 		// int client_max_body_size;
// 		// int listen;
// 		uint64_t	cliBodySize;
// 		uint64_t	listen;

// 		std::string	server_name;
// 		std::string root;

// 		std::vector<std::string> index;
// 		std::vector<std::string> limit_except;
// 		std::vector<std::string> error_page;
// } ;

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
		// int	_client_max;	
		int	_listen;	

		bool						cgiPass;
		uint64_t					cliBodySize;
		bool						autoIndex;
		std::vector<t_method>		allowMethod;
		std::string					root;
		std::vector<std::string>	index;
		return_t					ret;
		int							port;

		Location(const Location &other);
		Location& operator= (const Location &rhs);

};

std::ostream& operator<<(std::ostream& os, const Location& loc);

// friend std::ostream& operator<<(std::ostream& os, const Location& loc)
// std::ostream& operator<<(std::ostream& os, const Location& loc)
// {
// 	os << "[client_max] : " << loc._client_max << std::endl ;
//    	return os;
// }
#endif

