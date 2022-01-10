#include <iostream>
#include <iterator>
#include <stack>
#include <deque>
#include <list>
#include <vector>
#include "vector.hpp"
#include <type_traits>

using namespace ft;
using std::cout;
using std::endl;



namespace test{

	template <bool, typename T>
	struct switch_if{};
	template <typename T>
	struct switch_if<true, T>{typedef T type;};

	template<class Iterator>
	typename switch_if<std::__is_input_iterator<Iterator>::value, Iterator>::type *
	whatType(Iterator first, Iterator last) {
		std::cout << "input iterator\n";
		return nullptr;
	}
	template<class Iterator>
	typename switch_if<!std::__is_input_iterator<Iterator>::value, Iterator>::type *
	whatType(Iterator first, Iterator last) {
		std::cout << "NOT input iterator\n";
		return nullptr;
	}

	template<typename Container>
	size_t	myDistance(Container begin, Container end){
		size_t count = 0;
		while(!(begin - 3 == end)  && ++count)
			begin++;
		return count;
	}
	template<typename C>
	void	iterate(C c){
		size_t dis;

		dis = myDistance(c.rbegin(), c.rend());
		cout << "iterateReverce distance = " << dis << endl;
		dis = myDistance(c.begin(), c.end());
		cout << "iterate distance = " << dis << endl;
	}

	template <typename T>
	void print(T t, typename T::iterator * = NULL){
		typename T::iterator begin = t.begin();
		typename T::iterator end = t.end();
		while(begin != end)
			cout << "*being = " << *begin++ << endl;
	}
};

int main( )
{
   vector<int> vc;
   std::list<int> li;
   std::vector<int> svc;
   svc.assign(5, 25);
   vc.assign(svc.begin(), svc.end());
   cout << "vc = ";
   test::print(vc);
   cout << "svc = ";
   test::print(svc);
//    for (size_t i = 0; i < 10; i++)
// 		vc.push_back('a');
   
// 	std::list<int> li( 10 );
	// test::iterate(vc);
	test::whatType(vc.begin(),vc.end());
	test::whatType(li,li);
}