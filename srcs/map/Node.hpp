#pragma once
#include "iterator.hpp"
#include <algorithm>
#include <cstdarg>
#include <cstddef>
#include <memory>

namespace ft{//typename _Alloc
	template <typename pair_type, class Compare, class _Alloc = std::allocator<pair_type> >
	class Node
	{
	public:
		// typedef class std::allocator<pair_type> _Alloc;
		static Compare comparator;
		Node<pair_type> *_root;
		Node<pair_type> *_rnode;
		Node<pair_type> *_lnode;
		_Alloc _allocNode;
		pair_type* _value;
		bool isBlack;
		Node()
			:_root(NULL),
			_rnode(NULL),
			_lnode(NULL),
			_value(NULL) {}
		Node(pair_type* value, Node * root = NULL)
			:_root(root),
			_rnode(NULL),
			_lnode(NULL),
			_value(value) {}
		explicit Node(Node *node)
			:_root(node->root),
			_rnode(node->_rnode),
			_lnode(node->_lnode),
			_value(node->_value) {}
		~Node();

		static bool insert(pair_type* value, Node ** node){
			if (not *node)
			{
				*node = newNode(value);
				return true;
			}
			else if (comparator (*value, *node[0]->_value))
				if (not node[0]->_rnode)
					return _rnode->insert(value, &(node[0]->_rnodem, *node));
			else if (comparator (*value, *node[0]->_value))
				if (not node[0]->_lnode)
					return _lnode->insert(value, &(node[0]->_lnodem, *node));
			return false;
		}

		static Node * newNode(pair_type * value, Node ** node, Node * root){
			// Node node = _allocNode.allocate(1);
			*node = _Alloc::allocate(1);
			_Alloc::construct(node[0]->_value, *value, root);
			return node;
		}
	};    
}