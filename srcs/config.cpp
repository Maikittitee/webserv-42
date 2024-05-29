/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/29 16:33:18 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <cstring>
#include "../include/Server.hpp"


Server::Server()
{
	
}

Server::~Server()
{
	
}

std::string	ft_trim(std::string line, char c)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of(c);
	// std::cout << "start : " << start << std::endl;
	end = line.find_last_not_of(c);
	// std::cout << "end : " << end << std::endl;
	
	// std::string::npos is position that string doesn't match
	// end != 0 -> checks if there are any non-key characters at the end of the string.
	
	if (start != std::string::npos &&  end != 0)
		return (line.substr(start, end - start + 1));
	/* Incase string and char have 1 charater and same text*/
	if (start == std::string::npos && end == std::string::npos)
		return ("");
	return (line);	
}
bool	ft_check_extension(char	*file)
{
	char *tmp;

	tmp = strrchr(file, '.');
	if (strcmp(tmp, ".conf") == 0)
		return (true);
	return (false);
}
std::string	ft_getvalue(std::string key, std::string line)
{
	int			i;
	std::string	value;

	i = 0;
	value = "";
	if (key == "}")
		return("");
	while (line[i])
	{
		// while (isspace(line[i])) // escape space
		// 	i++;
		while (line[i] == key[i]) // escape key
			i++;
		while (line[i] && isspace(line[i]))
			i++;
		while ((line[i] != ';' || line[i] != '{' || line[i] != '}') && line[i])
		{
			value += line[i];
			// value.append(sp_line[i]);
			i++;
		}
		break;
	}
	return (value);
}

std::string ft_getkey(std::string sp_line)
{
	int	i;
	std::string key;
	
	key = "";
	i = 0;
	if (sp_line == "}")
	{	
		key = "}";
		return (key);
	}	
	while (sp_line[i]) // keep txt
	{
		if (sp_line[i] && (sp_line[i] == '{' || sp_line[i] == '}' || isspace(sp_line[i])))
			break;
		key += sp_line[i];
		i++;
	}
	return (key);
}

std::string	ft_trim_ispace(std::string line)
{
	char is_sp[5] = {'\t', '\n', '\v', '\f', '\r'};
	std::string	sp_line;
	int	i;
	
	i = 0;
	sp_line = ft_trim(line, ' ');
	while (i < 4)
	{
		sp_line = ft_trim(sp_line, is_sp[i]);
		i++;
	}
	return (sp_line);	
}

bool	ft_getlocate(std::string key, std::string value, std::string sp_line)
{
	bool locate;
	
	locate = true;
	if (key != "location")
		return (false);
	// std::cout << "[key_locate]   : |" << key << "|" << std::endl;
	// std::cout << "[value_locate] : |" << value  << "|" << std::endl;
	// std::cout << "sp_line : " << sp_line << std::endl;
	
	// if check key == gzip , include -> link to other function
	if (key == "}") 
		locate = false;
	return (locate);
}

bool	ft_check_locate(std::string key)
{
	if (key == "root" || key == "return" \
	|| key == "index" || key == "autoindex"
	|| key == "cgi_pass" || key == "client_max_body_size")
		return (true);
	return (false);
}

void	ft_prt_locate(Location location)
{
	std::cout << "cgiPass : " << location.cgiPass << std::endl;
	std::cout << "autoIndex :" << location.autoIndex << std::endl;
	std::cout << "cliBodySize : " << location.cliBodySize << std::endl;
	std::cout << "root : " << location.root << std::endl;
	// std::cout << 
}

// Location	ft_init_locate(void)
// {
// 	Location	locate;
	
// 	locate.cgiPass = 0;
// 	locate.autoIndex = 0;
// 	locate.cliBodySize = 0;
// 	locate.root = "";
// 	locate.ret = {0, 0, ""};
// 	return (locate);
// }


// Location	ft_locate(std::string value)
// {
// 	Location location;

// 	// location.autoIndex = stoi(value);
// 	location = ft_init_locate();
// 	// if (value == "cgiPass")
// 		// location.cgiPass = value;
// 	// location
	
// 	return (location);
// }

int	parsing_config(int ac, char **av)
{
	std::string	line;
	std::string	file;
	std::string	key;
	std::string	value;
	std::string	sp_line;
	bool		locate;
	// Location	location;
	Server		server;
	
	// server._config["name"] = Location.
	// std::cout << "parsing config" << std::endl;	
	if (ac != 2)
		return(std::cerr << "Error : Expected 2 arguments" << std::endl, 0);
	std::ifstream input_file(av[1]);
	if (input_file.is_open() == false)
		return(std::cerr << "Error : Could not open file : " << av[1] << std::endl, 0);
	if (ft_check_extension(av[1]) == false)
		return (std::cerr << "Error : extension file" << std::endl, 0);
	int i = 0;
	locate = true;
	while (std::getline(input_file, line)) // return integer representing the status  of read not actual content of the line
	{
		// write new code for trim isspace
		// std::cout << key << " | " << value << std::endl;
		sp_line = ft_trim_ispace(line);
		// std::cout << "|" << sp_line << "|" << std::endl;
		key = ft_getkey(sp_line);
		// if (key == "location")
		// 	locate = true;
		if (key.empty())
			continue;
		else
			value = ft_getvalue(key, sp_line);
		// std::cout << "[key]   : |" << key << "|" << std::endl;
		// std::cout << "[value] : |" << value  << "|" << std::endl;
		// if (ft_check_locate(key) == true && locate == true) // check prob word of locate
			// locate = ft_getlocate(key, value, sp_line);
		// std::cout << key << " : " << value << std::endl;
		// server._config[key] = Location(value);
		server._config.insert(std::pair<std::string, Location>(key, Location(value)));
		// server._config.insert({key, ft_locate(value)});
		// ft_prt_locate()
		// i++;
		// if (i == 3)
			// break;
	}
	// for (const auto& pair : server._config)
	// {
    //     // std::cout << pair.first << '\n';
    //     std::cout << pair.first << " => " << pair.second ;
    // }

	std::map<std::string, Location>::iterator it;
	for (it = server._config.begin(); it != server._config.end(); it++)
	{
		std::cout << it->first << it->second;
	}
	input_file.close();
	return (0);	
}

int main(int ac, char **av)
{
	parsing_config(ac, av);	
}