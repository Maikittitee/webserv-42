#include "Request.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void    printResule(Request& req)
{
        std::cout << std::endl;
        std::cout << "Method: " << req._method << std::endl;
        std::cout << "Path: " << req._path << std::endl;
        std::cout << "Query: " << req._query_string << std::endl;
        std::cout << "Version: " << req._http_version << std::endl;
        std::map<std::string, std::string> header = req.getHeaderFieldMap ();
        std::map<std::string, std::string>::iterator it;
        for (it = header.begin(); it != header.end(); ++it) 
        {
            std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        }
        std::cout << "Body: " << req._body << std::endl;
}

void    printVector(Request& req)
{
    std::vector<std::string>::iterator it;
    std::cout << std::endl;
    std::cout << "Request Vector:" << std::endl;
    int i = 0;
    for (it = req.request_v.begin(); it != req.request_v.end(); ++it) 
    {
        if ((*it).find('\n', 0) != std::string::npos)
            std::cout << "found newline in the vector\n";
        std::cout << "vi: " << i << " --> ";
        std::cout << *it << std::endl;
        i = i + 1;
    }
}

int main(int argc, char **argv)
{
    int     fd;
    char    buffer[BUFFERSIZE + 1];
    ssize_t bytes;
    int     round;

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
    round = 0;
    bytes = read(fd, buffer, BUFFERSIZE);
    std::cout << "bytes = " << bytes <<std::endl;
    buffer[bytes] = '\0';
    if (bytes == -1)
        std::cout << "read error" << std::endl;
    std::cout << std::endl << "------------------------" << std::endl;
    std::cout << "Round: " << round << std::endl;
    std::cout << std::endl << "request: " << std::endl << buffer << std::endl;
    Request req(buffer);
    std::cout << "status = " << req.getStatus() << std::endl;
    printVector(req);
    printResule(req);
    std::cout << std::endl << "------------------------" << std::endl;
    round = 1;
    // sleep(1);
    while(bytes > 0)
    {
        bytes = read(fd, buffer, BUFFERSIZE);
        if (bytes < BUFFERSIZE)
        {
            req._isEndRecv = true;
        }
        buffer[bytes] = '\0';
        std::cout << "Round: " << round << std::endl;
        std::cout << std::endl << "buffer" << std::endl << buffer << std::endl;
        req.updateRequest(buffer);
        std::cout << "status = " << req.getStatus() << std::endl;
        // printVector(req);
        printResule(req);
        std::cout << std::endl << "------------------------" << std::endl;
        round++;
        // sleep(1);
    }
    close(fd);
    return 0;
}