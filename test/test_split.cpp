#include <iostream>
#include <vector>

std::vector<std::string>    ft_split(std::string str)
{
    int i;
    std::vector<std::string> res;
    std::string                 word;
    
    i = 0;
    while (str[i])
    {
        while (isspace(str[i]) && str[i])
            i++;
        word = "";
        while(!(isspace(str[i])) && str[i])
        {
            word += str[i];
            i++;
        }
        if (str[i] == '\0' && str[i])
            break;
        if (!word.empty())
            res.push_back(word);
    }
    return (res);
}

int main()
{
    std::vector<std::string> res_vec;

    res_vec  = ft_split("Hello  World");
    for (int i = 0; i < res_vec.size(); i++)
        std::cout << "|" << res_vec[i] << "|" << std::endl;
}