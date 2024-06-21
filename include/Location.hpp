#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <vector>
# include <string>
# include <string.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "Utils.hpp"
# include "Color.hpp"

enum
{
	OFF,
	ON
};

enum
{
	NOT_HAVE,
	HAVE
};

enum
{
	DEFAULT,
	START_LOCATION,
	BETWEEN_LOCATION,
	CLOSE_LOCATION
};

struct return_t {
	bool		have;	// if there is a return 1 (true)
	short int	code;	// Status Code
	std::string	text;	// Option
};

class Location{
	public:
		Location(void);
		bool						cgiPass;
		bool						autoIndex;
		std::vector<t_method>		allowMethod;
		uint64_t					cliBodySize;
		std::string					root;
		std::vector<std::string>	index;
		return_t					ret;

		Location(const Location &other);
		
		Location& operator= (const Location &rhs);

};

int	ft_stoi(std::string str);

std::ostream& operator<<(std::ostream &os, const std::vector<t_method>& eiei);
std::ostream& operator<<(std::ostream &os, const std::vector<std::string>& eiei);


std::ostream& operator<<(std::ostream& os, const Location& location);

#endif