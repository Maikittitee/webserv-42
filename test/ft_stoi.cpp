#include <iostream>
int	ft_stoi(std::string str)
{
	int	i;
    int sym;
    int res;

	i = 0;
    sym = 1;
    res = 0;
	while (isspace(str[i]))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sym = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = (res * 10) + (str[i] - '0');
        i++;
    }
    return (res * sym);
}

int main(void)
{
    std::cout << ft_stoi("  134"); 
}