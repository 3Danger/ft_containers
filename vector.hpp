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

using std::runtime_error;
using std::allocator;
using std::max;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_data "exception: vector::iterator: data is not comparable!"
#define EX_DEF_NULL "exeption: trying deference NULL"

#define RESERVE_DEFAULT 10

#define IS_ITERATOR(IS_TYPE, THIS_TYPE)\
typename enable_if<IS_TYPE<typename THIS_TYPE::iterator_category>::value, THIS_TYPE >::type

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
		typedef unsigned long	difference_type;
		typedef difference_type	size_type;
	private:
		size_type			_reserve;
		size_type			_usedMem;
		size_type			_hint;
//		Allocator			   _alloc;
		std::allocator<T>		_alloc;
		pointer					_data;
	private:
		//* private methods
		void	setterConstructor(size_type Reserve = RESERVE_DEFAULT, size_type UsedMem = 0, size_type Hint = 0)
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
		void	reallocate(size_type size, const_reference val = T(), bool mod_2x = false){
			size_type		newSize;
			value_type *	tmpData;
			size_type		i;

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

		void new_data(size_type n){
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
				for (size_type i = 0; i < _usedMem; i++)
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
			size_type hint = std::distance(start, finish);
			setterConstructor(RESERVE_DEFAULT, 0, hint);
			for(; start != finish; ++start)
				push_back(*start);
		}

		vector(size_type n, const_reference val){
			setterConstructor(RESERVE_DEFAULT, static_cast<ulong>(n), max(static_cast<ulong>(n << 1), static_cast<ulong>(RESERVE_DEFAULT)));
			for (size_type i = 0; i < n; i++)
				_data[i] = val;
		}
		vector(size_type n){
			setterConstructor(RESERVE_DEFAULT, 0, max(static_cast<ulong>(n << 1), static_cast<ulong>(RESERVE_DEFAULT)));
		}
		~vector(){_alloc.deallocate(_data, _hint);}
//*	public methods
		inline size_type	capacity()	const {return _hint;}
		inline size_type	size()		const {return _usedMem;}
		inline bool			empty()		const {return !_usedMem || !_data;}
		size_type			max_size()	const {return _alloc.max_size();}
		reference		operator [](size_type i)		{return _data[i];}
		const_reference	operator [](size_type i) const	{return _data[i];}
		inline void		clean()		{_usedMem = 0;}
		reference		at(size_type i){
			if (i >= _usedMem || i < 0 || !_data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		const_reference	at(size_type i) const{
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
			size_type tmpReservedMinMem = oth._reserve;
			Allocator tmpAlloc = oth._alloc;
			size_type tmpHitPoint = oth._hint;
			size_type tmpUsedMem = oth._usedMem;
			pointer tmpData = oth._data;

			oth._reserve = _reserve;
			oth._hint = _hint;
			oth._usedMem = _usedMem;
			oth._alloc = _alloc;
			oth._data = _data;

			_reserve = tmpReservedMinMem;
			_hint = tmpHitPoint;
			_usedMem = tmpUsedMem;
			_alloc = tmpAlloc;
			_data = tmpData;
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
			size_type len = std::distance(start, finish);
			if (len > _hint) {
				delete_data();
				new_data(len);
			}
			_usedMem = 0;
			while(_usedMem < len)
				_data[_usedMem++] = *start++;
		}
		// assign with integer & T parameter
		void assign(size_type n, const_reference value){
			if (n > _hint){
				delete_data();
				new_data(n);
			}
			for (size_type i = 0; i < n; i++)
				_data[i] = value;
			_usedMem = n;
		}

		void	resize(size_type n, const_reference val){
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

		void reserve(const size_type & newSize){
			if (newSize > _hint)
				reallocate(newSize);
			_reserve = newSize;
		}

		void	shrink_to_fit(){
			if (_usedMem == _hint)
				return ;
			reallocate(_usedMem);
		}
		// * iterators
	public:
		class const_iterator {
		public:
			typedef size_type difference_type;
			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef const T *const_pointer;
			typedef const T &const_reference;
			typedef std::random_access_iterator_tag iterator_category;
		protected:
			friend class vector;

			pointer _data;
			long _usedMem;
			long _iter;

			const_iterator(pointer data, size_type usedMem, size_type currentIter)
					: _data(data), _usedMem(usedMem), _iter(currentIter) {}
		public:
			const_iterator(size_type num)
					: _data(NULL), _usedMem(0), _iter(num) {}
			const_iterator()
					: _data(NULL), _usedMem(0), _iter(0) {}

			const_iterator(const_iterator const &Iter)
					: _data(Iter._data), _usedMem(Iter._usedMem), _iter(Iter._iter) {}

		private:
			void compare(const_iterator const &oth) {
				if (oth._data != _data)
					throw runtime_error(NO_COMPARE_data);
			}

		public:
			const_pointer	operator->(){return &const_iterator::_data[const_iterator::_iter];}
			const_reference operator*() const{
				if (_iter >= _usedMem || _iter < 0)
					return _data[_usedMem - 1];
				return _data[_iter];
			}
			const_reference	operator[](size_type num){
				if (num < 0 || num >= _usedMem)
					return _data[_usedMem - 1];
				return _data[num];
			}

			bool operator< (const const_iterator &rhs) const { return _iter <	 rhs._iter; }
			bool operator==(const const_iterator &rhs) const { return _iter == rhs._iter; }
			bool operator!=(const const_iterator &rhs) const { return _iter != rhs._iter; }
			bool operator> (const const_iterator &rhs) const { return _iter >	 rhs._iter; }
			bool operator<=(const const_iterator &rhs) const { return _iter <= rhs._iter; }
			bool operator>=(const const_iterator &rhs) const { return _iter >= rhs._iter; }

			const_iterator operator--(int) {
				const_iterator tmp(*this);
				--_iter;
				return tmp;
			}

			const_iterator operator++(int) {
				const_iterator tmp(*this);
				++_iter;
				return tmp;
			}

			const_iterator &operator++() {
				_iter++;
				return *this;
			}

			const_iterator &operator--() {
				_iter--;
				return *this;
			}

			friend const_iterator operator-(const const_iterator & it1, const const_iterator & it2);
			friend const_iterator operator+(const const_iterator & it1, const const_iterator & it2);

			const_iterator &operator+=(size_type const num){_iter += num; return *this;}
			const_iterator &operator-=(size_type const num){_iter -= num; return *this;}
			const_iterator &operator=(const const_iterator &oth) {
				const_iterator::_usedMem = oth._usedMem;
				const_iterator::_iter = oth._iter;
				const_iterator::_data = oth._data;
				return *this;
			}

			const_iterator &operator+(const const_iterator & oth){return _iter + oth._iter;}
			const_iterator &operator-(const const_iterator & oth){return _iter - oth._iter;}
		};

		class iterator:public const_iterator{
			friend class ft::vector<T>;
			iterator(pointer data, size_type usedMem, size_type iter): const_iterator(data, usedMem, iter){}
		public:
			iterator(){}
			iterator(const_iterator const & oth): const_iterator(oth){}
			reference operator*() {
				if (const_iterator::_iter >= const_iterator::_usedMem || const_iterator::_iter < 0)
					return const_iterator::_data[_usedMem - 1];
				return const_iterator::_data[const_iterator::_iter];
			}
			pointer	operator->(){return &const_iterator::_data[const_iterator::_iter];}
			reference &operator[](size_type const num){
				if (num < 0) 
					throw std::out_of_range("iterator[]");
				return _data[const_iterator::_iter];		
			}
		};


		class reverse_iterator {
		public:
			typedef size_type difference_type;
			typedef T value_type;
			typedef T *pointer;
			typedef T &reference;
			typedef const T *const_pointer;
			typedef const T &const_reference;
			typedef std::random_access_iterator_tag iterator_category;
		protected:
			friend class vector;

			pointer _data;
			long _usedMem;
			long _iter;

			reverse_iterator(pointer data, size_type usedMem, size_type currentIter)
					: _data(data), _usedMem(usedMem), _iter(currentIter) {}
		public:
			reverse_iterator()
					: _data(NULL), _usedMem(0), _iter(0) {}

			reverse_iterator(reverse_iterator const &Iter)
					: _data(Iter._data), _usedMem(Iter._usedMem), _iter(Iter._iter) {}

		private:
			void compare(reverse_iterator const &oth) {
				if (oth._data != _data)
					throw runtime_error(NO_COMPARE_data);
			}

		public:
			reference operator*() {
				if (_iter >= _usedMem || _iter < 0)
					return _data[_usedMem - 1];
				return _data[_iter];
			}
			bool operator< (const reverse_iterator &rhs) const {return rhs._iter <  _iter;}
			bool operator==(const reverse_iterator &rhs) const {return rhs._iter == _iter;}
			bool operator!=(const reverse_iterator &rhs) const {return rhs._iter != _iter;}
			bool operator> (const reverse_iterator &rhs) const {return rhs._iter >  _iter;}
			bool operator<=(const reverse_iterator &rhs) const {return rhs._iter <= _iter;}
			bool operator>=(const reverse_iterator &rhs) const {return rhs._iter >= _iter;}
			reverse_iterator operator++() {_iter--; return *this;}
			reverse_iterator operator--() {_iter++; return *this;}
			reverse_iterator operator--(int) {reverse_iterator tmp(*this);++_iter; return tmp;}
			reverse_iterator operator++(int) {reverse_iterator tmp(*this);--_iter; return tmp;}
			size_type operator+(const reverse_iterator & oth){return oth._iter + _iter;}
			size_type operator-(const reverse_iterator & oth){return oth._iter - _iter;}
			template <typename integer> reverse_iterator
			operator+(typename enable_if<is_integer<integer>::value, integer >::type num) const {
				return reverse_iterator(_data, _usedMem, _iter + num);}
			template <typename integer> reverse_iterator
			operator-(typename enable_if<is_integer<integer>::value, integer >::type num) const {
				return reverse_iterator(_data, _usedMem, _iter - num);}
			reverse_iterator &operator=(const reverse_iterator &oth) {
				_usedMem = oth._usedMem;
				_iter = oth._iter;
				_data = oth._data;
				return *this;
			}
		};
// * begin and end
		reverse_iterator	rbegin(){return reverse_iterator(_data, _usedMem, _usedMem -1);}
		iterator			begin(){return iterator(_data, _usedMem, 0);}
		reverse_iterator	rend(){return reverse_iterator(_data, _usedMem, -1);}
		iterator			end(){return iterator(_data, _usedMem, _usedMem);}
		const_reference		front() const	{this->checkData(); return _data[0];}
		const_reference		back()	const	{this->checkData(); return _data[_usedMem -1];}
		reference			front() 		{this->checkData(); return _data[0];}
		reference			back()			{this->checkData(); return _data[_usedMem -1];}
	private:
		bool	_insert(size_type pos, const_reference value){
			if (_data && _usedMem < _hint){
				for (size_type i = _hint -1; i <= pos ; --i) {
					_data[i + 1] = _data[i];
				}
				_data[pos] = value;
				_usedMem++;
				return true;
			}
			return false;
		}
	public:
		iterator	insert(iterator & pos, const_reference value){
			if (!_data || !_usedMem)
				push_back(value);
			else if (!_insert(pos._iter, value)) {
				if (pos._iter >= _hint){
					push_back(value);
				}else{
					reallocate(_usedMem, NULL, true);
					for(size_type i = _hint - 1; i > pos._iter; --i) {
						_data[i + 1] = _data[i];
					}
					_data[pos->iter] = value;
					_usedMem++;
				}
			}
		}
	};
	template <typename V>
	struct reverse_iterator: public V{
		template<typename VI>
		reverse_iterator(VI const &oth_iter): V::V(oth_iter){}
	};
	//template <typename V>
	//class const_reverse_iterator: public V{};
};
#endif //CONTAINERYYY_VECTOR_H
