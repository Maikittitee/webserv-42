// C++ program to demonstrate functioning of substr()
#include <iostream>
#include <string>
using namespace std;

// int main()
// {
//     // Take any string
//     string s = "dog:cat";

//     // Find position of ':' using find()
//     int pos = s.find("d");
//     cout << "pos : "  << pos << endl; 
//     // Copy substring after pos
//     string sub = s.substr(pos + 1);

//     // prints the result
//     cout << "String is: " << sub;

//     return 0;
// }

std::string	ft_trimstr(std::string line)
{
	size_t	start;
	size_t	end;

	start = line.find_first_not_of(" ");
	std::cout << "start : " << start << std::endl;
	end = line.find_last_not_of(" ");
	std::cout << "end : " << end << std::endl;
	
	if (start != std::string::npos &&  end != 0)
		return (line.substr(start, end - start + 1));
	return ("");
}

int main()
{
    std::string line = "  ";
    std::cout << "str : " << ft_trimstr(line) << std::endl;


}