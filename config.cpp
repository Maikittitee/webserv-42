/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/23 09:33:38 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <cstring>

std::string	ft_trimtab(std::string line)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of("	");
	end = line.find_last_not_of("	");
	
	if (start != std::string::npos &&  end != 0)
		return (line.substr(start, end - start + 1));
	return (line);
}

std::string	ft_trimsp(std::string line)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of(" ");
	// std::cout << "start : " << start << std::endl;
	end = line.find_last_not_of(" ");
	// std::cout << "end : " << end << std::endl;
	
	if (start != std::string::npos &&  end != 0)
		return (line.substr(start, end - start));
	return ("");
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
	while (line[i])
	{
		// std::cout  << "Entry" << std::endl;
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
std::string ft_getkey(std::string txt)
{
	int	i;
	std::string key;
	
	key = "";
	i = 0;
	
	// std::cout << "ft_getkey" << std::endl;
	while (txt[i]) // keep txt
	{
		if (txt[i] && (txt[i] == '{' || txt[i] == '}' || isspace(txt[i])))
			break;
		key += txt[i];
		i++;
	}
	// std::cout << "|" << key << "|" << std::endl;  
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

int main(int ac ,char **av)
{
	std::string	line;
	std::string	file;
	std::string	key;
	std::string	value;
	std::string	sp_line;
	
	if (ac != 2)
		return(std::cerr << "Error : Expected 2 arguments" << std::endl, 0);
	std::ifstream input_file(av[1]);
	if (input_file.is_open() == false)
		return(std::cerr << "Error : Could not open file : " << av[1] << std::endl, 0);
	if (ft_check_extension(av[1]) == false)
		return (std::cerr << "Error : extension file" << std::endl, 0);
	int i = 0;
	while(std::getline(input_file, line)) // return integer representing the status  of read not actual content of the line
	{
		
		sp_line = ft_trim_ispace(line);
		key = ft_getkey(sp_line);
		// if (!key.empty())
		if (key[0] == '\0')
			continue;
		else
			value = ft_getvalue(key, sp_line);
		std::cout << "[key]   : |" << key << "|" << std::endl;
		std::cout << "[value] : |" << value  << "|" << std::endl;
		// std::cout << key << " : " << value << std::endl;
		// i++;
		// if (i == 4)
		// 	break;
		// std::cout << line << std::endl;
		
	}
	input_file.close();
	return (0);
}

