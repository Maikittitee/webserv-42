#include "../include/Location.hpp"

// Location::Location(void) : _client_max(3) {}
Location::Location(void) 
{
	// std::cout << BCYN << "Constructor Location called"  << RESET << std::endl;
	cgiPass = OFF;
	autoIndex = OFF;
	allowMethod.clear();
	cliBodySize = 5000;
	root = "";
	index.clear();
	ret.have = NOT_HAVE;
	ret.code = 0;
	ret.text = "";
}

// Location::Location() : _client_max(3) {}

Location::Location(const Location &other):cgiPass(other.cgiPass), autoIndex(other.autoIndex), allowMethod(other.allowMethod), cliBodySize(other.cliBodySize), root(other.root), index(other.index), ret(other.ret){}

Location& Location::operator= (const Location &rhs){
			if (this == &rhs)
				return *this;
			cgiPass = rhs.cgiPass;
			autoIndex = rhs.autoIndex;
			allowMethod = rhs.allowMethod;
			cliBodySize = rhs.cliBodySize;
			root = rhs.root ;
			index = rhs.index;
			ret = rhs.ret;
			return *this;
		}

// std::ostream& operator<<(std::ostream &os, const std::vector<t_method>& eiei)
// {
// 	for (int i = 0; i < eiei.size(); i++){
// 		os << eiei[i] << ", ";
// 	}
// 	os << std::endl;
// 	return (os);
// }
// std::ostream& operator<<(std::ostream &os, const std::vector<std::string>& eiei)
// {
// 	for (int i = 0; i < eiei.size(); i++){
// 		os << eiei[i] << ", ";
// 	}
// 	os << std::endl;
// 	return (os);
// }


// std::ostream& operator<<(std::ostream& os, const Location& location)
// {
// 	os << "cgi: " << std::boolalpha << location.cgiPass << std::endl;
// 	os << "autoIndex: " << std::boolalpha << location.autoIndex << std::endl;
// 	os << "allowMethod: " << location.allowMethod << std::endl;
// 	os << "cliBodySize: " << location.cliBodySize << std::endl;
// 	os << "root: " << location.root << std::endl;
// 	os << "index: " << location.index << std::endl;
// 	if (!location.ret.have)
// 		os << "no return" << std::endl;
// 	else 
// 		os << "return: " << location.ret.code << " " << location.ret.text << std::endl;
// 	return (os);

// }