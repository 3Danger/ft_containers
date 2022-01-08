#include <iostream>
#include <cmath>
#include <stack>
#include <deque>
#include <vector>
#include "vector.hpp"

using namespace std;

template<class Container>
void	print(Container con){
	typename Container::iterator beg = con.begin();
	typename Container::iterator end = con.end();

	while(beg != end)
		std::cout << *beg++ << ". ";
	std::cout << std::endl;
}

int main(int ac, char ** av){
	typedef ft::vector<int>::reverse_iterator iter;
	ft::vector<int> st;
	iter begin, end;
	vector<int> sval;

	srand(99987);
	if (ac > 1)
		srand(atoi(av[1]));
	for (size_t i = 0; i < rand() % 900; i++)
		st.push_back(rand() % 80 + 19);


	cout << "_ft::vector: ";	
	print(st);
	// sval.resize(st.)
	sval.resize(st.size());
	copy(st.begin(), st.end(), sval.begin());
	cout << "std::vector: ";
	print(sval);

	// print(st);
	// st.push_back(1);
	// st.push_back(2);
	// st.push_back(3);
	// st.push_back(4);
	// st.push_back(5);
	// st.resize(10, 6);
	// print(st);
	// ft::vector<int>::reverse_iterator it = st.rend();
	// std::cout << *it << std::endl;
	// try{
		// std::cout << st.at(40000) << std::endl;
	// } catch (std::exception const & e) {
	// 	std::cout << e.what() << std::endl;
	// }
	// std::cout << st[500000] << std::endl;
}