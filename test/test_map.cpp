/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:09:58 by nkietwee          #+#    #+#             */
/*   Updated: 2024/05/25 21:54:07 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



// CPP Program to demonstrate the implementation in Map
// divyansh mishra --> divyanshmishra101010
#include <iostream>
#include <iterator>
#include <map>
using namespace std;

class Location{
	public:
		bool						cgiPass;
		bool						autoIndex;
		int							port;
		// std::vector<t_method>		allowMethod;
		uint64_t					cliBodySize;
		std::string					root;
		Location(int port);
		// std::vector<std::string>	index;
		// return_t					ret;

};

// Person(const std::string& name, int age) : name(name), age(age) {}

Location::Location(int port): port(port)
{
	
}
int main()
{
    std::map<std::string, Location> cf;
    std::map<std::string, Location>::iterator it;
    //  std::map<std::string, int> cf_iter;
     
    cf["default"]  = Location(3);
    cf["default"]  = Location(4);
    for (it=cf.begin(); it!=cf.end(); ++it)
	{
		cout << it->first << " => " << it->second << '\n';
	}
}

// #include <iostream>
// #include <map>
// #include <string>

// using namespace std;

// int main() {

//    map<string, string> strMap;

//    strMap["Monday"]    = "Montag";
//    strMap["Tuesday"]   = "Dienstag";
//    strMap["Wednesday"] = "Mittwoch";
//    strMap["Thursday"]  = "Donnerstag";
//    strMap["Friday"]    = "Freitag";
//    strMap["Saturday"]  = "Samstag";
//    // strMap.insert(make_pair("Sunday", "Sonntag"));
//    strMap.insert(pair<string, string>("Sunday", "Sonntag"));

//    for (map<string, string>::iterator p = strMap.begin();
//       p != strMap.end(); ++p ) {
//          cout << "English: " << p->first
//               << ", German: " << p->second << endl;
//    }

//    cout << endl;

//    strMap.erase(strMap.find("Tuesday"));

//    for (map<string, string>::iterator p = strMap.begin();
//       p != strMap.end(); ++p ) {
//          cout << "English: " << p->first
//               << ", German: " << p->second << endl;
//    }
// }