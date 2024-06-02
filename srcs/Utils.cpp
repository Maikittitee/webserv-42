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

// std::ostream &operator << (std::ostream &os, const t_method &method)
// {
// 	switch (method)
// 	{
// 		case ELSE:
// 			os << "ELSE";
// 			break;
// 		case GET:
// 			os << "GET";
// 			break;
// 		case POST:
// 			os << "POST";
// 			break;
// 		case DELETE:
// 			os << "DELETE";
// 			break;
// 		case HEAD:
// 			os << "HEAD";
// 			break;
// 		default:
// 			os << "not a method";
// 			break;
// 	}
// 	return (os);
// }