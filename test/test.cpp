/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:16 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/22 17:33:39 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

std::string	trim(std::string line, char c)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of(c);
	std::cout << "start : " << start << std::endl;
	end = line.find_last_not_of(c);
	std::cout << "end : " << end << std::endl;


	if (start != std::string::npos &&  end != 0)
		return (line.substr(start, end - start + 1));
	/* Incase string and char have 1 charater and same text*/
	if (start == std::string::npos && end == std::string::npos)
		return ("");
	std::cout << "test" << std::endl;
	return (line);
}

int main(){
	// std::string str2 = "Trim  these spaces";
	std::string str = "1";
  std::string trimmed_str = trim(str, '1');
	
  std::cout << "Original string: " << "|" << str << "|" << std::endl;
  std::cout << "Trimmed string: "  << "|" << trimmed_str  << "|" << std::endl;
	// std::cout << "npos : "<< std::string::npos << std::endl;
	return 0;
}
