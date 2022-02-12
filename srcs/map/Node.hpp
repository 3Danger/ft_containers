#pragma once
#include "iterator.hpp"
#include <algorithm>
#include <cstdarg>
#include <cstddef>
#include <memory>

namespace ft{//typename _Alloc
	template <typename T, typename _Alloc = std::allocator<T> >
	class Node
	{
	public:
		// typedef class std::allocator<T> _Alloc;
		Node<T> *_root;
		Node<T> *_rnode;
		Node<T> *_lnode;
		_Alloc _allocNode;
		T* _value;
		bool isBlack;
		Node()
			:_root(NULL),
			_rnode(NULL),
			_lnode(NULL),
			_value(NULL) {}
		Node(T* value, Node * root)
			:_root(NULL),
			_rnode(NULL),
			_lnode(NULL),
			_value(value) {}
		explicit Node(const Node *node)
			:_root(NULL),
			_rnode(node->_rnode),
			_lnode(node->_lnode),
			_value(node->_value) {}
		~Node();

		static void insert(T* value, Node ** root){
			if (not *root)
				*root = newNode(value);
			else if (not root[0]->_value)
				root[0]->_value = value;
			else if (*value > *root[0]->_value)
				_rnode ? _rnode->insert(value, root) : _rnode = newNode(value, *root);
			else if (*value < *root[0]->_value)
				_lnode ? _lnode->insert(value, root) : _lnode = newNode(value, *root);
		}

		static Node * newNode(T * value, Node * root = NULL){
			Node node = _allocNode.allocate(1);
			_allocNode.construct(node->_value, *value, root);
			return node;
		}
	};    
}