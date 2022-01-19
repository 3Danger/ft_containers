#include <iostream>
//#include <iterator>
#include <vector>
#include <string>
#include <list>
#include "vector.hpp"
#include <typeinfo>


using std::cout;
using std::endl;

//using namespace ft;
//using namespace std;

template <typename T> void
printer(){
	std::string str = "HelloWorld howAreYou?";
	T t(str.begin(), str.end());
	t.reserve(100);
	typename T::iterator beg = t.begin();
	typename T::iterator end = t.end();
	cout << "distance = " << std::distance(beg, end) << "; ";
	cout << "size = " << t.size() << "; ";
	cout << "cap = " << t.capacity() << "; ";
	cout << "max = " << t.max_size() << "; ";
//	cout << " = " << (std::vector<char>());
	while(beg != end)
		cout << *beg++ << "|";
	cout << endl;
}

template <typename T> void
rprinter(){
	std::string str = "HelloWorld howAreYou?";
	T t(str.begin(), str.end());
	t.reserve(100);
	typename T::reverse_iterator beg = t.rbegin();
	typename T::reverse_iterator end = t.rend();
	cout << "distance = " << std::distance(beg, end) << "; ";
	cout << "size = " << t.size() << "; ";
	cout << "cap = " << t.capacity() << "; ";
	cout << "max = " << t.max_size() << "; ";
//	cout << " = " << (std::vector<char>());
	while(beg != end)
		cout << *beg++ << "|";
	cout << endl;
}

int main( )
{
	std::vector<int> ar = {9,8,7,6,5,4,3,2,1};
	//std::vector<char> cc;
//	cc.
	//printer<std::vector<char> >();
	//printer<ft::vector<char> >();
	//rprinter<std::vector<char> >();
	//rprinter<ft::vector<char> >();
	//ft::reverse_iterator my_rit(ar.begin(), ar.end());
}
