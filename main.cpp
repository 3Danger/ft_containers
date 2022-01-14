#include <iostream>
//#include <iterator>
#include <vector>
#include <string>
#include <list>
#include "vector.h"
//#include <type_traits>

//#include <stack>
//#include <deque>
//#include <list>
//using namespace ft;
//using namespace std;
using std::cout;
using std::endl;


//template<bool B, class T = void>
//struct e_if {};
//
//template<class T>
//struct e_if<true, T> { typedef T type; };

int main( )
{
	ft::vector<char>::iterator				fbeg;
	ft::vector<char>::iterator				fend;

//	std::vector<char>::iterator				sbeg;
//	std::vector<char>::iterator				send;

	std::string str = "hello";

//	std::vector<char>						svc(str.begin(), str.end());
    std::list<char>						slc(str.begin(), str.end());
    ft::vector<char>						fvc(slc.begin(), slc.end());

//	ft::vector<char>						fvc(12, '-');
//	std::vector<char>						svc(12, '+');
//
//	svc.
//	fbeg = fvc.begin();
//	fend = fvc.end();
//
//	sbeg = svc.begin();
//	send = svc.end();
//
	cout << "ft:\n";
//	for(int i = 0; fbeg != fend; ++fbeg)
//		cout << *fbeg << " - " << i++ << endl;
	int x = fvc.end() - fvc.begin();
	cout << x << endl;
	for (int i = 0; i < x; ++i) {
		cout << fvc[i] << endl;
	}
//	cout << "std:\n";
//	for(int i = 0; sbeg != send; ++sbeg)
//		cout << *sbeg << " - " << i++ << endl;
}
