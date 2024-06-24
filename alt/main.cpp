#include <iostream>
# include <stdio.h>
# include <fcntl.h>
# include <string>
# include <unistd.h>

# define BUFFERSIZE 10

int	main()
{
	if (access("../../../IMG_8246.jpeg", F_OK) != 0)
		std::cout << "not found" << std::endl;
	else {
		std::cout << "found" << std::endl;
	}	
}

