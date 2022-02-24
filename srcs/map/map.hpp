#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include "Comparator.hpp"
#include "Visualize.hpp"
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
		typedef		pair<Key, T>		value_type;
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
	    Node *_node;
	private:
		typedef enum e_color{RED, BLACK} eColor;
	    size_type _sizeNodes;
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
		map(void): _node(NULL), _sizeNodes(0) {}
		map(const Allocator &__a): _node(NULL),  _sizeNodes(0), _allocator(_allocator){}
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

		
		// bool insert(value_type&& value){
		// 	return insert(value);
		// }
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
		size_type erase( const Key& key )
		{
			if (not _node)
				return 0;
			Node * node = findNode(key, _node);
			if (node)
			{
				if (node == _node)
				{
					if (node->_lnode || node->_rnode)
					{
						Node * n = findToSwap(node->_lnode, true);
						if (n == NULL)
							n = findToSwap(node->_rnode, false);
						std::swap(n->_value.first, node->_value.first);
						std::swap(n->_value.second, node->_value.second);
						node = n;
					}
					else
					{
						_nodeAllocator.destroy(node);
						_nodeAllocator.deallocate(node, 1);
						_node = NULL;
						_sizeNodes = 0;
						return 1;
					}
				}
				delete_one_child(node);
				return 1;
			}
			return 0;
		}
		 
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
			eColor  _color;
			Node *	_rnode;
			Node *	_lnode;
			Node *	_parent;
			
			Node()
				:_count(0)
				,_value(NULL)
				,_color(RED)
				,_rnode(NULL)
				,_lnode(NULL)
				,_parent(NULL){}
			Node(const value_type value, Node * parnt = NULL)
				:_count(0)
				,_value(value)
				,_color(RED)
				,_rnode(NULL)
				,_lnode(NULL)
				,_parent(parnt){}
			explicit Node(const Node &node)
				:_count(node->_count)
				,_value(node->_value)
				,_color(node->_color)
				,_rnode(node->_rnode)
				,_lnode(node->_lnode)
				,_parent(node->_parent){}
			~Node(){};
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
			//TODO remark _color and recount black nodes
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
		
		Node * findNode(Key const & key, Node * root)
		{
			if (key == root->_value.first)
				return root;
			if (_cmp(key, root->_value.first))
			{
				if (root->_lnode)
					return findNode(key, root->_lnode);
			}
			else
			{
				if (root->_rnode)
					return findNode(key, root->_rnode);
			}
			return NULL;
		}
		
		Node * findToSwap(Node * node, bool toRight)
		{
			if (toRight && node->_rnode)
				return findToSwap(node->_rnode, toRight);
			else if (not toRight && node->_lnode)
				return findToSwap(node->_lnode, toRight);
			else
				return node;
		}
		
		bool newNode(const value_type& value, Node ** node, Node *parent)
		{
			++_sizeNodes;
			node[0] = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(*node, value, parent);
			insertCase_1(*node);
			return true;
		}

		
		void insertCase_1(Node *node)
		{
			if (node->_parent)
				insertCase_2(node);
			else
				node->_color = BLACK;
		}
		
		void insertCase_2(Node *node)
		{
			if (node->_parent->_color)
				return ;
			else
				insertCase_3(node);
		}
		
		void insertCase_3(Node *node)
		{
			Node *brother = getBrother(node), *p_parent;
		
			if (brother && not brother->_color) {
				node->_parent->_color = BLACK;
				brother->_color = BLACK;
				p_parent = node->_parent->_parent;
				p_parent->_color = RED;
				insertCase_1(p_parent);
			} else {
				insertCase_4(node);
			}
		}
		
		void insertCase_4(Node *node)
		{
			Node *g = grandParent(node);
		
			if ((node == node->_parent->_rnode) && (node->_parent == g->_lnode)) {
				rotate_left(node->_parent);
				node = node->_lnode;
			} else if ((node == node->_parent->_lnode) && (node->_parent == g->_rnode)) {
				rotate_right(node->_parent);
				node = node->_rnode;
			}
			insertCase_5(node);
		}
		
		void insertCase_5(Node *node)
		{
			Node *p_parent = node->_parent->_parent;
		
			node->_parent->_color = BLACK;
			p_parent->_color = RED;
			if ((node == node->_parent->_lnode) && (node->_parent == p_parent->_lnode)) {
				rotate_right(p_parent);
			} else { /* (node == node->_parent->_rnode) && (node->_parent == p_parent->_rnode) */
				rotate_left(p_parent);
			}
		}

		void breakParent(Node * node)
		{
			Node ** connect;
			if (node->_parent->_lnode == node)
				connect = &node->_parent->_lnode;
			else
				connect = &node->_parent->_rnode;
			if (*connect == node)
				*connect = NULL;
			node->_parent = NULL;
		}
	
		void stupidDelete(Node * node)
		{
			if (node->_parent)
				breakParent(node);
			else
				_node = NULL;
			_nodeAllocator.destroy(node);
			_nodeAllocator.deallocate(node, 1);
			--_sizeNodes;
		}

		Node * sibling(Node *n)
		{
			if (isRight(n))
				return n->_parent->_lnode;
			else
				return n->_parent->_rnode;
		}

		void replace_node(Node* n, Node* child) {
		    child->_parent = n->_parent;
		    if (isRight(n)) {
		        n->_parent->_rnode = child;
		    } else {
		        n->_parent->_lnode = child;
		    }
		}
		
		// void makeParent(Node * node)
		// {
		// 	Node * parent = _nodeAllocator.allocate(1);
		// 	// _nodeAllocator.construct(parent, void);
		// 	node->_parent = parent;
		// 	parent->_lnode = node;
		// 	parent->_rnode = node;
		// }
		
		// void removeParent(Node * node)
		// {
		// 	Node * parent = node->_parent;
		// 	node->_parent = NULL;
		// 	// _nodeAllocator.destroy(parent);
		// 	_nodeAllocator.deallocate(parent, 1);
		// }
		
		bool is_leaf(Node * node)
		{
			return (not node) || (not node->_lnode && not node->_rnode);
		}
		
		void delete_one_child(Node *n)
		{
			/*
			 * Условие: n имеет не более одного ненулевого потомка.
			 */
			Node *child = is_leaf(n->_rnode) ? n->_lnode : n->_rnode;
		    
			// replace_node(n, child);
			if (n->_color == BLACK) {
				if (child && child->_color == RED)
					child->_color = BLACK;
				else
					delete_case1(n);
			}
			stupidDelete(n);
		}
		
		void delete_case1(Node *n)
		{
			if (n->_parent != NULL)
				delete_case2(n);
		}
		
		void delete_case2(Node *n)
		{
			Node *s = sibling(n);
		
			if (isRed(s)) {
				n->_parent->_color = RED;
				s->_color = BLACK;
				if (isRight(n))
					rotate_right(n->_parent);
				else
					rotate_left(n->_parent);
			} 
			delete_case3(n);
		}
		
		void delete_case3(Node *n)
		{
			Node *s = sibling(n);
		
			if ((isBlack(n->_parent)) &&
			    (isBlack(s)) &&
			    isChildBlacks(s)) {
				s->_color = RED;
				delete_case1(n->_parent);
			} else
				delete_case4(n);
		}
		
		void delete_case4(Node *n)
		{
			Node *s = sibling(n);
		
			if (isRed(n->_parent) && isBlack(s) && isChildBlacks(s)) {
				s->_color = RED;
				n->_parent->_color = BLACK;
			} else
				delete_case5(n);
		}
		
		void delete_case5(Node *n)
		{
			Node *s = sibling(n);
		
			if  (isBlack(s)) {
				if (not isRight(n) && isBlack(s->_rnode) && isRed(s->_lnode)) { /* this last test is trivial too due to cases 2-4. */
					s->_color = RED;
					s->_lnode->_color = BLACK;
					rotate_right(s);
				} else if (isRight(n) && isBlack(s->_lnode) && isRed(s->_rnode)) {/* this last test is trivial too due to cases 2-4. */
					s->_color = RED;
					s->_rnode->_color = BLACK;
					rotate_left(s);
				}
			}
			delete_case6(n);
		}
		
		void delete_case6(Node *n)
		{
			Node *s = sibling(n);
		
			s->_color = n->_parent->_color;
		    n->_parent->_color = BLACK;
		
			if (n == n->_parent->_lnode) {
		        s->_rnode->_color = BLACK;
				rotate_left(n->_parent);
			} else {
				s->_lnode->_color = BLACK;
				rotate_right(n->_parent);
			}
		}

		bool isChildBlacks(Node * node)
		{
			return isBlack(node->_lnode) && isBlack(node->_rnode);
		}

		bool isRight(Node * node)
		{
			return (node->_parent->_rnode == node);
		}

		//! https://ru.wikipedia.org/wiki/Красно-чёрное_дерево#Удаление

		bool isRed(Node * node){
			return node && node->_color == RED;
		}
		
		bool isBlack(Node * node){
			return not node || node->_color == BLACK;
		}
		
		Node * grandParent(Node * node)
		{
			if (node && node->_parent)
				return node->_parent->_parent;
			else
				return NULL;
		}
		
	//? EXAMPLE rotate _lnode
	/*
	*
	*        0
	*         \
	*		  5
	*		/   \
	*	   3     8
	*	  / \   / \
	*	 2   4 6   7
	*
	*               0
	*               \
	*             . . 8 //! pivot
	*           . .   \
	*		  5.       7
	*		/   ..  
	*	   3      .6
	*	  / \ 
	*	 2   4
	*
	*            0
	*            \
	*            8 //! pivot
	*          /  \
	*		  5   7
	*		/   \ 
	*	   3     6
	*	  / \ 
	*	 2   4
	*/
	
		void	rotate_left(Node *node)
		{
		    Node *pivot = node->_rnode;
			
		    pivot->_parent = node->_parent;
		    if (node->_parent) {
		        if (node->_parent->_lnode==node)
		            node->_parent->_lnode = pivot;
		        else
		            node->_parent->_rnode = pivot;
		    }
		    else
		        _node = pivot;
			
		    node->_rnode = pivot->_lnode;
		    if (pivot->_lnode)
		        pivot->_lnode->_parent = node;
		
		    node->_parent = pivot;
		    pivot->_lnode = node;
		}
		
		void	rotate_right(Node *node)
		{
		    Node *pivot = node->_lnode;
			
		    pivot->_parent = node->_parent;
		    if (node->_parent) {
		        if (node->_parent->_lnode==node)
		            node->_parent->_lnode = pivot;
		        else
		            node->_parent->_rnode = pivot;
		    }
		    else
		        _node = pivot;
			
		    node->_lnode = pivot->_rnode;
		    if (pivot->_rnode)
		        pivot->_rnode->_parent = node;
		
		    node->_parent = pivot;
		    pivot->_rnode = node;
		}
		
		Node * getBrother(Node *node)
		{
			Node * g = grandParent(node);
			if (g == NULL)
				return NULL; // No grandParent means no uncle
			if (node->_parent == g->_lnode)
				return g->_rnode;
			else
				return g->_lnode;
		}
	private:
	}; // map
} // namespace ft
	