#ifndef WS_UTILS_HPP
# define WS_UTILS_HPP

# 	include "Common.hpp"

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

bool						readFile(std::string &buff, std::string const &filename);
void						replace_str(std::string &str, std::string s1, std::string s2);
void						trimTrailingSpaces(std::string& str);
void						trimLeadingSpaces(std::string& str) ;
void						trimSpaces(std::string& str) ;
std::vector<std::string>	splitToVector(const std::string& str, char delimiter);
std::vector<std::string> 	lineToVector(const std::string& str);
std::ostream &operator << (std::ostream &os, const t_method &method);
bool is_directory(std::string &str);
#endif
