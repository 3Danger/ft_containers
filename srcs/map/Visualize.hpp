#pragma once

#include "map.hpp"
#include <string>


template <class Key, class T >
class Visualize{
public:
	typedef ft::map<Key, T> map_t;
	typedef typename map_t::Node node_t;
	node_t * _node;
	size_t deep = 0;
	Visualize(map_t & m): _node(m._node){}
	size_t recDepth(node_t * node, size_t s = 0)
	{
		if (not node)
			return s;
		s++;
		return (std::max(recDepth(node->_lnode, s), recDepth(node->_rnode, s)));
	}
	void recRun(node_t * node)
	{
		deep = recDepth(node);
		std::cout << "deep " << deep << std::endl;
		
	}
	
	void run()
	{
		recRun(_node);
	}
	
	
}; //Visualizen