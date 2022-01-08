#include <iostream>
#include <memory>
#include <string>
using std::runtime_error;
using std::allocator;
using std::max;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_DATA "exception: vector::iterator: data is not comparable!"


#define IS_NEED_DOWN_REALLOC( Hint, UsedMem ) ( (Hint - UsedMem) > (UsedMem + (UsedMem >> 2)) )

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
		void	setterConstructor(
			ptrdiff_t Reserve = 10, 
			ptrdiff_t UsedMem = 0, 
			ptrdiff_t Hint = 0)
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
	public:
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
		void	push_back(const value_type & value){
			pointer			tmpData;
			Allocator		tmpAlloc;

			if (!_Data){
				_Hint = _Reserve;
				_Data = _Alloc.allocate(_Hint);
				if (!_Data)
					throw runtime_error(NO_MEM_SPACE);
			} else if (_UsedMem == _Hint){
				tmpData = tmpAlloc.allocate(_Hint << 1);
				if (!tmpData)
					throw runtime_error(NO_MEM_SPACE);
				for (ptrdiff_t i = 0; i < _UsedMem; i++)
					tmpData[i] = _Data[i];
				_Alloc.deallocate(_Data, _Hint);
				_Alloc = Allocator(tmpAlloc);
				_Hint = _Hint << 1;
				_Data = tmpData;
			}
			_Data[_UsedMem++] = value;
		}
		reference at(ptrdiff_t i){
			if (i >= _UsedMem)
				throw runtime_error("exception: vector: out of range");
			return _Data[i];
		}
		reference operator [](ptrdiff_t i){return _Data[i];}
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
		void 	assign(ptrdiff_t n, const_reference value){
			if (n > _Hint){
				_Hint = n << 1;
				_Alloc.deallocate(_Data, _Hint);
				_Data = _Alloc.allocate(_Hint);
				if (!_Data)
					throw runtime_error(NO_MEM_SPACE);
			}
			for (ptrdiff_t i = 0; i < n; i++)
				_Data[i] = value;
			_UsedMem = n;
		}
		template<class iterator>
		void	assign(iterator start, iterator finish){
			std::allocator<T> tmpAlloc;
			// Allocator	tmpAlloc;
			pointer		tmpData;
			while(start != finish)
				push_back(*start++);
			if (IS_NEED_DOWN_REALLOC(_Hint, _UsedMem)){
				//	!!!			!!!				!!!!					!!!!!								!!!!!§
				tmpData = tmpAlloc.allocate(_UsedMem << 1);
				for (size_t i = 0; i < _UsedMem; i++)
					tmpData[i] = _Data[i];
				_Alloc.deallocate(_Data, _Hint);
				_Data = tmpData;
				_Alloc(tmpAlloc);
			}
		}
		size_t size() const {return _UsedMem;}
		void	reserve(ptrdiff_t n){_Reserve = n;} // ?
		void	resize(ptrdiff_t n, const_reference val = T()){
			if (n < 1)
				throw runtime_error("э, пошол отсюда!!! что за ресайз??");
			if (_UsedMem > n)
				_UsedMem = n;
			value_type * tmpData = _Alloc.allocate(max(n << 1, _Reserve));
			if (!tmpData)
				throw runtime_error(NO_MEM_SPACE);
			for (ssize_t i = _UsedMem - 1; i >= 0; i--)
				tmpData[i] = _Data[i];
			for (ssize_t i = n - 1; i >= _UsedMem - 1; i--)
				tmpData[i] = val;
			_Alloc.deallocate(_Data, _Hint);
			_Hint = max(n << 1, _Reserve);
			_Data = tmpData;
		}
	private:
		void copyFrom(ft::vector<T> const & oth){
			if (_Data){
				_Alloc.deallocate(_Data, _Hint);
				_Data = NULL;
			}
			_Hint = oth._Hint;
			_UsedMem = oth._UsedMem;
			if (_UsedMem > 0){
				_Data = _Alloc.allocate(_Hint);
				for (ptrdiff_t i = 0; i < _UsedMem; i++)
					_Data[i] = oth._Data[i];
			}
		}
	// * iterators
	private:
		class iterator_base{
		public:
			typedef	T			value_type;
			typedef	T&			reference;
			// typedef	const T&	const_reference;
			typedef	T*			pointer;
			// typedef	const T*	const_pointer;
		private:
			friend class vector;
			pointer		_Data;
			ptrdiff_t	const _UsedMem;
			ptrdiff_t	_Iter;
			iterator_base(pointer data, ptrdiff_t usedMem, ptrdiff_t currentIter)
				: _Data(data), _UsedMem(usedMem), _Iter(currentIter){}
		public:
			iterator_base()
				: _Data(NULL), _UsedMem(0), _Iter(0){}
			iterator_base(iterator_base const & iter)
				: _Data(iter._Data)
				, _UsedMem(iter._UsedMem)
				, _Iter(iter._Iter){}
			virtual ~iterator_base(){}
			reference operator*(){
				if (_Iter >= _UsedMem || _Iter < 0)
					return _Data[_UsedMem - 1];
				return _Data[_Iter];}
		// * bool operator
		private:
			void	compare(iterator_base const & oth){
				if (oth._Data != _Data)
					throw runtime_error(NO_COMPARE_DATA);
			}
		public:
			bool operator>	(iterator_base const & oth){compare(oth); return _Iter >  oth._Iter;}
			bool operator>=	(iterator_base const & oth){compare(oth); return _Iter >= oth._Iter;}
			bool operator<	(iterator_base const & oth){compare(oth); return _Iter <  oth._Iter;}
			bool operator<=	(iterator_base const & oth){compare(oth); return _Iter <= oth._Iter;}
			bool operator==	(iterator_base const & oth){compare(oth); return _Iter == oth._Iter;}
			bool operator!=	(iterator_base const & oth){compare(oth); return _Iter != oth._Iter;}
		};

		public:
		class iterator: public iterator_base{
		public:
			iterator(): iterator_base(){}
			iterator(pointer data, ptrdiff_t usedMem, ptrdiff_t iter): iterator_base(data, usedMem, iter){};
			iterator operator++(void){ ++iterator::_Iter; return *this;}
			iterator operator--(void){ --iterator::_Iter; return *this;}
			iterator operator--(int){
				iterator tmp(*this);
				iterator_base::_Iter--;
				return tmp;
			}
			iterator operator++(int){
				iterator tmp(*this);
				iterator_base::_Iter++;
				return tmp;
			}
		};

		class reverse_iterator: public iterator_base{
		public:
			reverse_iterator(): iterator_base(){}
			reverse_iterator(pointer data, ptrdiff_t usedMem, ptrdiff_t iter): iterator_base(data, usedMem, iter){};
			reverse_iterator operator++(void){ --iterator::_Iter; return *this;}
			reverse_iterator operator--(void){ ++iterator::_Iter; return *this;}
			reverse_iterator operator--(int){
				reverse_iterator tmp(*this);
				iterator_base::_Iter++;
				return tmp;
			}
			reverse_iterator operator++(int){
				reverse_iterator tmp(*this);
				iterator_base::_Iter--;
				return tmp;
			}
		};

	// * begin and end
	reverse_iterator	rbegin(){return reverse_iterator(_Data, _UsedMem, _UsedMem -1);}
	iterator			begin(){return iterator(_Data, _UsedMem, 0);}
	reverse_iterator	rend(){return reverse_iterator(_Data, _UsedMem, -1);}
	iterator			end(){return iterator(_Data, _UsedMem, _UsedMem);}
	};
};