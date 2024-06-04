#include <iostream>

int main(void)
{
    std::string name = "/name";

    // size_t  find = name.find("f");
    size_t  find = name.find('/');
    if (find != std::string::npos)
        std::cout << "find : " << find << std::endl; 
    else
        std::cout << "Not find" << std::endl; 
}