#include "Utils.hpp"
#include <iostream>

std::vector<std::string> splitToVector(const std::string& str, char delimiter) 
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while ((end = str.find(delimiter, start)) != std::string::npos)
	{
        if (end != start)
            tokens.push_back(str.substr(start, end - start));
        if(end == str.length() - 1)
            return tokens;
        start = end + 1;
    }
    if (start < str.length())
        tokens.push_back(str.substr(start));
    return tokens;
}

std::vector<std::string> headerSplit(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::string::size_type start = 0;
    std::string::size_type end = 0;
    bool    stop = false;

    while (((end = str.find(delimiter, start)) != std::string::npos && stop == false))
	{
        if (end != start)
        {
            tokens.push_back(str.substr(start, end - start));
            stop = true;
        }
        if(end == str.length() - 1)
            return tokens;
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
        std::cout << "tew1\n";
        tokens.push_back(str.substr(start, end - start + 1));
        start = end + 1;
    }
	if (start < str.size())
	{
        std::cout << "tew2\n";
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