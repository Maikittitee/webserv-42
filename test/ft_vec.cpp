#include <iostream>
#include <vector>

int main(void)
{
    // std::vector<std::string> name;
    std::vector<std::string> res;
    std::string choice[4] = {"" , "aaa", "bbb", "ccc"};
    
    // for (int j = 0; j < 4 ; j++)
    // {
    //     res.push_back(choice[j]);
    // }
    res.push_back("");
    if (res[0] == "")
        std::cout << "Empty" << std::endl;
    else
        std::cout << "NOT Empty" << std::endl;
    for(int i = 0; i < res.size(); i++)
    {
        // res.pop_back(name[i]);
        // if ()
        std::cout << "|" << res[i] << "|" << std::endl;
    }
}