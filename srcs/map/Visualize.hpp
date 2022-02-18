#pragma once

// #include "map.hpp"
#include <string>
#include <sstream>

#include <iostream>
#include <utility>
#include <algorithm>
#include <list>

#include "../ColourConsole.hpp"


template <class node_t>
class Visualize{
public:
	node_t * _node;
	size_t deep = 0;
	std::stringstream str;
	Visualize(node_t * m): _node(m)
	{
		deep = recDepth(_node) + 8;
	}
	// Visualize(map_t & m): _node(m._node)
	// {
	// 	deep = recDepth(_node) + 4;
	// }


	size_t recDepth(node_t * node, size_t s = 0)
	{
		if (not node)
			return s;
		s++;
		return (std::max(recDepth(node->_lnode, s), recDepth(node->_rnode, s)));
	}

	int _print_t(node_t *tree, int is_left, int offset, int depth, char s[64][255])
	{
	    char b[deep];
	    int width = 5;
	
	    if (!tree) return 0;
	
		if (tree->isBlack)
	        sprintf(b, "%02dblk", tree->_value.first);
	    else
	        sprintf(b, "%02dred", tree->_value.first);
	
	    int left  = _print_t(tree->_lnode,  1, offset,                depth + 1, s);
	    int right = _print_t(tree->_rnode, 0, offset + left + width, depth + 1, s);
	
	    for (int i = 0; i < width; i++)
	        s[2 * depth][offset + left + i] = b[i];
	
	    if (depth && is_left) {
	
	        for (int i = 0; i < width + right; i++)
	            s[2 * depth - 1][offset + left + width/2 + i] = '-';
	
	        s[2 * depth - 1][offset + left + width/2] = '/';
	        s[2 * depth - 1][offset + left + width + right + width/2] = '|';
	
	    } else if (depth && !is_left) {
	
	        for (int i = 0; i < left + width; i++)
	            s[2 * depth - 1][offset - width/2 + i] = '-';
	
	        s[2 * depth - 1][offset + left + width/2] = '\\';
	        s[2 * depth - 1][offset - width/2 - 1] = '|';
	    }	
	    return left + width + right;
	}
	
	void run(node_t * node = NULL)
	{
		
		node_t *tree = node ? node : _node;
	    char s[deep][255];
	    for (int i = 0; i < deep; i++)
	        sprintf(s[i], "%80s", " ");
	
	    _print_t(tree, 0, 0, 0, s);
	
	    for (int i = 0; i < deep; i++)
	    {
	        std::string ss(s[i]);
	        std::string::size_type pos = 0;
	        if (i & 1)
				std::cout << CC::getColor() << ss << CC::getColor() << std::endl;
			else
			{
				while(pos != ss.npos)
					std::cout << getNext(ss, pos);
				std::cout << std::endl;
				// std::cout << CC::getColor(CC::GREEN) << s[i] << CC::getColor() << std::endl;
			}
		}
	}
	std::string getNext(std::string line, std::string::size_type & posPrev)
	{
		std::string::size_type pos;
		std::string::size_type posB = line.find_first_of("blk", posPrev);
		std::string::size_type posR = line.find_first_of("red", posPrev);
		
		pos = std::min(posB, posR);
		if (pos != posPrev)
		{
			std::swap(pos, posPrev);
			return line.substr(pos, (posPrev - pos) - 2) + " ";
		}
		posPrev = pos+2;
		if (posB < posR)
		{
			return CC::getColor(CC::BLUE, CC::BLACK) + line.substr(pos-2, 2) + CC::getColor();
		}
		return CC::getColor(CC::RED) + line.substr(pos-2, 2) + CC::getColor();
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