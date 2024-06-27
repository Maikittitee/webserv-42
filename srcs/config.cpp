/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/06/27 12:08:50 by nkietwee         ###   ########.fr       */
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

short	ft_stos(std::string str)
{
	int			i;
    short		res;

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

uint64_t	ft_stouint(std::string str)
{
	int			i;
    u_int64_t	res;

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
	for (int i = 0; i < vec.size(); i++)
        	std::cout << i << "|" << vec[i] << "|" << std::endl;
}

void	ft_print_vec_uint(std::vector<uint64_t> vec)
{
	for (int i = 0; i < vec.size(); i++)
        	std::cout << i << "|" << vec[i] << "|" << std::endl;
}

std::vector<std::string>    ft_split(std::string str)
{
    int							i;
    std::vector<std::string>	res;
    std::string					word;
    
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
	if (!tmp)
		return (false);
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
		// do nothing
		// std::cout << "line : " << line << std::endl;
		// std::cout << GRN << "Do nothing" << std::endl;
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
			if (line[i] == ';') // Don't forget to check in case it forget to fill ->  maybe use state 
				break;
			value += line[i];
			i++;
		}
		break;
	}
	value += "";
	return (value);
}

std::string ft_getkey(std::string sp_line)
{
	int			i;
	std::string	key;
	
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
	char		is_sp[5] = {'\t', '\n', '\v', '\f', '\r'};
	std::string	sp_line;
	int			i;
	
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
	if (key == "root")
	{
		if (!value.empty())
		{
			if (value.find_last_of('/') == value.size() - 1)
				location.root = value;
			else
				location.root = value + '/';
		}
	}
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
		location.ret.have  = true;
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

void	ft_prt_server(Server &sv)
{
	
	std::cout << GRN << "SERVER : " << RESET << std::endl;
	std::cout << "server_name : " << sv.server_name << std::endl;
	std::cout << "listen : " << sv.listen << std::endl;
	std::cout << std::endl;
}

void	ft_prt_allowmethod(std::map<std::string, Location>::iterator it, std::vector<t_method> allowMethod)
{
	for (int i = 0; i < allowMethod.size(); i++)
	{
		if (allowMethod[i] == ELSE)
			std::cout << it->first << ":: allowMethod [" << i << "]" << " : " << "ELSE" << std::endl;
		else if (allowMethod[i] == GET)
			std::cout << it->first << ":: allowMethod [" << i << "]" << " : " << "GET" << std::endl;
		else if (allowMethod[i] == POST)
			std::cout << it->first << ":: allowMethod [" << i << "]" << " : " << "POST" << std::endl;
		else if (allowMethod[i] == DELETE)
			std::cout << it->first << ":: allowMethod [" << i << "]" << " : " << "DELETE" << std::endl;
		else if (allowMethod[i] == HEAD)
			std::cout << it->first << ":: allowMethod [" << i << "]" << " : " << "HEAD" << std::endl;
	}
}

void	ft_prt_only_location(Location lc)
{
	std::cout << BLU << "location" << RESET << std::endl;
	if (lc.cgiPass == ON)
		std::cout << " :: " << "cgiPass : " <<  "on" << std::endl;
	else
		std::cout << " :: " << "cgiPass : " <<  "off" << std::endl;
		
	if (lc.autoIndex == ON)
		std::cout << " :: " << "autoIndex : " << "on" << std::endl;
	else
		std::cout << " :: " << "autoIndex : " << "off" << std::endl;

	std::cout << "allowMethod " << std::endl;
	
	// ft_prt_allowmethod(it, lc.allowMethod);
	
	std::cout << " :: " <<  "cliBodySize : " <<  lc.cliBodySize << std::endl;
	
	std::cout << " :: " << "root : " << lc.root << std::endl;
	
	for (int j = 0; j < lc.index.size(); j++)
		std::cout << " :: " << "index[" << j << "] : " << lc.index[j] << std::endl;
	
	std::cout << " :: " << "return code : " << lc.ret.code << std::endl;
	std::cout << " :: " << "return text: " << lc.ret.text << std::endl;
	if (lc.ret.have == HAVE)
		std::cout << " :: " << "return have : " << "have" << std::endl;
	else
		std::cout << " :: " << "return have : " << "not have" << std::endl;
		
	std::cout << std::endl;
}

void	ft_prt_location(std::map<std::string, Location> _config)
{
	std::map<std::string, Location>::iterator it;
	for (it = _config.begin(); it != _config.end(); it++)
		{
			std::cout << BLU << "location" << RESET << std::endl;
			if (it->second.cgiPass == ON)
				std::cout << it->first << " :: " << "cgiPass : " <<  "on" << std::endl;
			else
				std::cout << it->first << " :: " << "cgiPass : " <<  "off" << std::endl;
				
			if (it->second.autoIndex == ON)
				std::cout << it->first << " :: " << "autoIndex : " << "on" << std::endl;
			else
				std::cout << it->first << " :: " << "autoIndex : " << "off" << std::endl;

			// std::cout << "allowMethod " << std::endl;
			
			ft_prt_allowmethod(it, it->second.allowMethod);
			
			std::cout << it->first << " :: " <<  "cliBodySize : " <<  it->second.cliBodySize << std::endl;
			
			std::cout << it->first << " :: " << "root : " << it->second.root << std::endl;
			
			for (int j= 0; j < it->second.index.size(); j++)
				std::cout << it->first << " :: " << "index[" << j << "] : " << it->second.index[j] << std::endl;
			
			std::cout << it->first << " :: " << "return code : " << it->second.ret.code << std::endl;
			std::cout << it->first << " :: " << "return text: " << it->second.ret.text << std::endl;
			if (it->second.ret.have == HAVE)
				std::cout << it->first << " :: " << "return have : " << "have" << std::endl;
			else
				std::cout << it->first << " :: " << "return have : " << "not have" << std::endl;
				
			std::cout << std::endl;
		}
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

bool	ft_check_sameport(std::vector<Server> sv)
{
	std::string tmp_name = sv[0].server_name;
	u_int64_t tmp_listen = sv[0].listen;
	int	i = 1;
	int check = 1;
	int len_server = sv.size();
	while (i < len_server)
	{
		if (tmp_name == sv[i].server_name)
		{
			// std::cout << "Same name" << std::endl;
			if (tmp_listen == sv[i].listen)
			{
				// std::cout << "Same port" << std::endl;
				return (false);
			}	
		}
		i++;
		if (i == len_server - 1)
		{
			tmp_name = sv[check].server_name;
			tmp_listen = sv[check].listen;
			i = check + 1;
			check += 1;
		}
	}
	return (true);
} 

void	ft_init_server(Server &server)
{
	server.server_name = "localhost";
	server.listen = 0;
	server.error_page.clear();
}

std::vector<t_method>	ft_get_allowMethod(std::string value)
{
	std::vector<std::string>	sp;
	std::vector<t_method>		res;

	sp = ft_split(value);
	for (int i = 0; i < sp.size(); i++)
	{
		if (sp[i] == "ELSE")
			res.push_back(ELSE);
		else if (sp[i] == "GET")
			res.push_back(GET);
		else if (sp[i] == "POST")
			res.push_back(POST);
		else if (sp[i] == "DELETE")
			res.push_back(DELETE);
		else if (sp[i] == "HEAD")
			res.push_back(HEAD);
	}
	return (res);
}

void	ft_get_default_config(Location &def_loc, std::string key, std::string value)
{
	std::vector<std::string> sp;
	
	sp.clear();
	if (key == "client_max_body_size")
		def_loc.cliBodySize = ft_stouint(value);
	else if (key == "root")
	{
		if (!value.empty())
		{
			if (value.find_last_of('/') == value.size() - 1)
				def_loc.root = value;
			else
				def_loc.root = value + '/' ;
		}
	}
	else if (key == "index")
	{
		def_loc.index = ft_split(value);
	}
	else if (key == "return")
	{
		
		sp = ft_split(value);
		def_loc.ret.code = ft_stos(sp[0]);
		def_loc.ret.have =  HAVE;
		def_loc.ret.text = sp[1];
	}
	else if (key == "autoindex")
	{
		if (value == "on")
			def_loc.autoIndex = ON;
	}
	else if (key == "cgi_pass")
	{
		if (value == "on")
			def_loc.cgiPass = ON;	
	}
	else if (key == "limit_except")
		def_loc.allowMethod = ft_get_allowMethod(value);
}

int ft_checkfile(int ac, char *av)
{
	if (ac != 2)
		return(std::cerr << RED << "Error : Expected 2 arguments" << RESET << std::endl, false);
	if (ft_check_extension(av) == false)
		return (std::cerr << RED << "Error : extension file" << RESET << std::endl, false);
	return (true);
}

int	ft_checktxt(std::string key, std::string value)
{
	if (key.find("#") != std::string::npos || value.find("#") != std::string::npos)
		return (false);
	if (value == "false")
		return (false);
	if (ft_check_name(key) == false)
	{
		std::cerr << RED << key << " is valid" << RESET << std::endl;	
		return (false);
	}
	return (true);
}

int	ft_cnt_paren(std::string key, std::string value)
{
	if (key.find("{") != std::string::npos || value.find("{") != std::string::npos)
		return (1);
	if (key.find("}") != std::string::npos || value.find("}") != std::string::npos)
		return (-1);
	return (0);
}

void	ft_getlisten(int &stage, std::string value, std::vector<u_int64_t> &tmp_port)
{
	if (tmp_port[0] == 80 && stage == 0)
	{
		stage = 1;
		tmp_port.pop_back();
	}
	tmp_port.push_back(ft_stoi(value));
}

int	parsing_config(int ac, char **av, std::vector<Server> &sv)
{
	std::string						line;
	std::string						key;
	std::string						value;
	std::string						sp_line;
	short							locate;
	Location						location;
	std::string						tmp_key;
	Server							server;
	std::vector<std::string>		vec;
	std::vector<u_int64_t>			tmp_port;
	int								check_paren;
	Location						def_loc;

	check_paren = 0;
	locate = DEFAULT;
	tmp_port.push_back(80);
	if (ft_checkfile(ac, av[1]) == false)
		return (false);
	std::ifstream input_file(av[1]);
	if (input_file.is_open() == false)
		return(std::cerr << RED << "Error : Could not open file : " << RESET << av[1] << std::endl, 0);
	int stage = 0;	
	while (std::getline(input_file, line)) // return integer representing the status  of read not actual content of the line
	{
		sp_line = ft_trim_ispace(line);
		key = ft_getkey(sp_line);
		if (key.empty())
			continue;
		else
			value = ft_getvalue(key, sp_line);
		if (ft_checktxt(key, value) == false)	
			return (false);
		if (locate == DEFAULT)
			ft_get_default_config(def_loc, key, value);
		check_paren += ft_cnt_paren(key, value);
		if (strcmp(key.c_str() , "location") == 0) // find is location or not (if answer == std::string::npos , It mean don't found)
		{
			location = def_loc;
			if (!value.empty())
			{
				vec = ft_split(value);
				tmp_key = vec[0];
			}	
			locate = BETWEEN_LOCATION;
		}
		if (key == "listen")
			ft_getlisten(stage, value, tmp_port);
		else if (key == "server_name")
			server.server_name = value;
		else if (key == "error_page")
			server.error_page = ft_split(value);
		if (locate == BETWEEN_LOCATION)
			locate = ft_getlocate(location, key, value);
		if (locate == CLOSE_LOCATION)
		{
			server._config.insert(std::pair<std::string, Location>(tmp_key, location));
			location = def_loc;
		}
		if (check_paren == 0)
		{
			for (int i = 0; i < tmp_port.size(); i++)
			{
				server.listen = tmp_port[i];			
				sv.push_back(server);
			}
			tmp_port.clear();
			tmp_port.push_back(80);
			server = Server();
			stage = 0;
			locate = DEFAULT;
			def_loc = Location();
		}
	}	
	if (ft_check_sameport(sv) == false)
	{
		// std::cout << "Same port" << std::endl;
		return(false);
	}
	input_file.close();	
	return (true);	
}

// int main(int ac, char **av, char **env)
// {
// 	std::vector<Server> sv;

// 	if (parsing_config(ac, av, sv) == false)
// 	{
// 		std::cerr << RED << "Error File" << RESET << std::endl;
// 		return(1);
// 	}

// 	for (int i = 0; i < sv.size(); i++)
// 	{
// 		ft_prt_server(sv[i]);
// 		ft_prt_location(sv[i]._config);
// 	}
// 	return (0);	
// }