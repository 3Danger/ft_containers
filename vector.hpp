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
#include "vectorIterator.hpp"

using std::runtime_error;
using std::allocator;
using std::max;
using std::min;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_data "exception: vector::iterator: data is not comparable!"
#define EX_DEF_NULL "exeption: trying deference NULL"

#define RESERVE_DEFAULT 8

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
	public:
		typedef class ft::vIterator<T>		iterator;
		typedef class ft::cvIterator<T>		const_iterator;
		typedef class ft::rvIterator<T>		reverse_iterator;
		typedef class ft::crvIterator<T>	const_reverse_iterator;

		typedef Allocator			allocator_type;
		typedef	T					value_type;
		typedef	T &					reference;
		typedef	T *					pointer;
		typedef	T const &			const_reference;
		typedef	T const *			const_pointer;
		typedef ptrdiff_t			difference_type;
		typedef unsigned long		size_type;
	private:
		size_type				_reserve;
		size_type				_uMem;
		size_type				_cMem;
		// Allocator			_alloc;
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
			_reserve = Reserve;
			_cMem = max(Hint, Reserve);

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
		void	reallocate(size_type size){
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
			// _alloc.deallocate(_data, _cMem);
			delete_data();
			_alloc = newAlloc;
			_uMem = newUsedMem;
			_cMem = newCMem;
			_data = newData;
		}

		void delete_data(){
			if (_data) {
				for (size_t i = 0; i < _cMem; i++)
					_alloc.destroy(&_data[i]);
				_alloc.deallocate(_data, _cMem);
				_data = NULL;
				_uMem = 0;
				_cMem = 0;
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
			if (_uMem > 0){
				_data = _alloc.allocate(_cMem);
				for (size_type i = 0; i < _uMem; i++)
					_alloc.construct(&_data[i], oth._data[i]);
			}
		}
		void	checkData(){if (!_data) throw std::out_of_range(EX_DEF_NULL);}
	public:
//* constructor's / destructor
		explicit vector(const allocator_type& alloc = allocator_type())
			: _reserve(RESERVE_DEFAULT), _uMem(0),_cMem(0), _alloc(alloc), _data(NULL)
		{
			//setterConstructor();
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
			setterConstructor(RESERVE_DEFAULT, 0, newCMem << 1);
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
		~vector(){delete_data();}
//*	public methods
		inline difference_type	capacity()	const {return _cMem;}
		inline size_type			size()		const {return _uMem;}
		inline bool				empty()		const {return !_uMem || !_data;}
		difference_type			max_size()	const {return _alloc.max_size();}
		reference		operator [](difference_type i)			{return _data[i];}
		const_reference	operator [](difference_type i) const	{return _data[i];}
		inline void		clean()		{_uMem = 0;}
		reference		at(size_type i){
			if (i >= _uMem || i < 0 || !_data)
				throw std::out_of_range(std::string(
					"vector::_M_range_check: __n (which is ") + 
					std::to_string(i) + ") >= this->size() (which is " + 
					std::to_string(_uMem) + ")");
			return this->operator[](i);
		}
		const_reference	at(size_type i) const {
			if (i >= _uMem || i < 0 || !_data)
				throw std::out_of_range(std::string(
					"vector::_M_range_check: __n (which is ") + 
					std::to_string(i) + ") >= this->size() (which is " + 
					std::to_string(_uMem) + ")");
			return this->operator[](i);
		}
		void			push_back(const value_type &value){
			if (!_data){
				_cMem = _reserve;
				if (!(_data = _alloc.allocate(_cMem)))
					throw runtime_error(NO_MEM_SPACE);
			} else if (_uMem == _cMem)
				reallocate(_cMem << 1);
			_alloc.construct(&_data[_uMem++], value);
		}
		void			swap(ft::vector<T> & oth){
			std::swap(_reserve, oth._reserve);
			std::swap(_alloc, oth._alloc);
			std::swap(_uMem, oth._uMem);
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
		}
		// assign with integer & T parameter
		void assign(size_type n, const_reference value)
		{
			delete_data();
			new_data(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_data[_uMem++], value);
		}

		void	resize(size_t n, value_type val)
		{
			if (n > _alloc.max_size())
				throw runtime_error("vector: resize is much too");
			else if (n == 0)
				clean();
			else if (n != _cMem){
				reallocate(n);
				while (_uMem < n)
					_alloc.construct(_data + _uMem++, val);
				
			}
		}

		void	resize(size_t n){
			value_type t{};
			resize(n, t);
		}

		void reserve(const size_type newSize){
			if (newSize >= _cMem)
				reallocate(newSize + 1);
			_reserve = newSize;
		}

		void	shrink_to_fit(){
			if (_uMem == _cMem)
				return ;
			reallocate(_uMem + 1);
		}

		void	pop_back(){
			//delete _data[--_usedMem];
			--_uMem;
		}
// * begin and end
		iterator			 end(void)			{return (iterator(_data + _uMem));};
		const_iterator		 cend(void) const	{return (const_iterator(_data + _uMem));};
		iterator			 begin(void)		{return (iterator(_data));};
		const_iterator		 cbegin(void) const	{return (const_iterator(_data));};
		reverse_iterator		 rend(void)				{return (reverse_iterator(_data - 1));};
		const_reverse_iterator	 crend(void) const		{return (const_reverse_iterator(_data - 1));};
		reverse_iterator		 rbegin(void)			{return (reverse_iterator(_data + _uMem - 1));};
		const_reverse_iterator	 crbegin(void) const	{return (const_reverse_iterator(_data + _uMem - 1));};

		const_reference		front() const	{this->checkData(); return _data[0];}
		const_reference		back()	const	{this->checkData(); return _data[_uMem -1];}
		reference			front() 		{this->checkData(); return _data[0];}
		reference			back()			{this->checkData(); return _data[_uMem -1];}
	private:
		void	_insert(size_type pos, const_reference value, size_type count = 1){
			if (_cMem < _uMem + count)	// если памяти не достаточно, то расширяю память
				reallocate((_cMem + count) << 1); // ! Можно оптимизировать потом
			if (pos > _uMem)
				throw std::out_of_range\
					(std::string("_insert, выход за пределы массива POS ")
					 	+ std::to_string(pos));
			for (size_type i = _uMem - 1; i >= pos; --i)
				_alloc.construct(&_data[i + count], _data[i]);
			for (size_type i = pos; i < pos + count; ++i)
				_alloc.construct(&_data[i], value);
			_uMem += count;
		}
	public:
		//template<typename iterator>
		iterator	insert(iterator pos, const_reference value){
			_insert(&*pos -_data, value);
			return pos;
		}
		iterator	insert(iterator pos, size_type count, value_type value){
			_insert(&*pos - _data, value, count);
			return pos;
		}
		template <class InputIterator>
    	iterator insert (iterator position, InputIterator first, InputIterator last, IS_NOT_NUM(InputIterator)* = 0){
			size_type pos, tpos;

			tpos = pos = &*position - _data;
			for (;first != last; ++pos, ++first)
				_insert(pos, *first);
			return iterator(_data + tpos);
		}

		iterator erase(iterator first)
		{
			size_type index;
			std::allocator<int> alloc;
			
			// delete _data[index];
			index = &*first - _data;
			if (index >= _uMem)
				throw std::runtime_error(EX_DEF_NULL);
			--_uMem;
			for(size_type i = index; i < _uMem; ++i)
				_alloc.construct(&_data[i], _data[i + 1]);
			_alloc.destroy(&_data[_uMem]);
			return iterator(_data);
		}

		void	clear(){
			if (_data)
			{
				for (size_type i = 0; i < _uMem; i++)
					_alloc.destroy(&_data[i]);
				_alloc.deallocate(_data, _cMem);
			}
			_data = NULL;
			_cMem = 0;
			_uMem = 0;
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

			while(thisBegin != thisEnd && othBegin != othEnd && *thisBegin <= *othBegin){
				++thisBegin;
				++othBegin;
			}
			if (thisBegin == thisEnd && othBegin == othEnd)
				return false;
			else if (thisBegin == thisEnd)
				return true;
			else if (othBegin == othEnd)	//! оптимизация
				return false;
			return *thisBegin > *othBegin;;
		}
		bool operator >= (vector<T, Allocator> const & v1) const {
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
			return *thisBegin >= *othBegin;
		}
		bool operator <= (vector<T, Allocator> const & v1) const {
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
				return true;
			else if (othBegin == othEnd)
				return false;
			return *thisBegin > *othBegin;;
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
				return false;
			return false;
		}
		bool operator != (vector<T, Allocator> const & v1) const {return !operator==(v1);}
	};
};
#endif //CONTAINERYYY_VECTOR_H
