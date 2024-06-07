#include <iostream>
int main(void)
{
	std::string line;
    int i = 0 ;
    line = "Hello{";  // Hello {
    while (line[i])
    {
        // if (line[i + 1] == '\0' && (line[i] != '{' && line[i] != '}' && line[i] != ';'))
        if (line[i + 1] == '\0' && (line[i] != '{' && line[i] != '}' && line[i] != ';'))
            std::cout << "Not Correct" << std::endl;
        // std::cout << "Not correct" << std::endl;
        i++;
    }
    std::cout << "Finish" << std::endl;
}