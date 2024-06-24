#include <iostream>
# include <stdio.h>
# include <fcntl.h>
# include <string>
# include <unistd.h>

# define BUFFERSIZE 10

int	main()
{
	std::string output;
	int pid;
	int fds[2];
	char buffer[BUFFERSIZE];
	int fd = open("../docs/images/index.htm", O_RDONLY);
	int length = 0;

	pipe(fds);
	
	pid = fork();
	if (pid == 0){
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
		std::cout << "HELLO FROM CHILD\0" << std::endl;
		exit(0);
	}
	

	close(fds[1]);
	while (1)
	{
		bzero(buffer, length);
		std::cout << "output: " << output << std::endl;
		length = read(fds[0], buffer, BUFFERSIZE - 1);
		buffer[length] = 0;
		std::cout << "read " << length << " bytes: " << buffer << std::endl;
		if (length == 0)
			break;
		output.append(buffer, length);
	}
	std::cout << "---------" << std::endl;
	std::cout << output << std::endl;
}

