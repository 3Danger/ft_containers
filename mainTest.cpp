#include <iostream>
#include <cmath>
#include <stack>
#include <deque>
#include <vector>
#include "vector.hpp"

// #define VECTOR ft::vector<int>
#define VECTOR ft::vector<int>

template<class Container>
void	print(Container con){
	typename Container::iterator beg = con.begin();
	typename Container::iterator end = con.end();

	while(beg != end)
		std::cout << *(beg++) << ". ";
	std::cout << std::endl;
}

int main(int ac, char ** av){
	// typedef std::vector<int>::reverse_iterator	siter;
	VECTOR		vec1;
	VECTOR		vec2;
	ac > 1 ? srand(atoi(av[1])) : srand(2222);
	for (size_t i = 0; i < 17; i++)
		vec1.push_back(rand() % 80 + 19);
	vec2.resize(vec1.size());
	std::copy(vec1.begin(), vec1.end(), vec2.begin());
	vec2.assign(33, 5);
	std::cout << "vector 1: "; print(vec1);
	std::cout << "vector 2: "; print(vec2);
	// std::cout << "_ft::vector: " << vec1.capacity() << std::endl;
	std::cout << "vector 1:" << vec1.capacity() << std::endl;
	std::cout << "vector 2:" << vec2.capacity() << std::endl;

	// print(ftvec);
	// ftvec2.resize(ft.)
}