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
				delOne(node);
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
				,_color(node->color)
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
				rotateLeft(node->_parent);
				node = node->_lnode;
			} else if ((node == node->_parent->_lnode) && (node->_parent == g->_rnode)) {
				rotateRight(node->_parent);
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
				rotateRight(p_parent);
			} else { /* (node == node->_parent->_rnode) && (node->_parent == p_parent->_rnode) */
				rotateLeft(p_parent);
			}
		}

		void	replace_node(Node ** node, Node ** child) {
			child[0]->_parent = node[0]->_parent;
			if (node == node[0]->_parent[0]->_lnode) {
				node[0]->_parent->_lnode = child;
			} else {
				node[0]->_parent->_rnode = child;
			}
		}
		
		size_type countChilds(Node * node)
		{
			size_type	i = 0;
			node->_lnode && ++i;
			node->_rnode && ++i;
			return i;
		}

		void changeParent(Node * from, Node * to)
		{
			if (from->_parent)
				(
					from->_parent->_lnode == from ? \
					from->_parent->_lnode : \
					from->_parent->_rnode
				) = to;
			else
				_node = to;
			to->_parent = from->_parent;
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

		void delOne(Node * node)
		{
			if (node->_color == RED)
			{
				switch (countChilds(node))
				{
					case 0: /* TODO 0*/; break;
					case 1: /* TODO 1*/ ;break;
					case 2: del_red_2(&node) ;break;
				}
			}
			else
			{
				switch (countChilds(node))
				{
					case 0: del_black_0(node); break;
					case 1: del_black_1(node) ;break;
					case 2: /* TODO 2*/ ;break;
				}
			}
			stupidDelete(node);
		}

		bool isChildBlacks(Node * node)
		{
			return (node->_lnode == NULL || node->_lnode->_color == BLACK)\
					&& (node->_rnode == NULL || node->_rnode->_color == BLACK);
		}

		void del_black_0(Node * node)
		{
			size_type countChilds;
			Node * parent = node->_parent;
			Node * bro = getBrother(node);
			if (parent == NULL)
			{
				return;
			}
			if (parent->_color == RED)
			{
				if (bro == NULL || bro->_color == BLACK)
				{
					if (bro && isChildBlacks(bro))
						std::swap(bro->_color, parent->_color);
					else if (bro == NULL)
						parent->_color = BLACK;
					else if (getNextLine(bro) && getNextLine(bro)->_color == RED)
					{
						bro->_color = RED;
						parent->_color = BLACK;
						if (isRight(bro))
							rotateLeft(parent);
						else
							rotateRight(parent);
					}
					else if ((not getNextLine(bro) || getNextLine(bro)->_color == BLACK) && getNextAngle(bro) && getNextAngle(bro)->_color == RED)
					{
						BB5(node);
					}
				}
			}
			else // * parent is black
			{
				if (bro && bro->_color == RED)
				{
					Node * broAngle = getNextAngle(bro);
					if (not broAngle || broAngle->_color == BLACK)
					{
						if (isChildBlacks(broAngle))
						{
							bro->_color = BLACK;
							broAngle->_color = RED;
							if (isRight(bro))
								rotateLeft(parent->_parent);
							else
								rotateRight(parent->_parent);
						}
						else if (getNextAngle(broAngle) && getNextAngle(broAngle)->_color == RED)
						{
							rotateHard(bro);
						}
					}
				}
				else if (bro) //* bro is BLACK
				{
					Node * angleChild = getNextAngle(bro);
					if (angleChild && angleChild->_color == RED && isChildBlacks(angleChild))
					{
						BB5(node);
					}
				}
			}
		}

		void BB5(Node * node)
		{
			Node * bro = getBrother(node);
			Node * angleChild = getNextAngle(bro);
			angleChild->_color = BLACK;
			rotateHard(bro);
		}


		void rotateHard(Node * _3)
		{
			Node * _7 = _3->_parent;
			Node * _5 = getNextAngle(_3);
			Node * a3 = getNextLine(_3);
			Node * c5 = getNextLine(_5);
			Node * b5 = getNextAngle(_5);

			*getConnect(_3) = c5;
			c5->_parent = _7;
			*getConnect(b5) = _3;
			_3->_parent = _5;
			*getConnect(_5) = b5;
			b5->_parent = _3;
			if (_7->_parent)
				*getConnect(_7) = _5;
			else
				_node = _5;
			_5->_parent = _7->_parent;
			*getConnect(c5) = _7;
			_7->_parent = _5;
			b5->_color = BLACK;
		}

		Node ** getConnect(Node * node)
		{
			return isRight(node) ? &node->_parent->_rnode : &node->_parent->_lnode;
		}

		Node * getNextLine(Node * node)
		{
			if (isRight(node))
				return node->_rnode;
			return node->_lnode;
		}
		Node * getNextAngle(Node * node)
		{
			if (not isRight(node))
				return node->_rnode;
			return node->_lnode;
		}

		bool isRight(Node * node)
		{
			return (node->_parent->_rnode == node);
		}

		void del_black_1(Node * node)
		{
			Node * child = node->_lnode ? node->_lnode : node->_rnode;
			Node * parent = node->_parent;
			swap_values(node, child);
			delOne(child);
		}


		void del_red_2(Node ** node)
		{
			Node * lmax = getLastRight(node[0]->_lnode);
			swap_values(*node, lmax);
			*node = lmax;
		}
		

		
		void swap_values(Node *n1, Node *n2)
		{
			std::swap(n1->_value.first, n2->_value.first);
			std::swap(n1->_value.second, n2->_value.second);
		}
		
		Node * getLastRight(Node * node)
		{
			if (node->_rnode)
				return getLastRight(node->_rnode);
			return node;
		}

		// bool is_sheet(Node * node)
		// {
		// 	return (node && not node->_rnode && not node->_lnode);
		// }
		// //! https://ru.wikipedia.org/wiki/Красно-чёрное_дерево#Удаление
		// void	deleteOne(Node *node)
		// {
		// 	Node *child = is_sheet(n->right) ? n->left : n->right;
		//     if (child)
		//     {
		// 		replace_node(n, child);
		// 		if (n->color == BLACK) {
		// 			if (child->color == RED)
		// 				child->color = BLACK;
		// 			else
		// 				delete_case1(child);
		// 		}
		// 	}
		// 	_nodeAllocator.destroy(node);
		// 	_nodeAllocator.deallocate(node, 1);
		// }
		// void	deleteCase1(Node *node)
		// {
		// 	if (node->_parent != NULL)
		// 		deleteCase2(node);
		// }
		// void deleteCase2(Node *node)
		// {
		// 	Node *s = sibling(node);
		// 	if (not s->_color) {
		// 		node->_parent->_color = false;
		// 		s->_color = true;
		// 		if (node == node->_parent->_lnode)
		// 			rotateLeft(node->_parent);
		// 		else
		// 			rotateRight(node->_parent);
		// 	} 
		// 	deleteCase3(node);
		// }
		// void deleteCase3(Node *node)
		// {
		// 	Node *s = sibling(node);
		// 	if ((node->_parent->_color == true) &&
		// 		(s->_color == true) &&
		// 		(s->_lnode->_color == true) &&
		// 		(s->_rnode->_color == true)) {
		// 		s->_color = false;
		// 		deleteCase1(node->_parent);
		// 	} else
		// 		deleteCase4(node);
		// }
		// void deleteCase4(Node *node)
		// {
		// 	Node *s = sibling(node);
		// 	if ((node->_parent->_color == false) &&
		// 		(s->_color == true) &&
		// 		(s->_lnode->_color == true) &&
		// 		(s->_rnode->_color == true)) {
		// 		s->_color = false;
		// 		node->_parent->_color = true;
		// 	} else
		// 		deleteCase5(node);
		// }
		// void deleteCase5(Node *node)
		// {
		// 	Node *s = sibling(node);
		// 	if  (s->_color == true) {
		// 		if ((node == node->_parent->_lnode) &&
		// 			(s->_rnode->_color == true) &&
		// 			(s->_lnode->_color == false)) {
		// 			s->_color = false;
		// 			s->_lnode->_color = true;
		// 			rotateRight(s);
		// 		} else if ((node == node->_parent->_rnode) &&
		// 				(s->_lnode->_color == true) &&
		// 				(s->_rnode->_color == false)) {
		// 			s->_color = false;
		// 			s->_rnode->_color = true;
		// 			rotateLeft(s);
		// 		}
		// 	}
		// 	deleteCase6(node);
		// }
		// void deleteCase6(Node *node)
		// {
		// 	Node *s = sibling(node);
		// 	s->_color = node->_parent->_color;
		// 	node->_parent->_color = true;
		// 	if (node == node->_parent->_lnode) {
		// 		s->_rnode->_color = true;
		// 		rotateLeft(node->_parent);
		// 	} else {
		// 		s->_lnode->_color = true;
		// 		rotateRight(node->_parent);
		// 	}
		// }
		// Node * sibling(Node *node)
		// {
		// 	if (node == node->_parent->_lnode)
		// 		return node->_parent->_rnode;
		// 	else
		// 		return node->_parent->_lnode;
		// }
		
		Node * grandParent(Node * node)
		{
			if (node && node->_parent)
				return node->_parent->_parent;
			else
				return NULL;
		}
		
		void	rotateLeft(Node *node)
		{
		    Node *pivot = node->_rnode;
			
		    pivot->_parent = node->_parent;
		    if (node->_parent) {
		        if (node->_parent->_lnode==node)
		            node->_parent->_lnode = pivot;
		        else
		            node->_parent->_rnode = pivot;
		    }		
			
		    node->_rnode = pivot->_lnode;
		    if (pivot->_lnode)
		        pivot->_lnode->_parent = node;
		
		    node->_parent = pivot;
		    pivot->_lnode = node;
		    if (not pivot->_parent)
		        _node = pivot;
		}
		
		void	rotateRight(Node *node)
		{
		    Node *pivot = node->_lnode;
			
		    pivot->_parent = node->_parent;
		    if (node->_parent) {
		        if (node->_parent->_lnode==node)
		            node->_parent->_lnode = pivot;
		        else
		            node->_parent->_rnode = pivot;
		    }		
			
		    node->_lnode = pivot->_rnode;
		    if (pivot->_rnode)
		        pivot->_rnode->_parent = node;
		
		    node->_parent = pivot;
		    pivot->_rnode = node;
		    if (not pivot->_parent)
		        _node = pivot;
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
		Node * isOneChild(Node * node)
		{
			if (node->_lnode && not node->_rnode)
				return node->_lnode;
			if (node->_rnode && not node->_lnode)
				return node->_rnode;
			return NULL;
		}
	private:
	}; // map
} // namespace ft
	