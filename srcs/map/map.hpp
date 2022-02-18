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
			node[0] = _nodeAllocator.allocate(1);
			_nodeAllocator.construct(*node, value, parent);
			if (not parent)
			{
				node[0]->_count = 1;
				node[0]->isBlack = true;
			}
			// TODO this balance red black
			else if (not parent->isBlack)
			{
				node[0]->_count = parent->_count + 1;
			}
			else
			{
				node[0]->_count = parent->_count;
			}
			
			for(Node * tmp = *node; tmp
				&&(isRedRedBlackRedSimple(tmp)
				|| isRedRedBlackRed(tmp)
				|| isRedRedBlackBlack(tmp)
				|| isRedRedBlackRedRoot(tmp)); tmp = tmp->_parent);
			// if (isDoubleSimple(*node))
			// 	std::cout << "isDoubleSimple(*node)" << std::endl;
			
			// else if ()
				
				
			
			
				
			
			++sizeNodes;
			// isBalanced(_node);
			return true;
			// node[0]->_count = countBlack(*node);
		}
		
		bool isRedRedBlackBlack(Node * node)
		{
			if (not node->isBlack && node->_parent && node->_parent->_parent)
			{
				Node * parent = node->_parent;
				if (not parent->isBlack && parent->_parent )
				{
					if (parent->_parent->isBlack)
					{
						Node *bro = getBro(parent);
						if (not bro || bro->isBlack)
						{
							std::cout << "isRedRedBlackBlack" << std::endl;
							parent->isBlack = true;
							if (parent->_parent)
								parent->_parent->isBlack = false;
							// if (not (not bro && parent->_parent))
								mainRotate(node);
							return true;
						}
					}
					
				}
			}
			return false;
		}
		
		bool isRedRedBlackRedRoot(Node * node)
		{
			Node * parent = node->_parent;
			Node * pparent = parent ? parent->_parent : NULL;
			if (not node->isBlack && parent && pparent && not parent->isBlack)
			{
				if ((not pparent->_parent && pparent->isBlack))
				{
					Node * bro = getBro(parent);
					if (bro && not bro->isBlack)
					{
						std::cout << "isRedRedBlackRedRoot" << std::endl;
						bro->isBlack = true;
						parent->isBlack = true;
						node->isBlack = false;
						return true;
					}
				}
			}
			return false;
		}
		
		bool isRedRedBlackRedSimple(Node * node)
		{
			Node * parent = node->_parent;
			Node * pparent = parent ? parent->_parent : NULL;
			if (not node->isBlack && parent && not parent->isBlack)
			{
				if (pparent/*->_parent*/ && pparent->isBlack)
				{
					Node * bro = getBro(node->_parent);
					if (bro && not bro->isBlack && isNotChild(bro))
					{
						std::cout << "isRedRedBlackRed_Simple()" << std::endl;
						parent->isBlack = true;
						if (bro)
							bro->isBlack = true;
						node->isBlack = false;
						return true;
					}
				}
			}
			return false;
		}
		
		bool isRedRedBlackRed(Node * node)
		{
			Node * parent = node->_parent;
			Node * pparent = parent ? parent->_parent : NULL;
			if (not node->isBlack && parent && not parent->isBlack)
			{
				if (pparent/*->_parent*/ && pparent->isBlack)
				{
					Node * bro = getBro(node->_parent);
					if (bro && not bro->isBlack)
					{
						std::cout << "isRedRedBlackRed(tmp)" << std::endl;
						pparent->isBlack = false;
						if (bro)
							bro->isBlack = true;
						node->isBlack = true;
						mainRotate(node);
						return true;
					}
				}
			}
			return false;
		}
		
		bool isDoubleSimple(Node * node)
		{
			Node * parent = node->_parent;
			if (not parent)
				return false;
			Node * pparent = parent->_parent;
			if (parent && pparent && isOneChild(parent) && isOneChild(pparent))
			{
				Node * bro = getBro(parent);
				if (not parent->isBlack && not node->isBlack && pparent->isBlack && (not bro || bro->isBlack))
				{
					parent->isBlack = true;
					pparent->isBlack = false;
					mainRotate(node);
					return true;
				}
			}
			return false;
		}
		
		bool isNotChild(Node * node)
		{
			return not node->_lnode && not node->_rnode;
		}
		
		bool isHaveChild(Node * node)
		{
			return node->_lnode || node->_rnode;
		}

		bool isOneChild(Node * node)
		{
			if (not node->_lnode && node->_rnode)
				return true;
			if (node->_lnode && not node->_rnode)
				return true;
			return false;
		}
		
		Node * getBro(Node * node)
		{
			if (node && node->_parent)
				return (node == node->_parent->_lnode ? node->_parent->_rnode : node->_parent->_lnode);
			return NULL;
		}
		
		Node * isOneHandSameParent(Node * node)
		{
			while(node->_parent)
			{
				node = node->_parent;
				if (not node->_lnode || not node->_rnode)
					return node;
			}
			return NULL;
		}
		
		bool isBackRed(Node * node)
		{
			if (not node->_parent)
				return true;
			return not node->_parent->isBlack;
		}
		
		// bool isBalanced(Node * node)
		// {
				
		// 	if (not node)
		// 		return true;
		// 	Node * findMax = maxCount(node);
		// 	if (findMax && findMax->_count < 2)
		// 		return true;
		// 	if (findMax && findMax != node)
		// 		mainRotate(findMax);
		// 	return true; // TODO изменить!
		// }

		Node ** getParentConnect(Node * node)
		{
			if (not node->_parent)
				return NULL;
			if (node == node->_parent->_lnode)
				return &node->_parent->_lnode;
			return &node->_parent->_rnode;
		}
		
		void breakParent(Node * node)
		{
			Node ** oneConnect = getParentConnect(node);
			if (oneConnect)
				*oneConnect = NULL;
			node->_parent = NULL;		
		}
		
		void setParentFrom(Node * node, Node * from)
		{
			node->_parent = NULL;
			if (not from || not from->_parent)
				return ;
			node->_parent = from->_parent;
			Node ** fromConnect = getParentConnect(node);
			if (fromConnect)
				*fromConnect = node;
		}
		
		void mainRotate(Node * node)
		{
			
			if (node && node->_parent && node->_parent->_parent)
			{
				if (detectTypeMicroPattern(node))
					rotateNodeSlash(node);
				else
				{
					rotateNodeAngle(node);
					
				}
			}
		}
		
		/**
		 * @brief detecting type, angle or slash microPattern
		 * 
		 * @param node 
		 * @return true if slash
		 * @return false is angle
		 */
		bool detectTypeMicroPattern(Node * node)
		{
			Node * three, *two, *one;
			three = node;
			two = node->_parent;
			one = two->_parent;
			if (one->_value.first < three->_value.first)
			{
				if (three->_value.first > two->_value.first)
					return true;
				else
					return false;
			}
			else
			{
				if (three->_value.first < two->_value.first)
					return true;
				else
					return false;
			}
		}
		
		
			
		void rotateNodeSlash(Node * three)
		{
			std::cout << "rotateNodeSlash(Node* three)" << std::endl;
			
			Node * two = three->_parent;
			Node * one = two->_parent;
			breakParent(two);
			setParentFrom(two, one);
			if (one)
				insert(&two, two, one);
			if (not two->_parent)
				_node = two;
			// updateMark(_node, true);
			// updateMark(two, one ? one->isBlack : true);
		}
		
		//TODO !!!!!!!!!
		void rotateNodeAngle(Node * three)
		{
			std::cout << "rotateNodeAngle(Node * three)" << std::endl;
			
			Node * two = three->_parent;
			Node * one = two->_parent;
			Node * zero = one->_parent;
			
			breakConnectToParrent(two);
			breakConnectToParrent(three);
			if (zero)
			{
				*getConnect(one) = three;
				three->_parent = zero;
				// insert(&zero, zero, three);
			}
			insert(&three, three, two);
			insert(&three, three, one);
			if (not one->_parent->isBlack)
				one->isBlack = true;
		}
		
		void breakConnectToParrent(Node * node)
		{
			if (not node || not node->_parent)
				return ;
			*getConnect(node) = NULL;
			node->_parent = NULL;
		
		}
		
		Node ** getConnect(Node * node)
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
		
		void updateMark(Node * node, bool isBlackColor = true)
		{
			node->isBlack = isBlackColor;
			isBlackColor = !isBlackColor;
			if (node->_lnode)
				updateMark(node->_lnode, isBlackColor);
			if (node->_rnode)
				updateMark(node->_rnode, isBlackColor);
			if (node->_lnode || node->_rnode)
			{
				if (not node->isBlack)
					node->_count = (node->_lnode ? node->_lnode->_count : node->_rnode->_count) - 1;
				else
					node->_count = (node->_lnode ? node->_lnode->_count : node->_rnode->_count);
			}
			else
				node->_count = countBlack(node);
				
		}
		
		size_t countBlack(Node * node)
		{
			Node * tmp = node;
			size_t counter;
			for (counter = 0; tmp; tmp = tmp->_parent)
			{
				if (tmp->isBlack)
					counter++;
			}
			return counter;
		}
	private:
		
	}; // map
} // namespace ft
	