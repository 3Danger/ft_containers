#pragma once
#include <exception>
#include <string>

namespace ft{
	class vectorException: public std::exception{
	private:
		std::string reason;
	public:
		vectorException(std::string const & reason) throw() {this->reason = reason;}
		const char * what() const throw() {return reason.c_str();}
		~vectorException() throw(){};
	};
}