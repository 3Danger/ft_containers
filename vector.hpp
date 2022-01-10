#include <iostream>
#include <memory>
#include <string>
using std::runtime_error;
using std::allocator;
using std::max;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_DATA "exception: vector::iterator: data is not comparable!"
#define EX_DEF_NULL "exeption: trying deference NULL"


#define IS_NEED_DOWN_REALLOC( Hint, UsedMem ) \
( (Hint - UsedMem) > (UsedMem + (UsedMem >> 2)) )

namespace ft{
	template <class T, class Allocator = std::allocator<T> >
	class vector{
		friend class		iterator;
	public:
		typedef Allocator	allocator_type;
		typedef	const T&	const_reference;
		typedef	const T*	const_pointer;
		typedef	T			value_type;
		typedef	T&			reference;
		typedef	T*			pointer;
	private:
		ptrdiff_t			_Reserve;
		ptrdiff_t			_UsedMem;
		ptrdiff_t			_Hint;
		Allocator			_Alloc;
		pointer				_Data;
	private:
		//* private methods
		void	setterConstructor(ptrdiff_t Reserve = 10, ptrdiff_t UsedMem = 0, ptrdiff_t Hint = 0)
		{
			_UsedMem = UsedMem;
			_Reserve = Reserve;
			_Hint = Hint;
			if (Hint > 0){
				_Data = _Alloc.allocate(_Hint);
				if (!_Data)
					throw runtime_error(NO_MEM_SPACE);
			} else
				_Data = NULL;
		}
		void	reallocate(ptrdiff_t size, const_reference val = T(), bool mod_2x = false){
			ptrdiff_t		newSize = size;
			value_type *	tmpData;

			if (mod_2x)
				newSize <<= 1;
			tmpData = _Alloc.allocate(max(newSize, _Reserve));
			if (!tmpData)
				throw runtime_error(NO_MEM_SPACE);
			if (_UsedMem > size)
				_UsedMem = size;
			for (ssize_t i = _UsedMem - 1; i >= 0; i--)
				tmpData[i] = _Data[i];
			for (ssize_t i = max(size, _Reserve) - 1; i >= _UsedMem; i--)
				tmpData[i] = val;
			_Alloc.deallocate(_Data, _Hint);
			_Data = tmpData;
			_Hint = newSize;
		}
		void copyFrom(ft::vector<T> const & oth){
			if (_Data){
				_Alloc.deallocate(_Data, _Hint);
				_Data = NULL;
			}
			_Hint =	oth._Hint;
			_UsedMem = oth._UsedMem;
			if (_UsedMem > 0){
				_Data = _Alloc.allocate(_Hint);
				for (ptrdiff_t i = 0; i < _UsedMem; i++)
					_Data[i] = oth._Data[i];
			}
		}
	public:
//* constructor's / destructor
		vector(){
			setterConstructor();
		}
		vector(ft::vector<T> const & oth){
			setterConstructor();
			copyFrom(oth);
		}
		vector(ptrdiff_t size, value_type const & val = value_type()){
			setterConstructor(10, size, max(size << 1, _Reserve));
			for (ptrdiff_t i = 0; i < size; i++)
				_Data[i] = val;
		}
		~vector(){_Alloc.deallocate(_Data, _Hint);}
//*	public methods
		inline size_t	capacity()	const {return _Hint;}
		inline size_t	size()		const {return _UsedMem;}
		reference		operator [](ptrdiff_t i)		{return _Data[i];}
		const_reference	operator [](ptrdiff_t i) const	{return _Data[i];}
		inline void		clean()		{_UsedMem = 0;}
		reference		at(ptrdiff_t i){
			if (i >= _UsedMem || i < 0 || !_Data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		const_reference	at(ptrdiff_t i) const{
			if (i >= _UsedMem || i < 0 || !_Data)
				throw std::out_of_range("vector");
			return this->operator[](i);
		}
		void	push_back(const value_type & value){
			if (!_Data){
				_Hint = _Reserve;
				_Data = _Alloc.allocate(_Hint);
				if (!_Data)
					throw runtime_error(NO_MEM_SPACE);
			} else if (_UsedMem == _Hint){
				reallocate(_Hint, T(), true);
			}
			_Data[_UsedMem++] = value;
		}
		void	swap(ft::vector<T> & oth){
			ptrdiff_t tmpReservedMinMem = oth._Reserve;
			Allocator tmpAlloc = oth._Alloc;
			ptrdiff_t tmpHitPoint = oth._Hint;
			ptrdiff_t tmpUsedMem = oth._UsedMem;
			pointer tmpData = oth._Data;

			oth._Reserve = _Reserve;
			oth._Hint = _Hint;
			oth._UsedMem = _UsedMem;
			oth._Alloc = _Alloc;
			oth._Data = _Data;

			_Reserve = tmpReservedMinMem;
			_Hint = tmpHitPoint;
			_UsedMem = tmpUsedMem;
			_Alloc = tmpAlloc;
			_Data = tmpData;
		}
		// template <class InputIterator>
		// typename std::enable_if<std::__is_input_iterator<InputIterator>::value, InputIterator>::type
		// void	assign(InputIterator start, InputIterator finish){
		// 	_Alloc.deallocate(_Data, _Hint);
		// 	_Hint = max(n, _Reserve);
		// 	_Data = _Alloc.allocate(_Hint);
		// 	if (!_Data)
		// 		throw runtime_error(NO_MEM_SPACE);
		// 	while(start != finish){
		// 		push_back(*start++);
		// 	}
		// }
		//template<typename U, typename std::enable_if<std::is_integral<typename U::value, U>::type, U> >
		//void 	assign(U n, const_reference value){
		//	if (n > _Hint){
		//		_Alloc.deallocate(_Data, _Hint);
		//		_Hint = max(n , _Reserve);
		//		_Data = _Alloc.allocate(_Hint);
		//		if (!_Data)
		//			throw runtime_error(NO_MEM_SPACE);
		//	}
		//	for (ptrdiff_t i = 0; i < n; i++)
		//		_Data[i] = value;
		//	_UsedMem = n;
		//}
		void	reserve(ptrdiff_t n){
			if (n > _Reserve){
				_Reserve = n;
				return ;
			}
			_Reserve = n;
			reallocate(n);
		}
		void	resize(ptrdiff_t n, const_reference val = T()){
			if (n < 0)
				throw runtime_error("э, пошол отсюда!!! что за ресайз??");
			else if (n == 0){
				clean();
				return ;
			}
			else if (_UsedMem > n)
				_UsedMem = n;
			reallocate(n, val);
		}
		void	shrink_to_fit(){
			if (_UsedMem == _Hint)
				return ;
			reallocate(_UsedMem);
		}
	// * iterators
	private:
		class iterator_base{
		public:
			typedef ptrdiff_t	difference_type;
			typedef	T			value_type;
			typedef	T*			pointer;
			typedef	T&			reference;
			typedef	const T*	const_pointer;
			typedef	const T&	const_reference;
			typedef std::random_access_iterator_tag iterator_category;
		protected:
			friend class vector;
			friend class iterator;
			friend class reverse_iterator;
			pointer		_Data;
			ptrdiff_t	_UsedMem;
			ptrdiff_t	_Iter;
			int			_DirectionMove;
			iterator_base(pointer data, ptrdiff_t usedMem, ptrdiff_t currentIter, int dirMov)
				: _Data(data), _UsedMem(usedMem), _Iter(currentIter), _DirectionMove(dirMov){}
		public:
			iterator_base()
				: _Data(NULL), _UsedMem(0), _Iter(0){}
			iterator_base(iterator_base const & Iter)
				: _Data(Iter._Data)
				, _UsedMem(Iter._UsedMem)
				, _Iter(Iter._Iter)
				, _DirectionMove(Iter._DirectionMove){}
			virtual ~iterator_base(){}
			reference operator*(){
				if (_Iter >= _UsedMem || _Iter < 0)
					return _Data[_UsedMem - 1];
				return _Data[_Iter];}
		private:
			void	compare(iterator_base const & oth){
				if (oth._Data != _Data)
					throw runtime_error(NO_COMPARE_DATA);
			}
		public:
			iterator_base operator++(void){ _Iter += _DirectionMove; return *this;}
			iterator_base operator--(void){ _Iter -= _DirectionMove; return *this;}
			iterator_base operator--(int){ iterator_base tmp(*this); --(*this); return tmp;}
			iterator_base operator++(int){ iterator_base tmp(*this); ++(*this); return tmp;}
			iterator_base operator=(const iterator_base & oth){
				_DirectionMove = oth._DirectionMove;
				_UsedMem = oth._UsedMem;
				_Iter = oth._Iter;
				_Data = oth._Data;
				return *this;
			}

			bool operator>	(iterator_base const & oth){compare(oth); return _DirectionMove * _Iter >  _DirectionMove * oth._Iter;}
			bool operator<	(iterator_base const & oth){compare(oth); return _DirectionMove * _Iter <  _DirectionMove * oth._Iter;}
			bool operator==	(iterator_base const & oth){compare(oth); return _Iter == oth._Iter;}
			bool operator!=	(iterator_base const & oth){return !operator==(oth);}
			bool operator>=	(iterator_base const & oth){return !operator<(oth);}
			bool operator<=	(iterator_base const & oth){return !operator>(oth);}

			iterator_base	operator-(const iterator_base & oth) const {return iterator_base(_Data, _UsedMem, _Iter - (_DirectionMove * oth._Iter), _DirectionMove);}
			iterator_base	operator+(const iterator_base & oth) const {return iterator_base(_Data, _UsedMem, _Iter + (_DirectionMove * oth._Iter), _DirectionMove);}
			iterator_base	operator-(const ptrdiff_t value) const {return iterator_base(_Data, _UsedMem, _Iter - (_DirectionMove * value), _DirectionMove);}
			iterator_base	operator+(const ptrdiff_t value) const {return iterator_base(_Data, _UsedMem, _Iter + (_DirectionMove * value), _DirectionMove);}
			iterator_base	operator-=(const ptrdiff_t value) {_Iter -= (_DirectionMove * value); return *this;}
			iterator_base	operator+=(const ptrdiff_t value) {_Iter += (_DirectionMove * value); return *this;}
		};

	public:
		class iterator: public iterator_base{
		public:
			iterator(): iterator_base(){}
			iterator(pointer data, ptrdiff_t usedMem, ptrdiff_t iter): iterator_base(data, usedMem, iter, 1){};
			iterator(const iterator_base & oth): iterator_base(oth._Data, oth._UsedMem, oth._Iter, oth._DirectionMove){}
		};

		class reverse_iterator: public iterator_base{
		public:
			reverse_iterator(): iterator_base(){}
			reverse_iterator(pointer data, ptrdiff_t usedMem, ptrdiff_t iter): iterator_base(data, usedMem, iter, -1){};
			reverse_iterator(const iterator_base & oth): iterator_base(oth._Data, oth._UsedMem, oth._Iter, oth._DirectionMove){}
			bool operator>	(reverse_iterator const & oth){ return !iterator_base::operator>=(oth);};
			bool operator<	(reverse_iterator const & oth){ return !iterator_base::operator<=(oth);};
			bool operator>=	(reverse_iterator const & oth){ return !operator<(oth);};
			bool operator<=	(reverse_iterator const & oth){ return !operator>(oth);};
		};

// * begin and end
	reverse_iterator	rbegin(){return reverse_iterator(_Data, _UsedMem, _UsedMem -1);}
	iterator			begin(){return iterator(_Data, _UsedMem, 0);}
	reverse_iterator	rend(){return reverse_iterator(_Data, _UsedMem, -1);}
	iterator			end(){return iterator(_Data, _UsedMem, _UsedMem);}

	const_reference		front() const	{
		if (!_Data)
			throw runtime_error(EX_DEF_NULL);
		return _Data[0];
	}
	const_reference		back()	const	{
		if (!_Data)
			throw runtime_error(EX_DEF_NULL);
		return _Data[_UsedMem -1];
	}
	reference			front() 		{
		if (!_Data)
			throw runtime_error(EX_DEF_NULL);
		return _Data[0];
	}
	reference			back()			{
		if (!_Data)
			throw runtime_error(EX_DEF_NULL);
		return _Data[_UsedMem -1];
	}
	};
};