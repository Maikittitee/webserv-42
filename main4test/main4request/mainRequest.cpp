#include "RequestHttp.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Invalid input: request msg file's name" << std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }
    
    std::string line;
    std::string request;
    while (std::getline(file, line))
    {
        if (line.size() == 1)
            request += "\n";
        else
            request += line + "\n";
        line = "";
    }
    file.close();
    // std::cout << request;
    RequestHttp req(request);
    std::cout << "Method: " << req.getMethod() << std::endl;
    std::cout << "Path: " << req.getPath() << std::endl;
    std::cout << "Version: " << req.getHttpVersion() << std::endl;

    std::map<std::string, std::string> header = req.getHeaderFieldMap();
    std::map<std::string, std::string>::iterator it;
    for (it = header.begin(); it != header.end(); ++it) 
    {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }

    std::cout << "Body: " << req.getBody() << std::endl;
    std::cout << "Query: " << req.getQueryString() << std::endl;
    return 0;
}