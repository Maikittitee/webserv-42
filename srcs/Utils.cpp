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
        if (end != start)
            tokens.push_back(str.substr(start, end - start));
		else
			tokens.push_back("\n");
        start = end + 1;
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

std::string status_code_validate(int status_code)
{
	switch (status_code) {
        case 100: return "Continue";
        case 101: return "Switching Protocols";
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 203: return "Non-Authoritative Information";
        case 204: return "No Content";
        case 205: return "Reset Content";
        case 206: return "Partial Content";
        case 300: return "Multiple Choices";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 303: return "See Other";
        case 304: return "Not Modified";
        case 305: return "Use Proxy";
        case 307: return "Temporary Redirect";
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 402: return "Payment Required";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 406: return "Not Acceptable";
        case 407: return "Proxy Authentication Required";
        case 408: return "Request Timeout";
        case 409: return "Conflict";
        case 410: return "Gone";
        case 411: return "Length Required";
        case 412: return "Precondition Failed";
        case 413: return "Payload Too Large";
        case 414: return "URI Too Long";
        case 415: return "Unsupported Media Type";
        case 416: return "Range Not Satisfiable";
        case 417: return "Expectation Failed";
        case 426: return "Upgrade Required";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 504: return "Gateway Timeout";
        case 505: return "HTTP Version Not Supported";
        default:  return "Unknown Status Code";
    }
}