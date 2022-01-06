#include <iostream>
#include <stack>
#include <deque>
#include <vector>
// #include "vector.hpp"


template<class Container>
void	print(Container con){
	typename Container::iterator beg = con.begin();
	typename Container::iterator end = con.end();

	while(beg != end)
		std::cout << *beg++ << ". ";
	std::cout << std::endl;
}

int main(){
	std::vector<int> st;
	print(st);
	st.push_back(1);
	st.push_back(2);
	st.push_back(3);
	st.push_back(4);
	st.push_back(5);
	st.resize(10, 6);
	print(st);
	std::cout << *st.end() << std::endl;
	// try{
		// std::cout << st.at(40000) << std::endl;
	// } catch (std::exception const & e) {
	// 	std::cout << e.what() << std::endl;
	// }
	// std::cout << st[500000] << std::endl;
}