#include <iostream>
//#include <iterator>
//#include <stack>
//#include <deque>
//#include <list>
//#include <vector>
#include "vector.h"
//#include <type_traits>

using namespace ft;
using std::cout;
using std::endl;

int main( )
{
    vector<int>						vc;
	vector<int>::iterator			beg;
	vector<int>::iterator			end;
	vector<int>::reverse_iterator	rbeg;
	vector<int>::reverse_iterator	rend;

	vc.assign(4,7);
//    for (int i = 0; i < 5; ++i) {
//        vc.push_back(i * 1.5 - 1);
//    }
	beg = vc.begin();
	end = vc.end();
	while (!(beg >= end))
		cout << *(beg++) << endl;
	cout << "reverse" << endl;
	rbeg = vc.rbegin();
	rend = vc.rend();
	while(!(rbeg >= rend))
		cout << *rbeg++ << endl;
}