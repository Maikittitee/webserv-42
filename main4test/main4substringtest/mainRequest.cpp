#include <iostream>
#include <fcntl.h>
#include <unistd.h> // for read(), close()
#include <stdio.h>  // for perror()
#include <stdlib.h> // for EXIT_FAILURE

#define BUFFERSIZE 1000

int main(int argc, char **argv)
{
    int     fd;
    int     i = 0;
    char    buffer[100000];
    ssize_t bytes;

    if (argc != 2)
    {
        std::cerr << "Invalid input: request msg file's name" << std::endl;
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    bytes = read(fd, buffer, BUFFERSIZE);
    buffer[bytes + 1] = '\0';
    // printf("%s|\n", buffer);
    std::cout << buffer << std::endl << std::endl << "<---------------------------------------->" << std::endl;
    while(i <= bytes)
    {
        std::cout << buffer[i] << "(" << i << ")";
        if(buffer[i] == '\n' || buffer[i] == '\r')
        {
            std::cout << std::endl << "================================" << std::endl;
            std::cout << buffer[i-2] << std::endl;
            std::cout << buffer[i-1] << std::endl;
            std::cout << "i = " << i << std::endl << std::endl;
        }
        i++;
    }
    close(fd);
    return 0;
}