#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include "Comparator.hpp"
#include "pair.hpp"

namespace ft
{
	template< class Key, class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
	public:
		typedef		Key					key_type;
		typedef		T					mapped_type;
		typedef		pair<Key, T>	value_type;
		typedef		size_t				size_type;
		typedef		ptrdiff_t			difference_type;
		typedef		Compare				key_compare;
		typedef		Allocator			allocator_type;
		typedef		value_type&			reference;
		typedef		value_type const&	const_reference;
		typedef		value_type *		pointer;
		typedef		value_type const*	const_pointer;

	    //* typedef bidirectional iterator
	    //* typedef bidirectional reverse_iterator
	    
	// * variables
		struct Node;
	    Node *_node = NULL;
	private:
	    size_type sizeNodes = 0;
	    // *Allocator _allocator;
	    std::allocator<value_type> _allocator;
	    std::allocator<Node>   _nodeAllocator;
	    Compare _cmp;
	 
		// template <class Iter, class Node>
		// struct /*unspecified*/ {
		// 	Iter     position;
		// 	bool     inserted;
		// 	Node node;
		// };
	public:
		map(void){}
		map(const Allocator &__a): _allocator(_allocator){}
		/*
		map(map<Key, T> &&__m);
		map(const map<Key, T> &__m);
		map(_InputIterator __first, _InputIterator __last);
		map(initializer_list<pair<const Key, T> > __l, const Allocator > &__a);
		map(map<Key, T> &&__m, const Allocator > &__a);
		map(const map<Key, T> &__m, const Allocator > &__a);
		map(const less<Key> &__comp, const Allocator > &__a);
		map(_InputIterator __first, _InputIterator __last, const Allocator > &__a)
		map(initializer_list<pair<const Key, T> > __l, const less<Key> &__comp, const Allocator > &__a);
		map(_InputIterator __first, _InputIterator __last, const less<Key> &__comp, const Allocator > &__a);
		~map(void);
		*/

		// map& operator=( const map& other );
		allocator_type get_allocator() const {return _allocator;};
		// T& operator[]( const Key& key );
		// T& operator[]( Key&& key );
	
		// iterator begin();
		// iterator end();
		// reverse_iterator rbegin();
		// reverse_iterator rend();
		// bool empty() const;
		// size_type size() const;
		// size_type max_size() const;
		// void clear();
		// std::pair<iterator, bool> insert( const value_type& value );
		 

		// rbegin
		// crbegin
		
		// Capacity
		// empty
		 
		// size

		// max_size

		// Modifiers
		// clear

		
		bool insert(value_type&& value){
			return insert(value);
		}
		bool insert(const value_type &value){
			if (not _node)
			{
				newNode(value, &_node, NULL);
				return true;
			}
			return insert(value, &_node);
		}
		// pair<iterator, bool> insert(const value_type& value );
		// iterator insert( iterator hint, const value_type& value );

		// void erase( iterator pos );
		// void erase( iterator first, iterator last );
		// size_type erase( const Key& key );
		 
		// void swap( map& other );
		
		// size_type count( const Key& key ) const;
		  
		 
		// iterator find( const Key& key );
		// const_iterator find( const Key& key ) const;
		// std::pair<iterator,iterator> equal_range( const Key& key );
		// std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

		// iterator lower_bound( const Key& key );
		// const_iterator lower_bound( const Key& key ) const;
		
		// iterator upper_bound( const Key& key );
		// const_iterator upper_bound( const Key& key ) const;

		key_compare key_comp() const{
			return _cmp;
		}
		
		class value_compare
		{
			friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {};
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				};
		};

		// value_comp value_compare() const{
		// 	return value_compare(_cmp);
		// } 
		 
		// template< class Key, class T, class Compare, class Alloc >
		// bool operator==(const map<Key,T,Compare,Alloc>& lhs,
        //          const map<Key,T,Compare,Alloc>& rhs );
		// template< class Key, class T, class Compare, class Alloc >
		// void swap(map<Key,T,Compare,Alloc>& lhs,
		//	map<Key,T,Compare,Alloc>& rhs );
		
		
		
		//* SECOND
	// private:
		struct Node
		{
			size_t	_bDepth;
			Node *	_parnt;
			Node *	_rnode;
			Node *	_lnode;
			value_type _value;
			bool isBlack = true;
			
			Node()
				:_parnt(NULL)
				,_rnode(NULL)
				,_lnode(NULL)
				,_value(NULL) {}
			Node(const value_type value, Node * parnt = NULL)
				:_parnt(parnt)
				,_rnode(NULL)
				,_lnode(NULL)
				,_value(value) {}
			explicit Node(const Node &node)
				:_parnt(node->_parnt)
				,_rnode(node->_rnode)
				,_lnode(node->_lnode)
				,_value(node->_value) {}
			~Node();
		};  
    
        bool insert(const value_type& value, Node ** node, Node * parent = NULL)
        {
			if (not *node)
			{
				newNode(value, node, parent);
			}
			else if (value.first == node[0]->_value.first)
				return false;
			else if (_cmp(value.first, node[0]->_value.first))
				return insert(value, &(node[0]->_lnode), *node);
			else
				return insert(value, &(node[0]->_rnode), *node);
			return true;
		}
		
		void newNode(const value_type& value, Node ** node, Node *parent)
		{
			node[0] = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(*node, value, parent);
			if (parent && parent->isBlack)
				node[0]->isBlack = false;
			node[0]->_bDepth = countBlack(*node);
		}
		
		size_t countBlack(Node * node)
		{
			Node * tmp = node;
			size_t counter;
			for (counter = 0; tmp; tmp = tmp->_parnt)
			{
				if (tmp->isBlack)
					counter++;
			}
			return counter;
		}
		
		Node * findMaxDepthNode(Node * node, bool isMain = true)
		{
			Node * l = NULL;
			Node * r = NULL;
			if (node->_lnode)
				l = findMaxDepthNode(node->_lnode, false);
			if (node->_rnode)
				r = findMaxDepthNode(node->_rnode, false);
			if (not isMain)
			{
				if (not node->_lnode && not node->_rnode)
					return node;
				else if (l && not r)
					return l;
				else if (not l && r)
					return r;
				// else if ((not r && not l) || (l->_bDepth == r->_bDepth))
				// 	return NULL;
				return l->_bDepth > r->_bDepth ? l : r;
			}
			if (l && r)
			{
				if (l->_bDepth > r->_bDepth)
					return l;
				else if (l->_bDepth < r->_bDepth)
					return r;
				return NULL;
			}
			return l ? l : r;
		}
	private:
		
	}; // map
} // namespace ft
	