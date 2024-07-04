#ifndef WS_UTILS_HPP
# define WS_UTILS_HPP

#	include <ostream>
#	include <vector>

typedef enum e_version{
	HTTP09, // HTTP/0.9
	HTTP10, // HTTP/1.0
	HTTP11, // HTTP/1.1
	HTTP00, // else
} t_version;

void						trimTrailingSpaces(std::string& str);
void						trimLeadingSpaces(std::string& str) ;
void						trimSpaces(std::string& str) ;
void						trimNewline(std::string &str);
std::vector<std::string>	splitToVector(const std::string& str, char delimiter);
std::vector<std::string> 	lineToVector(const std::string& str);
std::vector<std::string> 	headerSplit(const std::string& str, char delimiter);
void						vectorPlueVector(std::vector<std::string>& v1, std::vector<std::string>& v2);

#endif