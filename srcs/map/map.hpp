#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include "Node.hpp"

namespace ft
{
	template< class Key, class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<std::pair<const Key, T> > > 
	class map
	{
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
	 
	// template <class Iter, class NodeType>
	// struct /*unspecified*/ {
	// 	Iter     position;
	// 	bool     inserted;
	// 	NodeType node;
	// };
	// instantiated with template arguments iterator and node_type.
	// Member classes
	// value_compare
	 
	// compares objects of type value_type
	// (class)
	// Member functions
	// (constructor)
	 
	// constructs the map
	// (public member function)
	// (destructor)
	 
	// destructs the map
	// (public member function)
	// operator=
	 
	// assigns values to the container
	// (public member function)
	// get_allocator
	 
	// returns the associated allocator
	// (public member function)
	// Element access
	// at
	 
	// access specified element with bounds checking
	// (public member function)
	// operator[]
	 
	// access or insert specified element
	// (public member function)
	// Iterators
	// begin
	// cbegin
	  
	// (C++11)
	 
	// returns an iterator to the beginning
	// (public member function)
	// end
	// cend
	  
	// (C++11)
	 
	// returns an iterator to the end
	// (public member function)
	// rbegin
	// crbegin
	  
	// (C++11)
	 
	// returns a reverse iterator to the beginning
	// (public member function)
	// rend
	// crend
	  
	// (C++11)
	 
	// returns a reverse iterator to the end
	// (public member function)
	// Capacity
	// empty
	 
	// checks whether the container is empty
	// (public member function)
	// size
	 
	// returns the number of elements
	// (public member function)
	// max_size
	 
	// returns the maximum possible number of elements
	// (public member function)
	// Modifiers
	// clear
	 
	// clears the contents
	// (public member function)
	// insert
	 
	// inserts elements or nodes (since C++17)
	// (public member function)
	// insert_or_assign
	  
	// (C++17)
	 
	// inserts an element or assigns to the current element if the key already exists
	// (public member function)
	// emplace
	  
	// (C++11)
	 
	// constructs element in-place
	// (public member function)
	// emplace_hint
	  
	// (C++11)
	 
	// constructs elements in-place using a hint
	// (public member function)
	// try_emplace
	  
	// (C++17)
	 
	// inserts in-place if the key does not exist, does nothing if the key exists
	// (public member function)
	// erase
	 
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
	