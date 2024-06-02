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
} t_method;

bool	readFile(std::string &buff, std::string const &filename);
void	replace_str(std::string &str, std::string s1, std::string s2);

#endif


std::ostream &operator << (std::ostream &os, const t_method &method);