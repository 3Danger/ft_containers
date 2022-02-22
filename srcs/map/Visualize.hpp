#pragma once

// #include "map.hpp"
#include <string>
#include <sstream>

#include <iostream>
#include <utility>
#include <algorithm>
#include <list>

#include "../ColourConsole.hpp"


template <class Node>
class Visualize{
public:
	// std::stringstream str;
	Visualize(){}
	size_t recDepth(Node * node, size_t s = 0)
	{
		if (not node)
			return s;
		s++;
		return (std::max(recDepth(node->_lnode, s), recDepth(node->_rnode, s)));
	}

	struct Trunk
	{
		Trunk *prev;
		std::string str;
	
		Trunk(Trunk *prev, std::string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};
	
	// Helper function to print branches of the binary tree
	void showTrunks(Trunk *p)
	{
		if (p == nullptr) {
			return;
		}
	
		showTrunks(p->prev);
		std::cout << p->str;
	}
	
	void run(int const & x, Node* root, Trunk *prev = NULL, bool isLeft = false)
	{
		if (root == nullptr) {
			return;
		}
	
		std::string prev_str = "    ";
		Trunk *trunk = new Trunk(prev, prev_str);
	
		run(x, root->_rnode, trunk, true);
	
		if (!prev) {
			trunk->str = "———";
		}
		else if (isLeft)
		{
			trunk->str = "+——-";
			prev_str = "   |";
		}
		else {
			trunk->str = "+——";
			prev->str = prev_str;
		}
	
		showTrunks(trunk);
		if (x != root->_value.first)
		{
			if (root->_color)
				std::cout << " " << CC::getColor(CC::BLUE) << root->_value.first << CC::getColor() << std::endl;
			else
				std::cout << " " << CC::getColor(CC::RED) << root->_value.first << CC::getColor() << std::endl;
		}
		else
		{
			if (root->_color)
				std::cout << " " << CC::getColor(CC::WHITE, CC::BLUE) << root->_value.first << CC::getColor() << std::endl;
			else
				std::cout << " " << CC::getColor(CC::WHITE, CC::RED) << root->_value.first << CC::getColor() << std::endl;
		}
	
		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = "   |";
	
		run(x, root->_lnode, trunk, false);
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
// 	typedef typename map_t::Node Node;
// 	Node * _node;
// 	size_t deep = 0;
// 	std::stringstream str;
// 	Visualize(map_t & m): _node(m._node){}
// 	size_t recDepth(Node * node, size_t s = 0)
// 	{
// 		if (not node)
// 			return s;
// 		s++;
// 		return (std::max(recDepth(node->_lnode, s), recDepth(node->_rnode, s)));
// 	}
// 	std::string recRun(size_t size, size_t deepCounter, Node * node, char tree)
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