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
#include <typeinfo>

#include <vector>

using std::runtime_error;
using std::allocator;
using std::max;
using std::min;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_data "exception: vector::iterator: data is not comparable!"
#define EX_DEF_NULL "exeption: trying deference NULL"

#define RESERVE_DEFAULT 5

#define IS_ITERATOR(IS_TYPE, THIS_TYPE)\
typename enable_if<IS_TYPE<typename THIS_TYPE::iterator_category>::value, THIS_TYPE >::type

#define IS_ALLNUM(THIS_TYPE)\
typename enable_if<is_integer<THIS_TYPE>::value || is_float<THIS_TYPE>::value, THIS_TYPE>::type

#define IS_NUM(THIS_TYPE)\
typename enable_if<is_integer<THIS_TYPE>::value, THIS_TYPE>::type

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
		typedef Allocator			allocator_type;
		typedef	T					value_type;
		typedef	value_type		 	&reference;
		typedef	value_type		 	*pointer;
		typedef	value_type const 	&const_reference;
		typedef	value_type const 	*const_pointer;
		typedef ptrdiff_t			difference_type;
		typedef size_t				size_type;
	private:
		size_type				_reserve;
								//acceptable memory
		size_type				_aMem;
								//used memory
		size_type				_uMem;
								//capacity memory
		size_type				_cMem;
//		Allocator			   _alloc;
		std::allocator<T>		_alloc;
		pointer					_data;
	private:
		//* private methods
		template<typename iter> size_type
		dist(iter i1, iter i2, IS_ITERATOR(!is_input_iterator, iter) * = NULL){
			size_type i = 0;
			for(; i1 != i2; ++i1, ++i)
				;
			return i;
		}
		void	setterConstructor(difference_type Reserve = RESERVE_DEFAULT, difference_type UsedMem = 0, difference_type Hint = 0)
		{
			_uMem = UsedMem;
			_aMem = UsedMem;
			_reserve = Reserve;
			_cMem = Hint;

			if (_cMem < 0)
				throw std::out_of_range("vector");
			if (Hint > 0){
				_data = _alloc.allocate(_cMem);
				if (!_data)
					throw runtime_error(NO_MEM_SPACE);
			} else {
				_data = NULL;
			}
		}
		void	reallocate(size_type size, const_reference val = T()){
			Allocator 		newAlloc;
			pointer			newData;
			size_type		newUsedMem;
			size_type		newCMem;
			size_type		i;

			newCMem = max(size, _reserve);
			newUsedMem = min(_uMem, size); // 10 5

			if (!(newData = newAlloc.allocate(newCMem)))
				throw runtime_error(NO_MEM_SPACE);
			for(i = 0; i < newUsedMem; ++i)	//  _data[0...4]
				newAlloc.construct(&newData[i], _data[i]);
			for (; i < newCMem; i++) // newData[5...newHint]
				newAlloc.construct(&newData[i], val);			
			_alloc.deallocate(_data, _cMem);
			_alloc = newAlloc;
			_uMem = newUsedMem;
			_aMem = size;
			_cMem = newCMem;
			_data = newData;
		}

		void delete_data(){
			if (_data) {
				_alloc.deallocate(_data, _cMem);
				//_data = NULL;
				//_hint = 0;
			}
		}

		void new_data(size_type n){
			_cMem = max(n , _reserve);
			_data = _alloc.allocate(_cMem);
			if (!_data)
				throw runtime_error(NO_MEM_SPACE);
		}

		void copyFrom(ft::vector<T> const & oth){
			delete_data();
			_cMem =	oth._cMem;
			_uMem = oth._uMem;
			_aMem = oth._aMem;
			if (_aMem > 0){
				_data = _alloc.allocate(_cMem);
				for (size_type i = 0; i < _aMem; i++)
					_data[i] = oth._data[i];
			}
		}
		void	checkData(){if (!_data) throw std::out_of_range(EX_DEF_NULL);}
	public:
//* constructor's / destructor
		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			setterConstructor();
		}
		vector(ft::vector<T, Allocator> const & oth, const allocator_type& alloc = allocator_type())
			: _reserve(RESERVE_DEFAULT), _uMem(0), _cMem(0), _alloc(alloc), _data(NULL)
		{
			copyFrom(oth);
		}
		// * input_iterator constructor
		template <typename InputIterator>
		vector(InputIterator start, InputIterator finish, const allocator_type & alloc = allocator_type(),
			   IS_ITERATOR(is_input_iterator, InputIterator) * = NULL)
			   : _alloc(alloc){
			setterConstructor();
			for(; start != finish; ++start)
				push_back(*start);
		}
		// * some_iterators constructor
		template <typename _Iterator>
		vector(_Iterator start, _Iterator finish,
			   IS_ITERATOR(!is_input_iterator, _Iterator) * = NULL){
			size_type newCMem = dist(start, finish);
			setterConstructor(RESERVE_DEFAULT, 0, newCMem);
			for(; start != finish; ++start)
				push_back(*start);
		}

		vector(difference_type n, const_reference val){
			setterConstructor(RESERVE_DEFAULT, static_cast<ulong>(n), max(static_cast<ulong>(n << 1), static_cast<ulong>(RESERVE_DEFAULT)));
			for (difference_type i = 0; i < n; i++)
				_alloc.construct(&_data[i], val);
		}
		vector(difference_type n){
			setterConstructor(RESERVE_DEFAULT, 0, max(static_cast<ulong>(n << 1), static_cast<ulong>(RESERVE_DEFAULT)));
		}
		~vector(){_alloc.deallocate(_data, _cMem);}
//*	public methods
		inline difference_type	capacity()	const {return _cMem;}
		inline size_type		size()		const {return _aMem;}
		inline bool				empty()		const {return !_uMem || !_data;}
		difference_type			max_size()	const {return _alloc.max_size();}
		reference		operator [](difference_type i)			{return _data[i];}
		const_reference	operator [](difference_type i) const	{return _data[i];}
		inline void		clean()		{_uMem = 0;}
		reference		at(size_type i){
			if (i >= _uMem || i < 0 || !_data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		const_reference	at(size_type i) const {
			if (i >= _uMem || i < 0 || !_data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		void			push_back(const value_type &value){
			if (!_data){
				_cMem = _reserve;
				_aMem = _reserve;
				if (!(_data = _alloc.allocate(_cMem)))
					throw runtime_error(NO_MEM_SPACE);
				for (size_type i = 0; i < _cMem; i++)
					_alloc.construct(&_data[i], value);
			} else if (_uMem == _cMem){
				reallocate(_cMem << 1);
			}
			//std::cout << std::endl;
			//std::cout << typeid(value).name() << std::endl;
			//_data[_usedMem++] = value;
			_alloc.construct(&_data[_uMem++], value);
			_aMem = max(_aMem, _uMem);
		}
		void			swap(ft::vector<T> & oth){
			std::swap(_reserve, oth._reserve);
			std::swap(_alloc, oth._alloc);
			std::swap(_uMem, oth._uMem);
			std::swap(_aMem, oth._aMem);
			std::swap(_cMem, oth._cMem);
			std::swap(_data, oth._data);
		}
		// assign with input_iterator
		template <typename input_itertor>
		void assign(input_itertor start, input_itertor finish,
					IS_ITERATOR(is_input_iterator, input_itertor) * = NULL){
			std::cout << "input_iterator" << std::endl;
			_uMem = 0;
			for(;start != finish; ++start){
				push_back(*start);
			}
		}
		// assign with random_access_iterator
		template <typename _iter>
		void assign(_iter start, _iter finish,
					IS_ITERATOR(!is_input_iterator, _iter) * = NULL){
			size_type len = dist(start, finish);
			if (len > _cMem) {
				delete_data();
				new_data(len);
			}
			_uMem = 0;
			while(_uMem < len)
				_alloc.construct(&_data[_uMem++], *start++);
			_aMem = _uMem;
		}
		// assign with integer & T parameter
		void assign(size_type n, const_reference value)
		{
			if (n > _cMem){
				delete_data();
				new_data(n);
			}
			_uMem = 0;
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_data[_uMem++], value);
			_aMem = _uMem = n;
		}

		void	resize(size_t n, value_type val)
		{
			if (n > _alloc.max_size())
				throw runtime_error("vector: resize is much too");
			//else if (n < _cMem)
			//	for (size_t i = _uMem - 1; i < n; i++)
			//		push_back(val);
			else if (n == 0)
				clean();
			else if (n != _cMem){
				reallocate(n, val);
			}
		}

		void	resize(size_t n){
			value_type t{};
			resize(n, t);
		}

		void reserve(const size_type newSize){
			if (newSize > _cMem)
				reallocate(newSize);
			_reserve = newSize;
		}

		void	shrink_to_fit(){
			if (_uMem == _cMem)
				return ;
			reallocate(_uMem);
		}

		void	pop_back(){
			//delete _data[--_usedMem];
			--_uMem;
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
			pointer			_data;
			size_type		_usedMem;
			difference_type	_iter;
			int				_direction;
			const_iterator(pointer data, difference_type usedMem, difference_type currentIter, difference_type direction = 0)
					: _data(data), 
					_usedMem(usedMem), 
					_iter(currentIter), 
					_direction(direction) {}
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
			reference check_range(size_type num){
				if (not _data)
					throw runtime_error("vector: data is empty");
				if (num >= _usedMem || num < 0)
					return _data[_usedMem - 1];
				return _data[std::abs(_direction - static_cast<int>(num))];
			}
			const_reference check_range(size_type num) const {
				if (not _data)
					throw runtime_error("vector: data is empty");
				if (num >= _usedMem || num < 0)
					return _data[_usedMem - 1];
				return _data[std::abs(_direction - static_cast<int>(num))];
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
				const_iterator::_direction = oth._direction;
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
				:super(oth), super::_direction(_uMem - 1){}
			reference	operator*()		{return this->check_range(super::_iter);}
			pointer		operator->()	{return &this->check_range(super::_iter);}
			reference	&operator[](difference_type const num){return super::check_range(num);}
		};
// * begin and end
		reverse_iterator	rbegin(){return reverse_iterator(_data, _uMem, _uMem -1);}
		iterator			begin(){return iterator(_data, _uMem, 0);}
		reverse_iterator	rend(){return reverse_iterator(_data, _uMem, -1);}
		iterator			end(){return iterator(_data, _uMem, _uMem);}

		const_reverse_iterator	crbegin() const {return const_reverse_iterator(_data, _uMem, _uMem -1);}
		const_iterator			cbegin() const {return const_iterator(_data, _uMem, 0);}
		const_reverse_iterator	crend() const {return const_reverse_iterator(_data, _uMem, -1);}
		const_iterator			cend() const {return const_iterator(_data, _uMem, _uMem);}

		const_reference		front() const	{this->checkData(); return _data[0];}
		const_reference		back()	const	{this->checkData(); return _data[_uMem -1];}
		reference			front() 		{this->checkData(); return _data[0];}
		reference			back()			{this->checkData(); return _data[_uMem -1];}
	private:
		void	_insert(difference_type pos, const_reference value, difference_type count = 1){
			difference_type i;

			if (_uMem + count > _cMem)
				reallocate((_uMem + count) << 1);
			else
			{
				_uMem += count;
				_aMem += count;
			}
			for (i = _cMem -1; i >= pos ; --i)
				_alloc.construct(&_data[i + count], _data[i]);
			for (i = 0; i < count; i++)
				_alloc.construct(&_data[pos + i], value);
		}
	public:
		//template<typename iterator>
		iterator	insert(const_iterator pos, const_reference value){
			_insert(pos._iter, value);
			return pos;
		}
		iterator	insert(const_iterator pos, size_type count, value_type value){
			_insert(pos._iter, value, count);
			return pos;
		}
		template <class InputIterator>
    	iterator insert (const_iterator position, InputIterator first, InputIterator last, IS_NOT_NUM(InputIterator)* = 0){
			while (first != last)
				_insert(position._iter, *first++);
			return iterator(_data, _uMem, position._iter);
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
				return false;
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
