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
			// std::cout << "inserted " << value.first << std::endl;
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
			size_t	_count;
			value_type _value;
			bool isBlack = false;
			Node *	_rnode;
			Node *	_lnode;
			Node *	_parent;
			
			Node()
				:_count(0)
				,_value(NULL)
				,_rnode(NULL)
				,_lnode(NULL)
				,_parent(NULL){}
			Node(const value_type value, Node * parnt = NULL)
				:_count(0)
				,_value(value)
				,_rnode(NULL)
				,_lnode(NULL)
				,_parent(parnt){}
			explicit Node(const Node &node)
				:_count(node->_count)
				,_value(node->_value)
				,_rnode(node->_rnode)
				,_lnode(node->_lnode)
				,_parent(node->_parent){}
			~Node();
		};  
    
        bool insert(const value_type& value, Node ** node, Node * parent = NULL)
        {
			if (not *node)
				return newNode(value, node, parent);
			else if (value.first == node[0]->_value.first)
				return false;
			else if (_cmp(value.first, node[0]->_value.first))
				return insert(value, &(node[0]->_lnode), *node);
			else
				return insert(value, &(node[0]->_rnode), *node);
		}
		
		void insert(Node ** where, Node * parent, Node * node)
		{
			//TODO remark color and recount black nodes
			if (not *where)
			{
				*where = node;
				node->_parent = parent;
			}
			else if (node->_value.first == where[0]->_value.first)
				return ;
			else if (_cmp(node->_value.first, where[0]->_value.first))
				insert(&where[0]->_lnode, where[0], node);
			else
				insert(&where[0]->_rnode, where[0], node);
				
		}
		
		
		bool newNode(const value_type& value, Node ** node, Node *parent)
		{
			++sizeNodes;
			node[0] = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(*node, value, parent);
			// TODO this balance red black
			Node * tmp = *node;
			// while(tmp)
			// {
				case_1(tmp);
			// 	tmp = tmp->_parent;
			// }
			return true;
			// node[0]->_count = countBlack(*node);
		}
		
		void case_1(Node *node)
		{
			if (node->_parent)
				case_2(node);
			else
				node->isBlack = true;
		}
		
		void case_2(Node *node)
		{
			if (node->_parent->isBlack)
				return; /* Tree is still valid */
			else
				case_3(node);
		}
		
		void case_3(Node *node)
		{
			Node *brother = getBrother(node), *p_parent;
		
			if (brother && not brother->isBlack) {
			// && (node->parent->color == RED) Второе условие проверяется в case_2, то есть родитель уже является красным.
				node->_parent->isBlack = true;
				brother->isBlack = true;
				p_parent = node->_parent->_parent;
				p_parent->isBlack = false;
				case_1(p_parent);
			} else {
				case_4(node);
			}
		}
		
		void case_4(Node *node)
		{
			Node *g = grandparent(node);
		
			if ((node == node->_parent->_rnode) && (node->_parent == g->_lnode)) {
				rotate_left(node->_parent);
		
				/*
				 * rotate_left может быть выполнен следующим образом, учитывая что уже есть *g =  grandparent(node) 
				 *
				 * Node *saved_p=g->_lnode, *saved_left_n=node->_lnode;
				 * g->_lnode=node; 
				 * node->_lnode=saved_p;
				 * saved_p->_rnode=saved_left_n;
				 * 
				 */
		
				node = node->_lnode;
			} else if ((node == node->_parent->_lnode) && (node->_parent == g->_rnode)) {
				rotate_right(node->_parent);
		
				/*
				 * rotate_right может быть выполнен следующим образом, учитывая что уже есть *g =  grandparent(node) 
				 *
				 * Node *saved_p=g->_rnode, *saved_right_n=node->_rnode;
				 * g->_rnode=node; 
				 * node->_rnode=saved_p;
				 * saved_p->_lnode=saved_right_n;
				 * 
				 */
		
				node = node->_rnode;
			}
			case_5(node);
		}
		
		void case_5(Node *node)
		{
			Node *p_parent = node->_parent->_parent;
		
			node->_parent->isBlack = true;
			p_parent->isBlack = false;
			if ((node == node->_parent->_lnode) && (node->_parent == p_parent->_lnode)) {
				rotate_right(p_parent);
			} else { /* (node == node->_parent->_rnode) && (node->_parent == p_parent->_rnode) */
				rotate_left(p_parent);
			}
		}
		
		Node * grandparent(Node * node)
		{
			if (node && node->_parent)
				return node->_parent->_parent;
			else
				return NULL;
		}
		
		void
		rotate_left(Node *n)
		{
		    Node *pivot = n->_rnode;
			
		    pivot->_parent = n->_parent; /* при этом, возможно, pivot становится корнем дерева */
		    if (n->_parent) {
		        if (n->_parent->_lnode==n)
		            n->_parent->_lnode = pivot;
		        else
		            n->_parent->_rnode = pivot;
		    }		
			
		    n->_rnode = pivot->_lnode;
		    if (pivot->_lnode)
		        pivot->_lnode->_parent = n;
		
		    n->_parent = pivot;
		    pivot->_lnode = n;
		    if (not pivot->_parent)
		        _node = pivot;
		}
		
		void
		rotate_right(Node *n)
		{
		    Node *pivot = n->_lnode;
			
		    pivot->_parent = n->_parent; /* при этом, возможно, pivot становится корнем дерева */
		    if (n->_parent) {
		        if (n->_parent->_lnode==n)
		            n->_parent->_lnode = pivot;
		        else
		            n->_parent->_rnode = pivot;
		    }		
			
		    n->_lnode = pivot->_rnode;
		    if (pivot->_rnode)
		        pivot->_rnode->_parent = n;
		
		    n->_parent = pivot;
		    pivot->_rnode = n;
		    if (not pivot->_parent)
		        _node = pivot;
		}
		
		Node * getBrother(Node *n)
		{
			Node * g = grandparent(n);
			if (g == NULL)
				return NULL; // No grandparent means no uncle
			if (n->_parent == g->_lnode)
				return g->_rnode;
			else
				return g->_lnode;
		}

		
		// /**
		//  * @brief detecting type, angle or slash microPattern
		//  * 
		//  * @param node 
		//  * @return true if slash
		//  * @return false is angle
		//  */
		// bool detectTypeMicroPattern(Node * node)
		// {
		// 	Node * three, *two, *one;
		// 	three = node;
		// 	two = node->_parent;
		// 	one = two->_parent;
		// 	if (one->_value.first < three->_value.first)
		// 	{
		// 		if (three->_value.first > two->_value.first)
		// 			return true;
		// 		else
		// 			return false;
		// 	}
		// 	else
		// 	{
		// 		if (three->_value.first < two->_value.first)
		// 			return true;
		// 		else
		// 			return false;
		// 	}
		// }
		
		
			
		// void rotateNodeSlash(Node * three)
		// {
		// 	std::cout << "rotateNodeSlash(Node* three)" << std::endl;
			
		// 	Node * two = three->_parent;
		// 	Node * one = two->_parent;
		// 	breakParent(two);
		// 	setParentFrom(two, one);
		// 	if (one)
		// 		insert(&two, two, one);
		// 	if (not two->_parent)
		// 		_node = two;
		// 	// updateMark(_node, true);
		// 	// updateMark(two, one ? one->isBlack : true);
		// }
		
		// //TODO !!!!!!!!!
		// void rotateNodeAngle(Node * three)
		// {
		// 	std::cout << "rotateNodeAngle(Node * three)" << std::endl;
			
		// 	Node * two = three->_parent;
		// 	Node * one = two->_parent;
		// 	Node * zero = one->_parent;
			
		// 	// breakParent(two);
		// 	breakParent(three);
		// 	breakParent(two);
		// 	Node ** connectOfOne = getConnectFromParent(one);
		// 	if (connectOfOne)
		// 		*connectOfOne = three;
		// 	else
		// 		_node = three;
		// 	three->_parent = zero;
		// 	insert(&three, three, one);
		// 	insert(&three, three, two);
		// }
		
		Node ** getConnectFromParent(Node * node)
		{
			Node * parent = node->_parent;
			if (parent)
			{
				if (parent->_lnode == node)
					return &parent->_lnode;
				return &parent->_rnode;
			}
			return NULL;
		}
		
		Node * maxCount(Node * node)
		{
			Node *l = NULL, *r = NULL;
			if(node->_lnode)
				l = maxCount(node->_lnode);
			if(node->_rnode)
				r = maxCount(node->_rnode);
			if ((r && not l) || (r && l && r->_count > l->_count))
				return r;
			else if ((not r && l) || (r && l && r->_count < l->_count))
				return l;
			if (l && r && l->_count == r->_count)
				return NULL;
			return node;
		}
	private:
		
	}; // map
} // namespace ft
	