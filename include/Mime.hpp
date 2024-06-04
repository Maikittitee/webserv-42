#ifndef MIME_HPP
# define MIME_HPP

# include "Common.hpp"

class Mime{
	public:

		Mime(void);
		~Mime() {};

		std::map<std::string, std::string> _mime_dict; // <file, type>
		
		std::string get_mime_type(std::string filename);

};

#endif