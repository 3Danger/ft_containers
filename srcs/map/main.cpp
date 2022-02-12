#include <iostream>
#include <string>
#include <unistd.h>


#ifndef FT
#include <map>
using namespace std;
#else
#include "map.hpp"
using namespace ft;
#endif

int	main()
{
	map<int, std::string> s;
	s[0] = "zer";
	s[1] = "one";
	s[2] = "two";
	s[3] = "tre";
	s[4] = "fou";
	s[5] = "fiv";
	s[6] = "six";

	std::cout << s.size() + 3U << std::endl;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		std::cout << "s.at(" << i << ") " << s.at(i) << " " << i << std::endl;
	}
	for (unsigned int i = 0; i < s.size(); i++)
	{
		std::cout << "s.count(" << i << ") " << s.count(i) << std::endl;
	}
	// for (uint8_t i = 0; i < s.size(); i++)
		// s.insert(,);
		
	// map<int, std::string>::typ
		
	
}