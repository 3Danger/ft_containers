#include <iostream>
#include <string>
#include <unistd.h>

#include <stdlib.h>
#include <string>

#include "Visualize.hpp"

#include <cmath>

// #define FT
// #ifndef FT
// #include <map>
// using namespace std;
// #else
#include "map.hpp"
using namespace ft;
// #endif

#define VISUAL


std::ostream& operator<<(std::ostream &os, map<int, std::string>::Node const * node)
{
	if (node)
		os << std::to_string(node->_value.first);
	else
		os << "empty";
	return os;
}

size_t count(map<int, std::string>::Node * node)
{
	size_t res = 0;
	if (not node->_lnode && not node->_rnode)
		res = 1;
	else if (node->_lnode || (node->_rnode))
	{
		if (node->_lnode)
			res += count(node->_lnode);
		if (node->_rnode)
			res += count(node->_rnode);
	}
	
	return res;
}


// #define CONSOLE

int    main()
{
	map<int, std::string>::Node * node;
	map<int, std::string> m;
	std::srand(22);
	Visualize<map<int, std::string>::Node > v(m._node);
	std::cout << "inserted 10" << std::endl;
	m.insert(pair<int, std::string>(10, "_"));
	v.run(m._node);
	std::cout << "inserted 42" << std::endl;
	m.insert(pair<int, std::string>(42, "_"));
	v.run(m._node);
	std::cout << "inserted 64" << std::endl;
	m.insert(pair<int, std::string>(64, "_"));
	v.run(m._node);
	std::cout << "inserted 31" << std::endl;
	m.insert(pair<int, std::string>(31, "_"));
	v.run(m._node);
	std::cout << "inserted 29" << std::endl;
	m.insert(pair<int, std::string>(29, "_"));
	v.run(m._node);
	std::cout << "inserted 83" << std::endl;
	m.insert(pair<int, std::string>(83, "_"));
	v.run(m._node);
	std::cout << "inserted 50" << std::endl;
	m.insert(pair<int, std::string>(50, "_"));
	v.run(m._node);
	std::cout << "inserted 7" << std::endl;
	m.insert(pair<int, std::string>(7, "_"));
	v.run(m._node);
	std::cout << "inserted 5" << std::endl;
	m.insert(pair<int, std::string>(5, "_"));
	std::cout << count(m._node) << std::endl;
	
	v.run(m._node);
	// m.insert(pair<int, std::string>(11, "_"));
	// m.insert(pair<int, std::string>(7, "_"));
	// m.insert(pair<int, std::string>(15, "_"));
	// m.insert(pair<int, std::string>(5, "_"));
	// m.insert(pair<int, std::string>(11, "_"));
	// m.insert(pair<int, std::string>(15, "_"));
	// m.insert(pair<int, std::string>(7, "_"));
	// m.insert(pair<int, std::string>(5, "_"));
	// for (int i = 10; i; --i)
	// {
	// 	// m.insert(pair<int, std::string>(std::rand() % 20, "_"));
	// 	m.insert(pair<int, std::string>(i, "_"));
	// 	// if (i < 6)
	// 	// {
	// 		Visualize<map<int, std::string>::Node > v(m._node);
	// 		v.run();
	// 	// }
	// }
	// std::cout << m.findUnbalancedNode(m._node) << std::endl;
	
	// std::cout << m.findMaxDepthNode(m._node)->_bDepth << std::endl;
	
	// m.insert(pair<int, std::string>(3, "_"));
	// m.insert(pair<int, std::string>(7, "_"));
	// m.insert(pair<int, std::string>(4, "_"));
	// m.insert(pair<int, std::string>(6, "_"));
	// m.insert(pair<int, std::string>(1, "_"));
	// m.insert(pair<int, std::string>(2, "_"));
	
}
/*
#ifdef CONSOLE
	// srand(time(0));
	// std::cout <<"\n##############################################################" << std::endl;
	// std::cout << "###                     ";
	// std::cout  << "MAP                                ###" << std::endl;
	// std::cout << "##############################################################\n" << std::endl;
						// std::cout << "\t\tDefault constructor\n" << std::endl;

	map<int, std::string> map1;
	// std::cout << "map1.size(): " << map1.size() << std::endl;
	// std::cout << "map1.empty(): " << (map1.empty() ? "true" : "false") << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.insert( value_type )\n" << std::endl;

	for (int i = 0; i < 10; ++i)
	{
		int    k = rand() % 21 + 21;
		int    v = rand() % 21 + 21;
		pair<map<int, std::string>::iterator, bool>    res;
		res = map1.insert(make_pair(k, "Str-" + std::to_string(v)));
		// std::cout << "map1.insert( " + std::to_string(k) + ", \"Str-" + std::to_string(v) + "\" ) "
		<< (res.second ? "true" : "false") << std::endl;
	}
	// std::cout << std::endl;
	// std::cout << "map1 key = value:\n";
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << "\t=\t" << it->second << std::endl;
	// std::cout << "map1.size(): " << map1.size() << std::endl;
	// std::cout << "map1.empty(): " << (map1.empty() ? "true" : "false") << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\tRange constructor\n" << std::endl;

	map<int, std::string> map2(map1.begin(), map1.end());
	// std::cout << "\tmap2( map1.begin(), map1.end() )\n" << std::endl;
	// std::cout << "map2 key = value:" << std::endl;
	for (map<int, std::string>::iterator it = map2.begin(), ite = map2.end(); it != ite; ++it)
		// std::cout << it->first << "\t=\t" << it->second << std::endl;
	// std::cout << "map2.size(): " << map2.size() << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.max_size()\n" << std::endl;

	// std::cout << "map1.max_size(): " << map1.max_size() << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.erase( iterator )\n" << std::endl;

	// std::cout << "map1 keys: ";
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << " ";
	// std::cout << std::endl;
	// std::cout << "map1.erase( ++map1.begin() )\n";
	map1.erase(++(map1.begin()));
	// std::cout << "map1 key: ";
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << " ";
	// std::cout << std::endl;
	// std::cout << "map1.size(): " << map1.size() << std::endl;
	// std::cout << "\n\t\t.erase( key_type )\n" << std::endl;
	// std::cout << "map1.erase(1) return: " << map1.erase(1) << std::endl;
	// std::cout << "map1.erase(" + std::to_string((++map1.rbegin())->first) + ") return: " << map1.erase((++map1.rbegin())->first) << std::endl;
	// std::cout << "map1 keys: ";
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << " ";
	// std::cout << std::endl;
	// std::cout << "map1.size(): " << map1.size() << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\toperator[ key_type ]\n" << std::endl;

	map1[42] = "forty two";
	// std::cout << "map1[42] = \"forty two\"\n";
	// std::cout << "map1 key = value:" << std::endl;
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << "\t=\t" << it->second << std::endl;
	// std::cout << "map1.size(): " << map1.size() << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.clear()\n" << std::endl;

	// std::cout << "map1.size(): " << map1.size() << std::endl;
	map1.clear();
	// std::cout << "map1.size(): " << map1.size() << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.swap( map )\n" << std::endl;

	for (int i = 0; i < 10; i++)
		map1.insert(make_pair(i * 2, "Str-" + std::to_string(i * 2)));
	// std::cout << "map1 key(value:)" << std::endl;
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << "(" << it->second << ") ";
	// std::cout << std::endl;
	// std::cout << "map1.size(): " << map1.size() << std::endl;
	// std::cout << "map2 key(value:)" << std::endl;
	for (map<int, std::string>::iterator it = map2.begin(), ite = map2.end(); it != ite; ++it)
		// std::cout << it->first << "(" << it->second << ") ";
	// std::cout << std::endl;
	// std::cout << "map2.size(): " << map2.size() << std::endl;
	// std::cout << "\n\t\tmap1.swap(map2)\n" << std::endl;
	map1.swap(map2);
	// std::cout << "map1 key(value:)" << std::endl;
	for (map<int, std::string>::iterator it = map1.begin(), ite = map1.end(); it != ite; ++it)
		// std::cout << it->first << "(" << it->second << ") ";
	// std::cout << std::endl;
	// std::cout << "map1.size(): " << map1.size() << std::endl;
	// std::cout << "map2 key(value:)" << std::endl;
	for (map<int, std::string>::iterator it = map2.begin(), ite = map2.end(); it != ite; ++it)
		// std::cout << it->first << "(" << it->second << ") ";
	// std::cout << std::endl;
	// std::cout << "map2.size(): " << map2.size() << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout <<"\t\t.lower_bound( key_type )\n" << std::endl;

	// std::cout << "map2.lower_bound(5)->first: " << map2.lower_bound(5)->first << std::endl;
	// std::cout << "map2.lower_bound(5)->second: " << map2.lower_bound(5)->second << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout <<"\t\t.upper_bound( key_type )\n" << std::endl;

	// std::cout << "map2.upper_bound(5)->first: " <<  map2.upper_bound(5)->first << std::endl;
	// std::cout << "map2.upper_bound(5)->second: " <<  map2.upper_bound(5)->second << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.equal_range( key_type )\n" << std::endl;

	pair <map<int, std::string>::iterator, map<int, std::string>::iterator> mtst = map2.equal_range(6);
	// std::cout << "map2.equal_range(6): ";
		// std::cout << mtst.first->first << " - " << mtst.second->first;
	// std::cout << std::endl;

	// std::cout << "\n<+==========================================================+>\n" << std::endl;
						// std::cout << "\t\t.find( key_type )\n" << std::endl;

	// std::cout << "map2.find(6)->first: " << map2.find(6)->first << std::endl;
	// std::cout << "map2.find(6)->second: " << map2.find(6)->second << std::endl;
#endif*/
