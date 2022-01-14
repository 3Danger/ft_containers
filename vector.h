//
// Created by Rasul on 12.01.2022.
//

#ifndef CONTAINERYYY_VECTOR_H
#define CONTAINERYYY_VECTOR_H

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

using std::runtime_error;
using std::allocator;
using std::max;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_data "exception: vector::iterator: data is not comparable!"
#define EX_DEF_NULL "exeption: trying deference NULL"

#define IS_NEED_DOWN_REALLOC( Hint, UsedMem ) \
( (Hint - UsedMem) > (UsedMem + (UsedMem >> 2)) )

//* ENABLE IF
template <bool, typename T>
struct _enable_if{};
template <typename T>
struct _enable_if<true, T>{typedef T type;};




// * FT NAMESPACE
namespace ft{
    template <class T, class Allocator = std::allocator<T> >
    class vector{
//        friend class		iterator;
//        friend class		reverse_iterator;
    public:
        typedef Allocator	allocator_type;
        typedef	const T&	const_reference;
        typedef	const T*	const_pointer;
        typedef	T			value_type;
        typedef	T&			reference;
        typedef	T*			pointer;
    private:
        unsigned long			_reserve;
        unsigned long			_usedMem;
        unsigned long			_hint;
//        Allocator               _alloc;
		std::allocator<T>		_alloc;
        pointer			        _data;
    private:
        //* private methods
        void	setterConstructor(unsigned long Reserve = 10, unsigned long UsedMem = 0, unsigned long Hint = 0)
        {
            _usedMem = UsedMem;
            _reserve = Reserve;
            _hint = Hint;
            if (Hint > 0){
                _data = _alloc.allocate(_hint);
                if (!_data)
                    throw runtime_error(NO_MEM_SPACE);
            } else
                _data = NULL;
        }
        void	reallocate(unsigned long size, const_reference val = T(), bool mod_2x = false){
            unsigned long		newSize = size;
            value_type *	tmpData;

            if (mod_2x)
                newSize <<= 1;
            tmpData = _alloc.allocate(max(newSize, _reserve));
            if (!tmpData)
                throw runtime_error(NO_MEM_SPACE);
            if (_usedMem > size)
                _usedMem = size;
            for (ssize_t i = _usedMem - 1; i >= 0; i--)
                tmpData[i] = _data[i];
            for (ssize_t i = max(size, _reserve) - 1; i >= _usedMem; i--)
                tmpData[i] = val;
            _alloc.deallocate(_data, _hint);
            _data = tmpData;
            _hint = newSize;
        }
        void copyFrom(ft::vector<T> const & oth){
            if (_data){
                _alloc.deallocate(_data, _hint);
                _data = NULL;
            }
            _hint =	oth._hint;
            _usedMem = oth._usedMem;
            if (_usedMem > 0){
                _data = _alloc.allocate(_hint);
                for (unsigned long i = 0; i < _usedMem; i++)
                    _data[i] = oth._data[i];
            }
        }
		void	checkData(){if (!_data) throw runtime_error(EX_DEF_NULL);}
    public:
//* constructor's / destructor
        vector(){setterConstructor();}
        vector(ft::vector<T, Allocator> const & oth){
			setterConstructor();
            copyFrom(oth);
        }
		template <typename InputIterator>
		vector(InputIterator start, InputIterator finish, typename InputIterator::iterator_category * = NULL){
//            setterConstructor(10, size, max(size << 1, _reserve));
			setterConstructor();
			for(; start != finish; ++start)
				push_back(*start);
        }
        explicit vector(unsigned long size, value_type const & val = value_type()): _reserve(10){
            setterConstructor(10, size, max(size << 1, _reserve));
            for (unsigned long i = 0; i < size; i++)
                _data[i] = val;
        }
        ~vector(){_alloc.deallocate(_data, _hint);}
//*	public methods
        inline size_t	capacity()	const {return _hint;}
        inline size_t	size()		const {return _usedMem;}
        reference		operator [](unsigned long i)		{return _data[i];}
        const_reference	operator [](unsigned long i) const	{return _data[i];}
        inline void		clean()		{_usedMem = 0;}
        reference		at(unsigned long i){
            if (i >= _usedMem || i < 0 || !_data)
                throw std::out_of_range("vector");
            return this->operator[](i);
        }
        const_reference	at(unsigned long i) const{
            if (i >= _usedMem || i < 0 || !_data)
                throw std::out_of_range("vector");
            return this->operator[](i);
        }
        void	push_back(const value_type & value){
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
        void	swap(ft::vector<T> & oth){
            unsigned long tmpReservedMinMem = oth._reserve;
            Allocator tmpAlloc = oth._alloc;
            unsigned long tmpHitPoint = oth._hint;
            unsigned long tmpUsedMem = oth._usedMem;
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
//		typename _enable_if<std::__is_input_iterator<InputIterator>::value, void>::type *
		template <typename InputIterator>
		void assign(InputIterator start, InputIterator finish, typename InputIterator::iterator_category * = NULL){
			for(;start != finish; ++start){
				push_back(*start);
			}
		}
        void assign(unsigned long n, value_type value){
            if (n > _hint){
                if (_data)
                    _alloc.deallocate(_data, _hint);
                _hint = max(n , _reserve);
                _data = _alloc.allocate(_hint);
                if (!_data)
                    throw runtime_error(NO_MEM_SPACE);
            }
            for (unsigned long i = 0; i < n; i++)
                _data[i] = value;
            _usedMem = n;
        }
        void	reserve(unsigned long n){
            if (n > _reserve){
                _reserve = n;
                return ;
            }
            _reserve = n;
            reallocate(n);
        }
        void	resize(unsigned long n, const_reference val = T()){
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
        void	shrink_to_fit(){
            if (_usedMem == _hint)
                return ;
            reallocate(_usedMem);
        }
        // * iterators
	public:
        class iterator {
		public:
			typedef unsigned long difference_type;
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

			iterator(pointer data, unsigned long usedMem, unsigned long currentIter)
					: _data(data), _usedMem(usedMem), _iter(currentIter) {}

		public:
			iterator()
					: _data(NULL), _usedMem(0), _iter(0) {}

			iterator(iterator const &Iter)
					: _data(Iter._data), _usedMem(Iter._usedMem), _iter(Iter._iter) {}

		private:
			void compare(iterator const &oth) {
				if (oth._data != _data)
					throw runtime_error(NO_COMPARE_data);
			}

		public:
			reference operator*() {
				if (_iter >= _usedMem || _iter < 0)
					return _data[_usedMem - 1];
				return _data[_iter];
			}

			bool operator<(const iterator &rhs) const { return _iter < rhs._iter; }

			bool operator==(const iterator &rhs) const { return _iter == rhs._iter; }

			bool operator!=(const iterator &rhs) const { return !(*this == rhs); }

			bool operator>(const iterator &rhs) const { return rhs < *this; }

			bool operator<=(const iterator &rhs) const { return !(rhs < *this); }

			bool operator>=(const iterator &rhs) const { return !(*this < rhs); }

			iterator operator--(int) {
				iterator tmp(*this);
				--(*this);
				return tmp;
			}

			iterator operator++(int) {
				iterator tmp(*this);
				++(*this);
				return tmp;
			}

			iterator &operator++() {
				_iter++;
				return *this;
			}

			iterator &operator--() {
				_iter--;
				return *this;
			}

			iterator &operator=(const iterator &oth) {
				_usedMem = oth._usedMem;
				_iter = oth._iter;
				_data = oth._data;
				return *this;
			}
		};
		class reverse_iterator {
		public:
			typedef unsigned long difference_type;
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

			reverse_iterator(pointer data, unsigned long usedMem, unsigned long currentIter)
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
			bool operator<(const reverse_iterator &rhs) const {
				return rhs._iter < _iter;
			}
			bool operator==(const reverse_iterator &rhs) const {
				return rhs._iter == _iter;
			}
			bool operator!=(const reverse_iterator &rhs) const {
				return rhs._iter != _iter;
			}
			bool operator>(const reverse_iterator &rhs) const {
				return rhs._iter > _iter;
			}
			bool operator<=(const reverse_iterator &rhs) const {
				return rhs._iter <= _iter;
			}
			bool operator>=(const reverse_iterator &rhs) const {
				return rhs._iter >= _iter;
			}
			reverse_iterator &operator++() {
				_iter--;
				return *this;
			}

			reverse_iterator &operator--() {
				_iter++;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp(*this);
				--(*this);
				return tmp;
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp(*this);
				++(*this);
				return tmp;
			}

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
    };
};

#endif //CONTAINERYYY_VECTOR_H
