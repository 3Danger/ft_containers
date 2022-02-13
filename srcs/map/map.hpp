#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include "Comparator.hpp"

#include "Node.hpp"
#include "pair.hpp"

namespace ft
{
	template< class Key, class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > > 
	class map
	{
	public:
		typedef		Key					key_type;
		typedef		T					mapped_type;
		typedef		pair<const Key, T>	value_type;
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
	    
	private:
	    Node<value_type, Compare> *_node = NULL;
	    unsigned int sizeNodes = 0;
	    Allocator _allocator;
	 
		// template <class Iter, class NodeType>
		// struct /*unspecified*/ {
		// 	Iter     position;
		// 	bool     inserted;
		// 	NodeType node;
		// };
	public:
		map(void){}
		map(const Allocator &__a): __a(_allocator){}
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
		allocator_type get_allocator() const {return _allocator};
		// T& operator[]( const Key& key );
		// T& operator[]( Key&& key );
	
		iterator begin();
		iterator end();
		reverse_iterator rbegin();
		reverse_iterator rend();
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void clear();
		std::pair<iterator, bool> insert( const value_type& value );
		 

		// rbegin
		// crbegin
		
		// Capacity
		// empty
		 
		// size

		// max_size

		// Modifiers
		// clear

		// insert

		void erase( iterator pos );
		void erase( iterator first, iterator last );
		size_type erase( const Key& key );
		// erases elements
		// (public member function)
		// swap
		 
		// swaps the contents
		// (public member function)
		// extract
		  
		// (C++17)
		 
		// extracts nodes from the container
		// (public member function)
		// merge
		  
		// (C++17)
		 
		// splices nodes from another container
		// (public member function)
		// Lookup
		// count
		 
		// returns the number of elements matching specific key
		// (public member function)
		// find
		 
		// finds element with specific key
		// (public member function)
		// contains
		  
		// (C++20)
		 
		// checks if the container contains element with specific key
		// (public member function)
		// equal_range
		 
		// returns range of elements matching a specific key
		// (public member function)
		// lower_bound
		 
		// returns an iterator to the first element not less than the given key
		// (public member function)
		// upper_bound
		 
		// returns an iterator to the first element greater than the given key
		// (public member function)
		// Observers
		// key_comp
		 
		// returns the function that compares keys
		// (public member function)
		// value_comp
		 
		// returns the function that compares keys in objects of type value_type
		// (public member function)
		// Non-member functions
		// operator==
		// operator!=
		// operator<
		// operator<=
		// operator>
		// operator>=
		// operator<=>
		  
		// (removed in C++20)
		// (removed in C++20)
		// (removed in C++20)
		// (removed in C++20)
		// (removed in C++20)
		// (C++20)
		 
		// lexicographically compares the values in the map
		// (function template)
		// std::swap(std::map)
		 
		// specializes the std::swap algorithm
		// (function template)
		// erase_if(std::map)
		  
		// (C++20)
		 
		// Erases all elements satisfying specific criteria
		// (function template)
	
	};
} // namespace ft
	