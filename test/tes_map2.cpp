#include <iostream>
#include <map>
#include <string>

// Define the Location class
class Location {
public:
    int port;
    std::string name;

    // Constructor
    Location(int p, const std::string& n) : port(p), name(n) {}

    // Overload the << operator to print Location objects
    // friend std::ostream& operator<<(std::ostream& os, const Location& loc) {
    //     os << "Port: " << loc.port << ", Name: " << loc.name;
    //     return os;
    // }
};

int main() {
    // Define the map
    std::map<std::string, Location> cf;

    // Insert Location objects into the map
    cf["default"] = Location(3, "Default Location");
    cf["secondary"] = Location(4, "Secondary Location");

    // Iterate and print the map contents
    for (const auto& pair : cf) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }

    return 0;
}
