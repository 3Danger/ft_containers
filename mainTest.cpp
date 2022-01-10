#include <iostream>
#include <iterator>
#include <stack>
#include <deque>
#include <list>
#include <vector>
#include "vector.hpp"

using namespace ft;
using std::cout;
using std::endl;

namespace test{
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
};

int main( )
{
   vector<char> vc;
   for (size_t i = 0; i < 10; i++)
		vc.push_back('a');
   
   test::iterate(vc);
//   std::list<int> li( 10 );
}