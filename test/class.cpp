#include <iostream>
class Location{
	public:
		bool						cgiPass;
		bool						autoIndex;
		int							port;
		// std::vector<t_method>		allowMethod;
		// uint64_t					cliBodySize;
		std::string					root;
		// Location(int port);
		// Location();
		// std::vector<std::string>	index;
		// return_t					ret;

};



// Person(const std::string& name, int age) : name(name), age(age) {
int main()
{
    Location locate;

    locate.port = 0;
    std::cout << locate.port << std::endl;
}