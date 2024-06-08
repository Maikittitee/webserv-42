#include <iostream>
#include <vector>

bool	ft_checksameport(std::vector<u_int64_t> port)
{
	int			i;
    int         start_loop;
	bool		check;
	u_int64_t	tmp_port;
	int			len;
	
	i = 1;
    start_loop = 1;
	check = false;
	if (port.empty())
		return (false);
	len = port.size();
	tmp_port = 	port[0];
    while (i < len)
    {
        if (tmp_port == port[i])
            return (true);
        if (i == len - 1)
        {
            tmp_port = port[start_loop];
            i = start_loop + 1;
            start_loop++;
            std::cout << "_______________" << std::endl;
            std::cout << "tmp_port : " << tmp_port << std::endl;
            std::cout << "i : " << i << std::endl;
            std::cout << "loop : " << start_loop << std::endl;
            std::cout << "_______________" << std::endl;
        }
        i++;
    } 
	return (false);
}

int main(void)
{
    std::vector<u_int64_t>  port;

    port.push_back(80); 
    // port.push_back(8000); 
    port.push_back(90);
    port.push_back(80);
    
    // std::cout << "True " << true << std::endl;
    // std::cout << "False " << false << std::endl;
    std::cout << "Same " << true << std::endl;
    std::cout << "Not same " << false << std::endl;
    bool check = ft_checksameport(port) ;
    if (check == true)
        std::cout << "Same" << std::endl; 
    else
        std::cout << "Not Same" << std::endl; 
    // std::cout << "Stage : " << check << std::endl; 

}