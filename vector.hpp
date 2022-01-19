//
// Created by Rasul on 12.01.2022.
//

#ifndef CONTAINERYYY_VECTOR_H
#define CONTAINERYYY_VECTOR_H

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include "sfinae.hpp"
#include <cmath>
#include <cstring>

#include <vector>

using std::runtime_error;
using std::allocator;
using std::max;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_data "exception: vector::iterator: data is not comparable!"
#define EX_DEF_NULL "exeption: trying deference NULL"

#define RESERVE_DEFAULT 10

#define IS_ITERATOR(IS_TYPE, THIS_TYPE)\
typename enable_if<IS_TYPE<typename THIS_TYPE::iterator_category>::value, THIS_TYPE >::type

#define IS_NUM(THIS_TYPE)\
typename enable_if<is_integer<THIS_TYPE>::value, THIS_TYPE>::type

#define IS_CONST_NUM(THIS_TYPE)\
typename enable_if<is_const_integer<THIS_TYPE>::value, THIS_TYPE>::type

#define IS_NO_CONST_NUM(THIS_TYPE)\
typename enable_if<is_no_const_integer<THIS_TYPE>::value, THIS_TYPE>::type

#define IS_NOT_NUM(THIS_TYPE)\
typename enable_if<!is_integer<THIS_TYPE>::value, THIS_TYPE>::type

#define IS_SAME(TYPE1, TYPE2)\
typename enable_if<is_same<TYPE1, TYPE2>::value, TYPE1>::type

// * FT NAMESPACE
namespace ft{
	template <class T, class Allocator = std::allocator<T> >
	class vector{
//		friend class		iterator;
//		friend class		reverse_iterator;
	public:
		typedef Allocator		allocator_type;
		typedef	const T&		const_reference;
		typedef	const T*		const_pointer;
		typedef	T				value_type;
		typedef	T&				reference;
		typedef	T*				pointer;
		typedef long long	difference_type;
	private:
		difference_type			_reserve;
		difference_type			_usedMem;
		difference_type			_hint;
//		Allocator			   _alloc;
		std::allocator<T>		_alloc;
		pointer					_data;
	private:
		//* private methods
		void	setterConstructor(difference_type Reserve = RESERVE_DEFAULT, difference_type UsedMem = 0, difference_type Hint = 0)
		{
			_usedMem = UsedMem;
			_reserve = Reserve;
			_hint = Hint;

			if (_hint < 0)
				throw std::out_of_range("vector");
			if (Hint > 0){
				_data = _alloc.allocate(_hint);
				if (!_data)
					throw runtime_error(NO_MEM_SPACE);
			} else
				_data = NULL;
		}
		void	reallocate(difference_type size, const_reference val = T(), bool mod_2x = false){
			difference_type		newSize;
			value_type *	tmpData;
			difference_type		i;

			newSize = mod_2x ? size << 1 : size;
			if (!(tmpData = _alloc.allocate(max(newSize, _reserve))))
				throw runtime_error(NO_MEM_SPACE);
			if (_usedMem > size)
				_usedMem = size;
			if ((i = _usedMem))
				do{
					i--;
					tmpData[i] = _data[i];
				}while(i);
			i = max(size, _reserve);
			if (i > _usedMem)
				do{
					i--;
					tmpData[i] = val;
				}while(i > _usedMem);
			_alloc.deallocate(_data, _hint);
			_data = tmpData;
			_hint = newSize;
		}

		void delete_data(){
			if (_data) {
				_alloc.deallocate(_data, _hint);
				_data = NULL;
				_hint = 0;
			}
		}

		void new_data(difference_type n){
			_hint = max(n , _reserve);
			_data = _alloc.allocate(_hint);
			if (!_data)
				throw runtime_error(NO_MEM_SPACE);
		}

		void copyFrom(ft::vector<T> const & oth){
			delete_data();
			_hint =	oth._hint;
			_usedMem = oth._usedMem;
			if (_usedMem > 0){
				_data = _alloc.allocate(_hint);
				for (difference_type i = 0; i < _usedMem; i++)
					_data[i] = oth._data[i];
			}
		}
		void	checkData(){if (!_data) throw std::out_of_range(EX_DEF_NULL);}
	public:
//* constructor's / destructor
		explicit vector(const allocator_type& alloc = allocator_type()): _alloc(alloc){setterConstructor();}
		explicit vector(ft::vector<T, Allocator> const & oth, const allocator_type& alloc = allocator_type()): _alloc(alloc){
			setterConstructor();
			copyFrom(oth);
		}
		// * input_iterator constructor
		template <typename InputIterator>
		vector(InputIterator start, InputIterator finish, const allocator_type & alloc = allocator_type(),
			   IS_ITERATOR(is_input_iterator, InputIterator) * = NULL): _alloc(alloc){
			setterConstructor();
			for(; start != finish; ++start)
				push_back(*start);
		}
		// * some_iterators constructor
		template <typename _Iterator>
		vector(_Iterator start, _Iterator finish,
			   IS_ITERATOR(!is_input_iterator, _Iterator) * = NULL){
			difference_type hint = std::distance(start, finish);
			setterConstructor(RESERVE_DEFAULT, 0, hint);
			for(; start != finish; ++start)
				push_back(*start);
		}

		vector(difference_type n, const_reference val){
			setterConstructor(RESERVE_DEFAULT, static_cast<ulong>(n), max(static_cast<ulong>(n << 1), static_cast<ulong>(RESERVE_DEFAULT)));
			for (difference_type i = 0; i < n; i++)
				_data[i] = val;
		}
		vector(difference_type n){
			setterConstructor(RESERVE_DEFAULT, 0, max(static_cast<ulong>(n << 1), static_cast<ulong>(RESERVE_DEFAULT)));
		}
		~vector(){_alloc.deallocate(_data, _hint);}
//*	public methods
		inline difference_type	capacity()	const {return _hint;}
		inline difference_type	size()		const {return _usedMem;}
		inline bool			empty()		const {return !_usedMem || !_data;}
		difference_type			max_size()	const {return _alloc.max_size();}
		reference		operator [](difference_type i)		{return _data[i];}
		const_reference	operator [](difference_type i) const	{return _data[i];}
		inline void		clean()		{_usedMem = 0;}
		reference		at(difference_type i){
			if (i >= _usedMem || i < 0 || !_data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		const_reference	at(difference_type i) const{
			if (i >= _usedMem || i < 0 || !_data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		void			push_back(const value_type & value){
			if (!_data){
				_hint = _reserve;
				_data = _alloc.allocate(_hint);
				if (!_data)
					throw runtime_error(NO_MEM_SPACE);
			} else if (_usedMem == _hint){
				reallocate(_hint, T(), true);
			}
			_data[_usedMem++] = value;
		}
		void			swap(ft::vector<T> & oth){
			std::swap(_reserve, oth._reserve);
			std::swap(_usedMem, oth._usedMem);
			std::swap(_alloc, oth._alloc);
			std::swap(_hint, oth._hint);
			std::swap(_data, oth._data);
		}
		// assign with input_iterator
		template <typename input_itertor>
		void assign(input_itertor start, input_itertor finish,
					IS_ITERATOR(is_input_iterator, input_itertor) * = NULL){
			std::cout << "input_iterator" << std::endl;
			_usedMem = 0;
			for(;start != finish; ++start){
				push_back(*start);
			}
		}
		// assign with random_access_iterator
		template <typename _iter>
		void assign(_iter start, _iter finish,
					IS_ITERATOR(!is_input_iterator, _iter) * = NULL){
			difference_type len = std::distance(start, finish);
			if (len > _hint) {
				delete_data();
				new_data(len);
			}
			_usedMem = 0;
			while(_usedMem < len)
				_data[_usedMem++] = *start++;
		}
		// assign with integer & T parameter
		void assign(difference_type n, const_reference value){
			if (n > _hint){
				delete_data();
				new_data(n);
			}
			for (difference_type i = 0; i < n; i++)
				_data[i] = value;
			_usedMem = n;
		}

		void	resize(difference_type n, const_reference val = T()){
			if (n < 0 && n > _alloc.max_size())
				throw runtime_error("э, пошол отсюда!!! что за ресайз??");
			else if (n == 0){
				clean();
				return ;
			}
			else if (_usedMem > n)
				_usedMem = n;
			reallocate(n, val);
		}

		void reserve(const difference_type & newSize){
			if (newSize > _hint)
				reallocate(newSize);
			_reserve = newSize;
		}

		void	shrink_to_fit(){
			if (_usedMem == _hint)
				return ;
			reallocate(_usedMem);
		}

		void	pop_back(){
			delete _data[--_usedMem];
		}
		// * iterators
	public:
		class const_iterator {
		public:
			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef const T *const_pointer;
			typedef const T &const_reference;
			typedef std::random_access_iterator_tag iterator_category;
		protected:
			friend class vector;
			pointer		_data;
			long		_usedMem;
			long		_iter;
			long		_direction;
			const_iterator(pointer data, difference_type usedMem, difference_type currentIter, difference_type direction = 0)
					: _data(data), _usedMem(usedMem), _iter(currentIter), _direction(direction) {}
		public:
			const_iterator(const_iterator const & oth)
				:_data(oth._data), _usedMem(oth._usedMem), _iter(oth._iter), _direction(oth._direction){}
			const_iterator(difference_type num)
					: _data(NULL), _usedMem(0), _iter(num) {}
			const_iterator()
					: _data(NULL), _usedMem(0), _iter(0) {}
		protected:
			void compare(const_iterator const &oth) {
				if (oth._data != _data)
					throw runtime_error(NO_COMPARE_data);
			}
			reference check_range(difference_type num){
				if (num >= _usedMem || num < 0)
					return _data[_usedMem - 1];
				return _data[std::abs(_direction - num)];
			}

		public:
			const_pointer	operator->() {return &check_range(_iter);}
			const_reference operator*() const {return check_range(_iter);}
			const_reference	operator[](difference_type num){return check_range(num);}
			bool operator< (const const_iterator &rhs) const { return _iter <  rhs._iter; }
			bool operator==(const const_iterator &rhs) const { return _iter == rhs._iter; }
			bool operator!=(const const_iterator &rhs) const { return _iter != rhs._iter; }
			bool operator> (const const_iterator &rhs) const { return _iter >  rhs._iter; }
			bool operator<=(const const_iterator &rhs) const { return _iter <= rhs._iter; }
			bool operator>=(const const_iterator &rhs) const { return _iter >= rhs._iter; }

			const_iterator operator--(int) {const_iterator tmp(*this); --_iter;	return tmp;}
			const_iterator operator++(int) {const_iterator tmp(*this); ++_iter;	return tmp;}
			const_iterator &operator++() {_iter++; return *this;}
			const_iterator &operator--() {_iter--; return *this;}
			friend const_iterator operator-(const const_iterator & it1, const const_iterator & it2);
			friend const_iterator operator+(const const_iterator & it1, const const_iterator & it2);
			const_iterator &operator+=(difference_type const num){_iter += num; return *this;}
			const_iterator &operator-=(difference_type const num){_iter -= num; return *this;}
			const_iterator &operator=(const const_iterator &oth) {
				const_iterator::_usedMem = oth._usedMem;
				const_iterator::_iter = oth._iter;
				const_iterator::_data = oth._data;
				return *this;
			}
			const_iterator operator+(const const_iterator & oth) const {
				const_iterator tmp(oth);
				tmp._iter += oth._iter;
				return tmp;
			}
			const_iterator operator-(const const_iterator & oth) const {
				const_iterator tmp(oth);
				tmp._iter -= oth._iter;
				return tmp;
			}

			const_iterator operator+(difference_type num) const {
				const_iterator tmp(*this);
				tmp._iter += num;
				return tmp;
			}

			const_iterator operator-(difference_type num) const {
				const_iterator tmp(*this);
				tmp._iter -= num;
				return tmp;
			}
		};

		class iterator: public const_iterator{
			typedef	const_iterator super;
			friend class vector<T, Allocator>;
			iterator(pointer data, difference_type usedMem, difference_type iter): const_iterator(data, usedMem, iter){}
		protected:
			friend class ft::vector<T>;
		public:
			iterator(){}
			iterator(const_iterator const & oth): const_iterator(oth){}
			reference	operator*()		{return this->check_range(super::_iter);}
			pointer		operator->()	{return &this->check_range(super::_iter);}
			reference	&operator[](difference_type const num){return super::check_range(num);}
		};
		class const_reverse_iterator: public const_iterator{
			typedef	const_iterator super;
			friend class vector<T, Allocator>;
			const_reverse_iterator(pointer data, difference_type usedMem, difference_type iter)
			: super(data, usedMem, iter, usedMem - 1){}
		public:
			const_reverse_iterator(){}
			const_reverse_iterator(const_iterator const & oth):super(oth){}
		};
		class reverse_iterator: public const_iterator{
			typedef	const_iterator super;
			friend class vector<T, Allocator>;
			reverse_iterator(pointer data, difference_type usedMem, difference_type iter)
				: super(data, usedMem, iter, usedMem - 1){}
		public:
			reverse_iterator(){}
			reverse_iterator(const_iterator const & oth)
				:super(oth), super::_direction(_usedMem - 1){}
			reference	operator*()		{return this->check_range(super::_iter);}
			pointer		operator->()	{return &this->check_range(super::_iter);}
			reference	&operator[](difference_type const num){return super::check_range(num);}
		};
// * begin and end
		reverse_iterator	rbegin(){return reverse_iterator(_data, _usedMem, _usedMem -1);}
		iterator			begin(){return iterator(_data, _usedMem, 0);}
		reverse_iterator	rend(){return reverse_iterator(_data, _usedMem, -1);}
		iterator			end(){return iterator(_data, _usedMem, _usedMem);}

		const_reverse_iterator	crbegin() const {return const_reverse_iterator(_data, _usedMem, _usedMem -1);}
		const_iterator			cbegin() const {return const_iterator(_data, _usedMem, 0);}
		const_reverse_iterator	crend() const {return const_reverse_iterator(_data, _usedMem, -1);}
		const_iterator			cend() const {return const_iterator(_data, _usedMem, _usedMem);}

		const_reference		front() const	{this->checkData(); return _data[0];}
		const_reference		back()	const	{this->checkData(); return _data[_usedMem -1];}
		reference			front() 		{this->checkData(); return _data[0];}
		reference			back()			{this->checkData(); return _data[_usedMem -1];}
	private:
		bool	_insert(difference_type pos, const_reference value, difference_type count = 1){
			difference_type i;
			if (_data && _usedMem + count <= _hint){
				for (i = _hint -1; i <= pos ; --i)
					_data[i + count] = _data[i];
				for (i = 0; i < count; i++)
					_data[pos + i] = value;
				_usedMem += count;
				return true;
			}
			return false;
		}
	public:
		template<typename iterator>
		iterator	insert(const_iterator pos, const_reference value){
			if (!_data || !_usedMem)
				push_back(value);
			else if (!_insert(pos._iter, value)) {
				if (pos._iter >= _hint){
					push_back(value);
				}else{
					reallocate(_usedMem, NULL, true);
					for(difference_type i = _hint - 1; i > pos._iter; --i) {
						_data[i + 1] = _data[i];
					}
					_data[pos->iter] = value;
					_usedMem++;
				}
			}
			return pos;
		}
		iterator	insert(const_iterator pos, difference_type count, value_type value){
			difference_type i;
			difference_type iter;

			iter = pos._iter;
			if (!_data || !_usedMem){
				for (i = 0; i < count; ++i, ++pos._usedMem)
					push_back(value);
				return pos;
			}
			else if (!_insert(iter, value, count)) {
				if (iter >= _hint){
					for (i = 0; i < count; i++)
						push_back(value);
				} else {
					reallocate((_usedMem + count) << 1);
					for(i = _hint - 1; i >= iter; --i)
						_data[i + count] = _data[i];
					for(i = 0; i < count; ++i)
						_data[iter + i] = value;
					_usedMem += count;
				}
			}
			pos._usedMem = _usedMem;
			return pos;
		}
		template <class InputIterator>
    	iterator insert (iterator position, InputIterator first, InputIterator last, IS_NOT_NUM(InputIterator)* = 0){
			difference_type count = std::distance(first, last);
			difference_type i;
			
			if (_usedMem + count > _hint)
				reallocate((_usedMem + count) << 1);
			std::memmove(&_data[position._iter + count], &_data[position._iter], sizeof(T) * ((_usedMem - position._iter) + 1));
			for(i = position._iter; first != last; ++i, ++first)
				_data[i] = *first;
			_usedMem += count;
			position._usedMem = _usedMem;
			return position;
		}

		bool operator > (vector<T, Allocator> const & v1) const {
			const_iterator thisBegin, thisEnd;
			const_iterator othBegin, othEnd;

			thisBegin	= cbegin();
			thisEnd		= cend();
			othBegin	= v1.cbegin();
			othEnd		= v1.cend();

			while(thisBegin != thisEnd && othBegin != othEnd && *thisBegin == *othBegin){
				++thisBegin;
				++othBegin;
			}
			if (thisBegin == thisEnd && othBegin == othEnd)
				return false;
			else if (thisBegin == thisEnd)
				return false;
			else if (othBegin == othEnd)
				return true;
			return *thisBegin > *othBegin;
		}
		bool operator < (vector<T, Allocator> const & v1) const {
			const_iterator thisBegin, thisEnd;
			const_iterator othBegin, othEnd;

			thisBegin	= cbegin();
			thisEnd		= cend();
			othBegin	= v1.cbegin();
			othEnd		= v1.cend();

			while(thisBegin != thisEnd && othBegin != othEnd && *thisBegin == *othBegin){
				++thisBegin;
				++othBegin;
			}
			if (thisBegin == thisEnd && othBegin == othEnd)
				return false;
			else if (thisBegin == thisEnd)
				return false;
			else if (othBegin == othEnd)
				return true;
			return *thisBegin < *othBegin;
		}
		bool operator >= (vector<T, Allocator> const & v1) const {
			const_iterator thisBegin, thisEnd;
			const_iterator othBegin, othEnd;

			thisBegin	= cbegin();
			thisEnd		= cend();
			othBegin	= v1.cbegin();
			othEnd		= v1.cend();

			while(thisBegin != thisEnd && othBegin != othEnd && *thisBegin < *othBegin){
				++thisBegin;
				++othBegin;
			}
			if (thisBegin == thisEnd && othBegin == othEnd)
				return true;
			else if (thisBegin == thisEnd)
				return false;
			else if (othBegin == othEnd)
				return true;
			return *thisBegin >= *othBegin;
		}
		bool operator <= (vector<T, Allocator> const & v1) const {
			const_iterator thisBegin, thisEnd;
			const_iterator othBegin, othEnd;

			thisBegin	= cbegin();
			thisEnd		= cend();
			othBegin	= v1.cbegin();
			othEnd		= v1.cend();

			while(thisBegin != thisEnd && othBegin != othEnd && *thisBegin > *othBegin){
				++thisBegin;
				++othBegin;
			}
			if (thisBegin == thisEnd && othBegin == othEnd)
				return true;
			else if (thisBegin == thisEnd)
				return false;
			else if (othBegin == othEnd)
				return true;
			return *thisBegin <= *othBegin;
		}
		bool operator == (vector<T, Allocator> const & v1) const {
			const_iterator thisBegin, thisEnd;
			const_iterator othBegin, othEnd;

			thisBegin	= cbegin();
			thisEnd		= cend();
			othBegin	= v1.cbegin();
			othEnd		= v1.cend();

			while(thisBegin != thisEnd && othBegin != othEnd && *thisBegin == *othBegin){
				++thisBegin;
				++othBegin;
			}
			if (thisBegin == thisEnd && othBegin == othEnd)
				return true;
			else if (thisBegin == thisEnd)
				return false;
			else if (othBegin == othEnd)
				return true;
			return false;
		}
		bool operator != (vector<T, Allocator> const & v1) const {return !operator==(v1);}
	};
	//template <typename V>
	//class reverse_iterator: public V{
	//	public:
	//	template<typename VI>
	//	reverse_iterator(VI const &oth_iter): V::V(oth_iter){}
	//	V&	base(){return this->V;}
	//};

	//class _reverse_iterator: public std::vector<int>::iterator{
	//	typedef typename _reverse_iterator::std::vector<int>::iterator base;
	//	public:
	//	std::vector<int>::iterator::
	//	template<typename VI>
	//	reverse_iterator(VI const &oth_iter): base::(oth_iter){}
	//};
	//template <typename V>
	//class const_reverse_iterator: public V{};
};
#endif //CONTAINERYYY_VECTOR_H
