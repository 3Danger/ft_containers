#pragma once

#include "map.hpp"
#include <string>
#include <sstream>

#include <iostream>
#include <utility>
#include <algorithm>
#include <list>

#include "../ColourConsole.hpp"


template <class Key, class T >
class Visualize{
public:
	typedef ft::map<Key, T> map_t;
	typedef typename map_t::Node node_t;
	node_t * _node;
	size_t deep = 0;
	std::stringstream str;
	Visualize(map_t & m): _node(m._node)
	{
		deep = recDepth(_node) + 4;
	}


	size_t recDepth(node_t * node, size_t s = 0)
	{
		if (not node)
			return s;
		s++;
		return (std::max(recDepth(node->_lnode, s), recDepth(node->_rnode, s)));
	}

	int _print_t(node_t *tree, int is_left, int offset, int depth, char s[20][255])
	{
	    char b[deep];
	    int width = 5;
	
	    if (!tree) return 0;
	
	    sprintf(b, " %03d ", tree->_value.first);
	
	    int left  = _print_t(tree->_lnode,  1, offset,                depth + 1, s);
	    int right = _print_t(tree->_rnode, 0, offset + left + width, depth + 1, s);
	
	    for (int i = 0; i < width; i++)
	        s[2 * depth][offset + left + i] = b[i];
	
	    if (depth && is_left) {
	
	        for (int i = 0; i < width + right; i++)
	            s[2 * depth - 1][offset + left + width/2 + i] = '-';
	
	        s[2 * depth - 1][offset + left + width/2] = '+';
	        s[2 * depth - 1][offset + left + width + right + width/2] = '+';
	
	    } else if (depth && !is_left) {
	
	        for (int i = 0; i < left + width; i++)
	            s[2 * depth - 1][offset - width/2 + i] = '-';
	
	        s[2 * depth - 1][offset + left + width/2] = '+';
	        s[2 * depth - 1][offset - width/2 - 1] = '+';
	    }	
	    return left + width + right;
	}
	
	void run(size_t _deep = 10)
	{
		node_t *tree = _node;
	    char s[deep][255];
	    for (int i = 0; i < deep; i++)
	        sprintf(s[i], "%80s", " ");
	
	    _print_t(tree, 0, 0, 0, s);
	
	    for (int i = 0; i < deep; i++)
	    {
	        if (i & 1)
				std::cout << CC::getColor() << s[i] << CC::getColor() << std::endl;
			else
				std::cout << CC::getColor(CC::GREEN) << s[i] << CC::getColor(CC::RESET) << std::endl;
		}
	    // for (int i = 0; i < deep; i++)
	    //     printf("%s\n", s[i]);
	}
};


	
// }; //Visualizen
// template <class Key, class T >
// class Visualize{
// 	std::string    spaceWriter(int size, std::string spaceSym = " ")
// 	{
// 		std::stringstream s;
// 		for (int i = 0; i < size; i++)
// 			s << spaceSym;
// 		return s.str();
// 	}
// public:
// 	typedef ft::map<Key, T> map_t;
// 	typedef typename map_t::node_t node_t;
// 	node_t * _node;
// 	size_t deep = 0;
// 	std::stringstream str;
// 	Visualize(map_t & m): _node(m._node){}
// 	size_t recDepth(node_t * node, size_t s = 0)
// 	{
// 		if (not node)
// 			return s;
// 		s++;
// 		return (std::max(recDepth(node->_lnode, s), recDepth(node->_rnode, s)));
// 	}
// 	std::string recRun(size_t size, size_t deepCounter, node_t * node, char tree)
// 	{
// 		std::string result;
// 		std::string value;
// 		std::string spaces = spaceWriter(size + 1);
// 		if (deepCounter && not node)
// 			return spaces + " ";
// 		if (not deepCounter)
// 		{
// 			value = node ? std::to_string(node->_value.first) : std::string("n");
// 			result += spaces + value;
// 			return result;
// 		}
// 		return	recRun(size >> 1, deepCounter -1, node->_lnode, '/') + 
// 				recRun(size >> 1, deepCounter -1, node->_rnode, '\\');
// 	}
	
// 	void run()
// 	{
// 		deep = recDepth(_node);
		
// 		for (size_t i = 0; i < deep; i++)
// 		{
			
// 			std::cout << std::endl;
// 			std::cout << recRun(deep << 1, i, _node, '|') << std::endl;
// 		}
		
// 		std::cout << str.str() << std::endl;
		
// 	}
	
	
// }; //Visualizen