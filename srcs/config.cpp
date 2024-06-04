/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/06/04 22:19:03 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <cstring>
#include <utility>
#include "../include/Server.hpp"
#include "../include/Location.hpp"


// Dfconf::Dfconf(){}
// Dfconf::~Dfconf(){}


std::ostream& operator<<(std::ostream& os, const t_dfconf& df)
{
	// os << "cgi: " << std::boolalpha << location.cgiPass << std::endl;
	os << "cliBodySize : " << df.cliBodySize << std::endl;
	os << "listen : " << df.listen << std::endl;
	os << "server_name : " << df.server_name << std::endl;
	os << "root : " << df.root << std::endl;
	
// 	// os << "index: " << location.index << std::endl;
// 	if (!location.ret.have)
// 		os << "no return" << std::endl;
// 	else 
// 		os << "return: " << location.ret.code << " " << location.ret.text << std::endl;
	return (os);
}


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





// std::ostream& operator<<(std::ostream& os, const Dfconf& df)
// {
// 	os << "cliBodySize : " << df.cliBodySize << std::endl;
// 	os << "listen : " << std::boolalpha << df.listen << std::endl;
// 	os << "server_name : " << std::boolalpha << df.server_name << std::endl;
// 	os << "root: " << df.root << std::endl;
	
	
// 	// os << "allowMethod: " << df.allowMethod << std::endl;
// 	// os << "index: " << df.index << std::endl;
// 	// if (!df.ret.have)
// 		// os << "no return" << std::endl;
// 	// else 
// 		// os << "return: " << df.ret.code << " " << df.ret.text << std::endl;
// 	return (os);
// }

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

void	ft_print_vec(std::vector<std::string> vec)
{
	// size_t len = vec.size();
	// std::cout << "len : " << len << std::endl;
	for (int i = 0; i < vec.size(); i++)
	{
		// if(!vec[i].empty())
        	std::cout << i << "|" << vec[i] << "|" << std::endl;
	}
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

void	ft_fillvector(std::vector<std::string> src, std::vector<std::string> &des)
{
	// int i;

	// i = 0;
	// if (des[0] == "")
	// 	i = 1;
	// std::cout << "i : " << i << std::endl;
	if (des[0].empty())
		des.pop_back();
	for (int i = 0; i < src.size(); i++)
	{
		des.push_back(src[i]);
	}
}

void	ft_get_default_conf(t_dfconf &df, std::string key, std::string value)
{
	// t_dfconf	df;
	std::vector<std::string> vec;

	// vec.push_back("");
	if (key == "client_max_body_size")
	{
		df.cliBodySize = ft_stouint(value);
	}
	else if (key == "listen")
	{
		df.listen = ft_stouint(value);
	}
	// if (key == "server_name")
	else if (key == "server_name")
	{
		// std::cout << "value_servername : " << value << std::endl;
		df.server_name = value;
	}
	else if (key == "root")
	{
		df.root = value;
	}
	else if (key == "index")
	{
		vec = ft_split(value);
		// ft_print_vec(vec);
		ft_fillvector(vec, df.index);
		
	}
	else if (key == "limit_except")
	{
		vec = ft_split(value);
		ft_fillvector(vec, df.limit_except);
		
	}
	else if (key == "error_page")
	{
		vec = ft_split(value);
		ft_fillvector(vec, df.error_page);
		
	}

	// location.insert(std::pair<std::string, Dfconf>("default", df));
	// return (df);
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
			// value.append(sp_line[i]);
			i++;
		}
		break;
	}
	value += "";
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


t_dfconf	ft_init_stuct(void)
{
	t_dfconf df;

	df.cliBodySize = 5000;
	df.listen = 80;
	df.server_name = "localhost";
	df.root = "";
	df.index.push_back("");
	df.limit_except.push_back("");
	df.error_page.push_back("");
	
	return (df);
}

void	ft_print_df_conf(t_dfconf df)
{
	std::cout << "cliBodySize : " << df.cliBodySize << std::endl;
	std::cout << "listen : " << df.listen << std::endl;
	std::cout << "server_name : " << df.server_name << std::endl;
	std::cout << "root : " << df.root << std::endl;	
	
	std::cout << "index : " << std::endl;
	ft_print_vec(df.index);
	
	std::cout << "limit_except : " << std::endl;
	ft_print_vec(df.limit_except);
	
	std::cout << "error_page : " << std::endl;
	ft_print_vec(df.error_page);
}

int	parsing_config(int ac, char **av, char **env)
{
	std::string	line;
	std::string	file;
	std::string	key;
	std::string	value;
	std::string	sp_line;
	t_dfconf	df;
	bool		locate;
	Location	location;
	Server		server(50, env);
	df = ft_init_stuct();
	
	if (ac != 2)
		return(std::cerr << "Error : Expected 2 arguments" << std::endl, 0);
	std::ifstream input_file(av[1]);
	if (input_file.is_open() == false)
		return(std::cerr << "Error : Could not open file : " << av[1] << std::endl, 0);
	if (ft_check_extension(av[1]) == false)
		return (std::cerr << "Error : extension file" << std::endl, 0);
	int i = 0;
	locate = DEFAULT1;
	while (std::getline(input_file, line)) // return integer representing the status  of read not actual content of the line
	{
		// write new code for trim isspace
		sp_line = ft_trim_ispace(line);
		key = ft_getkey(sp_line);
		// if (key == "location")
		// 	locate = true;
		if (key.empty())
			continue;
		else
			value = ft_getvalue(key, sp_line);
		// std::cout << "|" << key << "|" << " : "  << "|" << value << "|" << std::endl;
		if (key.find('/') != std::string::npos) // find is location or not (if answer == std::string::npos , It mean don't found)
			locate = LOCATION;
		if (locate == DEFAULT1)
			ft_get_default_conf(df, key, value);
		i++;
		if (i == 8)
			break;
	}
	ft_print_df_conf(df);
	
	exit(0);		

	
	// std::map<std::string, t_dfconf>::iterator itd;
	// std::map<std::string, Dfconf>::iterator itd;
	// for (itd = df_conf.begin(); itd != df_conf.end(); itd++)
	// {
	// 	std::cout << itd->first << " : " <<  itd->second << std::endl;
	// 	// std::cout << "[test_print] client_max : " << it->second._client_max << std::endl;
	// }
		
	// std::map<std::string, Location>::iterator it;
	// for (it = server._config.begin(); it != server._config.end(); it++)
	// {
	// 	std::cout << it->first << " : " <<  it->second << std::endl;
	// 	// std::cout << "[test_print] client_max : " << it->second._client_max << std::endl;
	// }
	input_file.close();
	return (0);	
}

int main(int ac, char **av, char **env)
{
	parsing_config(ac, av, env);	

	return (0);	
}