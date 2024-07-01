#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>

int	main()
{
	int fd = open("makefile", O_RDONLY);
	std::cout << "1st fd: " << fd << std::endl;
	close(fd);

	fd = open("makefile", O_RDONLY);
	std::cout << "2nd fd: " << fd << std::endl;
	close(fd);
}