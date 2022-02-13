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
		typedef     Node<value_type, Compare> node_type;
	    //* typedef bidirectional iterator
	    //* typedef bidirectional reverse_iterator
	    
	private:
	    node_type *_node = NULL;
	    size_type sizeNodes = 0;
	    Allocator _allocator;
	    Compare _cmp;
	 
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
		 
		//!

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
        //    map<Key,T,Compare,Alloc>& rhs );
	
	};
} // namespace ft
	