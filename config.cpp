/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:08 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/11 03:10:41 by nkietwee         ###   ########.fr       */
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

std::string ft_getkey(std::string txt)
{
	int	i;
	std::string key;

	i = 0;
	while (txt[i])
	{	
		while (txt[i] && isspace(txt[i])) // escape isspace
			i++;
		while (txt[i] && !isspace(txt[i]))
		{
			key += txt[i];	
			i++;
		}
		break;
	}
	return (key);
}

int main(int ac ,char **av)
{
	std::string	txt;
	std::string	file;
	std::string	key;
	
	if (ac != 2)
		return(std::cerr << "Error : Expected 2 arguments" << std::endl, 0);
	std::ifstream input_file(av[1]);
	if (input_file.is_open() == false)
		return(std::cerr << "Error : Could not open file:" << av[1] << std::endl, 0);
	if (ft_check_extension(av[1]) == false)
		return (std::cerr << "Error : extension file" << std::endl, 0);
	// std::cout << "test" << std::endl;
	while(std::getline(input_file, txt)) // return integer representing the status  of read not actual content of the line
	{
		key = ft_getkey(txt);
		if ( key != "{" && key != "}")
			std::cout << "key : " << key << "|" << std::endl;
		// std::cout << txt << std::endl;
	}
	input_file.close();
	return (0);
}

