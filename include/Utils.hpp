#ifndef WS_UTILS_HPP
# define WS_UTILS_HPP

#	include <iostream>
#	include <string>
#	include <fstream>

typedef enum e_method{
			ELSE,
			GET,
			POST,
			DELETE,
			HEAD,
			PUT,
			NONE
} t_method;

typedef enum e_version{
	HTTP09, // HTTP/0.9
	HTTP10, // HTTP/1.0
	HTTP11, // HTTP/1.1
	HTTP00, // else
} t_version;

bool	readFile(std::string &buff, std::string const &filename);
void	replace_str(std::string &str, std::string s1, std::string s2);

#endif
