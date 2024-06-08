/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/06/09 01:52:06 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <cstring>
#include <utility>
#include "../include/Server.hpp"
#include "../include/Location.hpp"

std::ostream& operator<<(std::ostream& os, const Location& location)
{
	// os << "cgi: " << std::boolalpha << location.cgiPass << std::endl;
	// os << "autoIndex: " << std::boolalpha << location.autoIndex << std::endl;
	// // os << "allowMethod: " << location.allowMethod << std::endl;
	
	// os << "cliBodySize : " << location.cliBodySize << std::endl;
	os << "cliBodySize : " << location.cliBodySize << std::endl;
	
// 	os << "root: " << location.root << std::endl;
// 	// os << "index: " << location.index << std::endl;
// 	if (!location.ret.have)
// 		os << "no return" << std::endl;
// 	else 
// 		os << "return: " << location.ret.code << " " << location.ret.text << std::endl;
	return (os);
}

uint64_t	ft_stouint(std::string str)
{
	int	i;
    u_int64_t res;

	i = 0;
    res = 0;
	while (isspace(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
			return (0);
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res);
}

void	ft_print_vec_str(std::vector<std::string> vec)
{
	// size_t len = vec.size();
	// std::cout << "len : " << len << std::endl;
	for (int i = 0; i < vec.size(); i++)
        	std::cout << i << "|" << vec[i] << "|" << std::endl;
}

void	ft_print_vec_uint(std::vector<uint64_t> vec)
{
	// size_t len = vec.size();
	// std::cout << "len : " << len << std::endl;
	for (int i = 0; i < vec.size(); i++)
        	std::cout << i << "|" << vec[i] << "|" << std::endl;
}

std::vector<std::string>    ft_split(std::string str)
{
    int i;
    std::vector<std::string> res;
    std::string                 word;
    
    i = 0;
    while (str[i])
    {
        while (isspace(str[i]) && str[i])
            i++;
        word = "";
        while(!(isspace(str[i])) && str[i])
        {
            word += str[i];
            i++;
        }
        if (str[i] == '\0' && str[i])
            break;
        if (!word.empty())
            res.push_back(word);
    }
    return (res);
}

std::string	ft_trim(std::string line, char c)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of(c);
	end = line.find_last_not_of(c);
	
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
	int len = line.size();
	if (line[len - 1] == ';' || line[len - 1] == '}' || line[len - 1] == '{')
	{
		
	}
	else
		return("false");
	while (line[i])
	{
		while (line[i] == key[i]) // escape key
			i++;
		while (line[i] && isspace(line[i]))
			i++;
		while ((line[i] != '{' || line[i] != '}') && line[i])
		{
			// std::cout << "line[i]" << line[i] << std::endl;
			if (line[i] == ';') // Don't forget to check in case it forget to fill ->  maybe use state 
				break;
			value += line[i];
			// value.append(sp_line[i]);
			i++;
		}
		break;
	}
	value += "";
	if (value.find("#") == std::string::npos)
		return (value);
	return ("false");	
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
	if (key.find("#") == std::string::npos) // not find 
		return (key);
	return ("false");	
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

short	ft_getlocate(Location &location, std::string key, std::string value)
{
	std::vector<std::string> sp;

	sp.clear();
	// std::cout << "key_locate : " << key << std::endl;
	if (key == "root")
		location.root = value;
	else if (key == "client_max_body_size")
		location.cliBodySize = ft_stouint(value);
	else if (key == "cgi_pass")
	{
		if (value == "on")
			location.cgiPass = ON;
		else
			location.cgiPass = OFF;
	}
	else if (key == "return")
	{
		sp = ft_split(value);
		// std::cout << "sp[0] : " << sp[0] << std::endl;
		// std::cout << "sp[1] : " << sp[1] << std::endl;
		// exit(0);
		location.ret.code  = true;
		location.ret.code = ft_stoi(sp[0]);
		location.ret.text = sp[1]; 
	}
	else if (key == "index")
		location.index = ft_split(value);
	else if (key == "autoindex")
		location.autoIndex = ON;
	else if (key == "}")
		return (CLOSE_LOCATION);
	return (BETWEEN_LOCATION);
}

void	ft_prt_server(Server sv)
{
	
	std::cout << GRN << "SERVER : " << RESET << std::endl;
	std::cout << "server_name : " << sv.server_name << std::endl;
	std::cout << "listen : " << sv.listen << std::endl;
	std::cout << "error_page : " << std::endl;
	ft_print_vec_str(sv.error_page);
	
	// ft_prt_locate(sv._config);
}

void	ft_prt_location(Location location)
{
	if (location.cgiPass == false)
		std::cout << "cgiPass : " << "off" << std::endl;
	else
		std::cout << "cgiPass : " << "on" << std::endl;
	std::cout << "autoIndex :" << location.autoIndex << std::endl;
	std::cout << "cliBodySize : " << location.cliBodySize << std::endl;
	std::cout << "root : " << location.root << std::endl;
	std::cout << "___________index___________" << std::endl;
	for (int i = 0; i < location.index.size(); i++)
	{
		std::cout << location.index[i] << std::endl;
	}
	std::cout << "________________________________________________________________" << std::endl;
}

int	ft_stoi(std::string str)
{
	int	i;
    int sym;
    int res;

	i = 0;
    sym = 1;
    res = 0;
	while (isspace(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sym = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res * sym);
}

void	ft_print_df_conf(t_dfconf df)
{
	std::cout << "cliBodySize : " << df.cliBodySize << std::endl;
	std::cout << "listen : " << df.listen << std::endl;
	std::cout << "server_name : " << df.server_name << std::endl;
	std::cout << "root : " << df.root << std::endl;	
	
	std::cout << "index : " << std::endl;
	ft_print_vec_str(df.index);
	
	std::cout << "limit_except : " << std::endl;
	ft_print_vec_str(df.limit_except);
	
	std::cout << "error_page : " << std::endl;
	ft_print_vec_str(df.error_page);
}

Location	ft_init_location()
{
	Location location;

	location.cgiPass = 0;
	location.autoIndex = 0;
	location.allowMethod.clear();
	location.cliBodySize = 5000;
	location.root = "";
	location.index.clear();
	location.ret.have = false;
	location.ret.code = 0;
	location.ret.text = "";
	return (location);
}

void ft_prt_locate(short locate)
{
	if (locate == DEFAULT)
		std::cout << "locate : DEFAULT" << std::endl;
	else if (locate == START_LOCATION)
		std::cout << "locate : START_DEFAULT" << std::endl;
	else if (locate == BETWEEN_LOCATION)
		std::cout << "locate : BETWEEN_DEFAULT" << std::endl;
	else if (locate == CLOSE_LOCATION)
		std::cout << "locate : CLOSE_DEFAULT" << std::endl;
}

bool ft_check_name(std::string key)
{
	if (key == "server" ||  key == "client_max_body_size" || key == "root" \
				|| key == "index" || key == "limit_except" || key == "return" \
				|| key == "autoindex" || key == "error_page" || key == "listen" \
				|| key == "cgi_pass" || key == "location" || key == "server_name" \
				|| key == "}" || key == "{" )
		return (true);
	return (false);
}

bool	ft_check_sameport(std::vector<u_int64_t> port)
{
	int			i;
    int         start_loop;
	bool		check;
	u_int64_t	tmp_port;
	int			len;
	
	i = 1;
    start_loop = 1;
	check = false;
	if (port.empty())
		return (false);
	len = port.size();
	tmp_port = 	port[0];
    while (i < len)
    {
        if (tmp_port == port[i])
            return (true);
        if (i == len - 1)
        {
            tmp_port = port[start_loop];
            i = start_loop + 1;
            start_loop++;
        }
        i++;
    } 
	return (false);
}

int	parsing_config(int ac, char **av,Server &server, std::vector<uint64_t> &tmp_port)
{
	std::string	line;
	std::string	file;
	std::string	key;
	std::string	value;
	std::string	sp_line;
	short		locate;
	Location	location;
	std::string	tmp_key;
	std::map<std::string, Location> _con;
	std::vector<std::string> vec;
	
	if (ac != 2)
		return(std::cerr << RED << "Error : Expected 2 arguments" << RESET << std::endl, 0);
	std::ifstream input_file(av[1]);
	if (input_file.is_open() == false)
		return(std::cerr << RED << "Error : Could not open file : " << RESET << av[1] << std::endl, 0);
	if (ft_check_extension(av[1]) == false)
		return (std::cerr << RED << "Error : extension file" << RESET << std::endl, 0);
	int i = 0;
	int stage = 0;	
	while (std::getline(input_file, line)) // return integer representing the status  of read not actual content of the line
	{
		locate = DEFAULT;
		// write new code for trim isspace
		sp_line = ft_trim_ispace(line);
		key = ft_getkey(sp_line);
		if (key.empty())
			continue;
		else
			value = ft_getvalue(key, sp_line);
		if (key == "false" || value == "false")
		{
			std::cout << "false " << std::endl;
			return (-1);
		}
		// std::cout << "|" << key << "|" << " : "  << "|" << value << "|" << std::endl;
		// if (key.find("location") != std::string::npos) // find is location or not (if answer == std::string::npos , It mean don't found)
		// if (key.find("location") == 0) // find is location or not (if answer == std::string::npos , It mean don't found)
		if (strcmp(key.c_str() , "location") == 0) // find is location or not (if answer == std::string::npos , It mean don't found)
		{
			if (!value.empty())
			{
				vec = ft_split(value);
				tmp_key = vec[0];
				std::cout << "|" << tmp_key << "|" << std::endl;
			}	
			locate = BETWEEN_LOCATION;
		}
		if (key == "listen")
		{
			if (tmp_port[0] == 80 && stage == 0)
			{
				stage = 1;
				tmp_port.pop_back();
			}
			tmp_port.push_back(ft_stoi(value));
		}
		else if (key == "server_name")
			server.server_name = value;
		else if (key == "error_page")
			server.error_page = ft_split(value);
		if (ft_check_name(key) == false)
			std::cerr << RED << key << " is valid" << RESET << std::endl;	
		if (locate == BETWEEN_LOCATION)
		{
			locate = ft_getlocate(location, key, value);
			// ft_prt_locate(locate);
		}
		// else if (locate == CLOSE_LOCATION)
		if (locate == CLOSE_LOCATION)
		{
			// ft_prt_location(location);
			server._config.insert(std::pair<std::string, Location>(tmp_key, location));
			location = ft_init_location();
		}
	}
	
	/*
		PRINT MAP LOCATION
	*/
	std::map<std::string, Location>::iterator it;
	for (it = server._config.begin(); it != server._config.end(); it++)
	{
		if (it->second.cgiPass == true)
			std::cout << it->first << " :: " << "cgiPass : " <<  "on" << std::endl;
		else
			std::cout << it->first << " :: " << "cgiPass : " <<  "off" << std::endl;
		std::cout << it->first << " :: " <<  "cliBodySize : " <<  it->second.cliBodySize << std::endl;
		std::cout << it->first << " :: " << "root : " << it->second.root << std::endl;
		std::cout << it->first << " :: " << "return code : " << it->second.ret.code << std::endl;
		std::cout << it->first << " :: " << "return text: " << it->second.ret.text << std::endl;
		if (it->second.ret.have == HAVE)
			std::cout << it->first << " :: " << "return have : " << "have" << std::endl;
		else
			std::cout << it->first << " :: " << "return have : " << "not have" << std::endl;
		if (it->second.autoIndex == ON)
			std::cout << it->first << " :: " << "autoIndex : " << "on" << std::endl;
		else
			std::cout << it->first << " :: " << "autoIndex : " << "off" << std::endl;
		for (int j= 0; j < it->second.index.size(); j++)
			std::cout << it->first << " :: " << "index[" << j << "] : " << it->second.index[j] << std::endl;
			
		std::cout << std::endl;
	}
	input_file.close();
	if (ft_check_sameport(tmp_port) == true)
	{
		std::cerr << RED << "Error : Same Port" << RESET << std::endl;
		// return (-1);
		exit (0);
	}
	return (0);	
}



int main(int ac, char **av, char **env)
{
	std::string name;
	Server tmp_sv;
	Server sv_get;
	std::vector<uint64_t> tmp_port;
	std::vector<Server> sv;

	tmp_port.push_back(80);
	if (parsing_config(ac, av, tmp_sv, tmp_port) == -1)
	{
		std::cerr << RED << "Error File" << RESET << std::endl;
		return(1);
	}
	for (int i = 0; i < tmp_port.size(); i++)
	{
		sv_get = tmp_sv;
		sv_get.listen = tmp_port[i];
		sv.push_back(sv_get);
	}
	// for (int i = 0; i < tmp_port.size(); i++)
	// {
	// 	ft_prt_server(sv[i]);
	// }
	// ft_print_vec_uint(tmp_port);
	return (0);	
}