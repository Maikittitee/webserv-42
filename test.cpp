/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:07:16 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/13 16:35:28 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

std::string trim(const std::string& str)
{
  // Find the first non-space character from the beginning
	size_t start = str.find_first_not_of(" ");
	std::cout << "start : " << start << std::endl;
  // Find the last non-space character from the end (excluding null terminator)
	size_t end = str.find_last_not_of(" ") + 1;
	std::cout << "end : " << end << std::endl;

  // If both start and end are valid, return the substring
	if (start != std::string::npos && end != 0)
	{
		std::cout << "Entry" << std::endl;
		// str.substr(start, end - start);
//   if (start != std::string::npos) {
    return str.substr(start, end - start);
	}
	

//   // If the string is all spaces, return an empty string
  return "";
}

int main() {
	// std::string str2 = "Trim  these spaces";
	std::string str = " s ";
  std::string trimmed_str = trim(str);
	
  std::cout << "Original string: " << str << std::endl;
  std::cout << "Trimmed string: " << trimmed_str << std::endl;
	// std::cout << "npos : "<< std::string::npos << std::endl;
	return 0;
}
