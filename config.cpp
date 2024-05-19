/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/17 13:03:31 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <cstring>

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
	// std::cout << "[value] : " << value << std::endl;
	return (value);
}
// std::string	ft_getvalue(std::string txt)
// {
// 	char	*key;
// 	char	*tmp_txt;
	
// 	tmp_txt = (char *)txt.c_str();	
// 	std::cout << "--------" << std::endl;
// 	std::cout << txt << std::endl;
// 	std::cout << "--------" << std::endl;
	
// 	key = strtok((char *)txt.c_str(), " ");
// 	while(key)
// 	{
// 		std::cout << key << std::endl;
// 		key = strtok(NULL, " ");		
// 	}
// 	return (txt);
// }

std::string ft_getkey(std::string txt)
{
	int	i;
	std::string key;

	i = 0;
	
	while (txt[i])
	{	
		while (txt[i] && isspace(txt[i])) // escape isspace
			i++;
		while (txt[i]) // keep txt
		{
			key += txt[i];
			if (txt[i] && (txt[i] == '{' || txt[i] == '}' || txt[i] == ';'))
				break;
			i++;
		}
		break;
	}
	std::cout << "key : " << key << std::endl;  
	return (key);
}


std::string	ft_trimtab(std::string line)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of("	");
	// std::cout << "start : " << start << std::endl;
	end = line.find_last_not_of("	");
	// std::cout << "end : " << end << std::endl;
	
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
	// std::cout << "test" << std::endl;
	int i = 0;
	while(std::getline(input_file, line)) // return integer representing the status  of read not actual content of the line
	{
		
		// sp_line = ft_trimsp(line);
		// sp_line = ft_trimtab(sp_line);
		// sp_line = ft_trim(line, ' ');
		// sp_line = ft_trim(sp_line, '	');
		// std::cout << "sp_line : " << sp_line << "|" << std::endl;
		
		key = ft_getkey(sp_line);
		// std::cout << "before value" << std::endl;
		// value = ft_getvalue(key, sp_line);
		// if (key.empty())
			// std::cout << "Empty" << std::endl;
		// else if ( key != "{" && key != "}")
		std::cout << key << " : " << value << std::endl;
		// std::cout << "key : " << key << "|" << std::endl;
		// std::cout << "key : " << key << "|" << std::endl;
		// std::cout << "value : " << value << "|" << std::endl;
		i++;
		if (i == 4)
			break;
		// std::cout << line << std::endl;
		
	}
	input_file.close();
	return (0);
}

