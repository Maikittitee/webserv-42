#include "../include/Utils.hpp"

bool readFile(std::string &buff, std::string const &filename)
{
	std::ifstream file(filename);
	int length;
	file.seekg(0, std::ios::end);

	if (!file.is_open()){
		std::cerr << "Can't Open The File" << std::endl;
		return (false);
	}
	length = file.tellg();

	char *buffer = new char[length];
	file.seekg(0, std::ios::beg);
	file.read(buffer, length);
	file.close();
	buff = buffer;
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