
#include "../include/Utils.hpp"

std::string concat_path(std::string s1, std::string s2)
{
	std::string ret;
	std::string mid = "/";

	if (s1.back() == '/' || s1.front() == '/')
		mid = "";
	ret = s1 + mid + s2;
	replace_str(ret, "//", "/");
	return (ret);
}

bool readFile(std::string &buff, std::string const &filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	int length;
	file.seekg(0, std::ios::end);

	if (!file.is_open()){
		std::cerr << "Can't Open The File" << std::endl;
		return (false);
	}
	length = file.tellg();

	std::cout << RED << length << RESET << std::endl; 

	char *buffer = new char[length];
	file.seekg(0, std::ios::beg);
	file.read(buffer, length);
	file.close();
	buff = buffer; // ?????
	return (true);

}

void	replace_str(std::string &str, std::string s1, std::string s2)
{
	size_t	found_pos = 0;
	int		index = 0;

	if (s1.empty() || s2.empty())
		return ;
	while (true)
	{
		found_pos = str.find(s1, index);
		if (found_pos > str.size())
			break ;
		str.erase(found_pos, s1.length());
		str.insert(found_pos, s2);
		index = found_pos + s2.length();
	}
}


std::vector<std::string> splitToVector(const std::string& str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while ((end = str.find(delimiter, start)) != std::string::npos)
	{
        if (end != start)
            tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }
    if (start < str.length())
        tokens.push_back(str.substr(start));
    return tokens;
}

std::vector<std::string> lineToVector(const std::string& str) 
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while ((end = str.find('\n', start)) != std::string::npos)
	{
        tokens.push_back(str.substr(start, end - start + 1));
        start = end + 1;
    }
	if (start < str.size())
	{
		tokens.push_back(str.substr(start, str.size() - start));
	}
    return tokens;
}

void	trimLeadingSpaces(std::string& str) 
{
	size_t start = str.find_first_not_of(' ');
	if (start != std::string::npos)
		str = str.substr(start);
}

void	trimTrailingSpaces(std::string& str)
{
    size_t end = str.find_last_not_of(' ');
    if (end != std::string::npos)
        str = str.substr(0, end + 1);
}

void	trimSpaces(std::string& str) 
{
    trimLeadingSpaces(str);
    trimTrailingSpaces(str);
}

std::ostream &operator << (std::ostream &os, const t_method &method)
{
	switch (method)
	{
		case ELSE:
			os << "ELSE";
			break;
		case GET:
			os << "GET";
			break;
		case POST:
			os << "POST";
			break;
		case DELETE:
			os << "DELETE";
			break;
		case HEAD:
			os << "HEAD";
			break;
		default:
			os << "not a method";
			break;
	}
	return (os);
}

bool is_directory(std::string &str)
{
	struct stat s;

	if (access(str.c_str(), F_OK) != 0)
		return (false);

	if (stat(str.c_str() ,&s) == 0)
	{
		if(s.st_mode & S_IFREG) // if it's file
		{
			return (false);
		}
		else if (s.st_mode & S_IFDIR) 
		{
			return (true);
		} 
		return (false);
	}
	return (false);
}

void	vectorPlueVector(std::vector<std::string>& v1, std::vector<std::string>& v2)
{
    for (std::vector<std::string>::iterator it = v2.begin(); it != v2.end(); ++it) 
	{
        v1.push_back(*it);
    }	
}

void    trimNewline(std::string &str)
{
    // Find the first non-newline character from the beginning
    std::string::size_type start = 0;
    while (start < str.size() && (str[start] == '\n' || str[start] == '\r')) {
        ++start;
    }

    // Find the last non-newline character from the end
    std::string::size_type end = str.size();
    while (end > start && (str[end - 1] == '\n' || str[end - 1] == '\r')) {
        --end;
    }

    // If there are leading or trailing newlines, modify the string in place
    if (start > 0 || end < str.size()) {
        str = str.substr(start, end - start);
    }
}