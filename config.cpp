/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/22 14:37:15 by nkietwee         ###   ########.fr       */
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
		return (line.substr(start, end - start));
	return ("");
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
	
	if (start != std::string::npos &&  end != 0)
		return (line.substr(start, end - start));
	return ("");
}
bool	ft_check_extension(char	*file)
{
	char *tmp;

	tmp = strrchr(file, '.');
	if (strcmp(tmp, ".conf") == 0)
		return (true);
	return (false);
}
std::string	ft_getvalue(std::string key, std::string sp_line)
{
	int			i;
	std::string	value;

	i = 0;
	while (sp_line[i])
	{
		
		while (sp_line[i] == key[i])
			i++;
		while (sp_line[i] && isspace(sp_line[i]))
			i++;
		while (sp_line[i] != ';' && sp_line[i])
		{
			value += sp_line[i];
			// value.append(sp_line[i]);
			i++;
		}
	}
	return (value);
}
std::string ft_getkey(std::string txt)
{
	int	i;
	std::string key;

	i = 0;
	
	// std::cout << "ft_getkey" << std::endl;
	while (txt[i])
	{	
		while (txt[i] && isspace(txt[i])) // escape isspace
			i++;
		while (txt[i]) // keep txt
		{
			if (txt[i] && (txt[i] == '{' || txt[i] == '}' || isspace(txt[i])))
				break;
			key += txt[i];
			i++;
		}
		break;
	}
	std::cout << "|" << key << "|" << std::endl;  
	return (key);
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
		
		key = ft_getkey(line);
		// std::cout << "before value" << std::endl;
		// value = ft_getvalue(key, sp_line);
		// if (key.empty())
			// std::cout << "Empty" << std::endl;
		// else if ( key != "{" && key != "}")
		// std::cout << key << " : " << value << std::endl;
		// i++;
		// if (i == 4)
		// 	break;
		// std::cout << line << std::endl;
		
	}
	input_file.close();
	return (0);
}

