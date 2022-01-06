#include <memory>
#include <string>
using std::runtime_error;
using std::allocator;
using std::max;
#define NO_MEM_SPACE "exception: vector: allocator can't allocate memory"
#define NO_COMPARE_DATA "exception: vector::iterator: data is not comparable!"

namespace ft{
	template <class T, class Allocator = std::allocator<T> >
	class vector{
		friend class iterator;
	private:
		size_t			_reserve;
		Allocator		_alloc;
		size_t			_usedMem;
		size_t			_hitpoint;
		T *				_data;
	public:
		vector()
			: _usedMem(0)
			, _hitpoint(0)
			, _reserve(10)
			, _data(NULL){}
		vector(size_t n, T const & val = T()): vector(){
			// _reserve = 10; ////!!!!! vector() _reserve
			_hitpoint = max(n << 1, _reserve);
			_data = _alloc.allocate(_hitpoint);
			_usedMem = n;
			for (size_t i = 0; i < n; i++)
				_data[i] = val;
		}
		vector(vector const & oth)
			: _hitpoint(oth._hitpoint)
			, _usedMem(oth._usedMem)
			, _alloc(oth._alloc)
			, _data(oth._data){}
		~vector(){_alloc.deallocate(_data, _hitpoint);}
		void	push_back(const T & value){
			if (!_data){
				_hitpoint = _reserve;
				_data = _alloc.allocate(_hitpoint);
			}else if (_usedMem == _hitpoint){
				T * tmpData = _alloc.allocate(_hitpoint << 1);
				if (!tmpData)
					throw runtime_error(NO_MEM_SPACE);
				for (size_t i = 0; i < _usedMem; i++)
					tmpData[i] = _data[i];
				_alloc.deallocate(_data, _hitpoint);
				_hitpoint = _hitpoint << 1;
				_data = tmpData;
			}
			_data[_usedMem] = value;
			_usedMem++;
		}
		T & at(size_t i){
			if (i >= _usedMem)
				throw runtime_error("exception: vector: out of range");
			return _data[i];
		}
		T & operator [](size_t i){return _data[i];}
		void	swap(ft::vector<T> & oth){
			size_t tmpReservedMinMem = oth._reserve;
			Allocator tmpAlloc = oth._alloc;
			size_t tmpHitPoint = oth._hitpoint;
			size_t tmpUsedMem = oth._usedMem;
			T * tmpData = oth._data;

			oth._reserve = _reserve;
			oth._hitpoint = _hitpoint;
			oth._usedMem = _usedMem;
			oth._alloc = _alloc;
			oth._data = _data;

			_reserve = tmpReservedMinMem;
			_hitpoint = tmpHitPoint;
			_usedMem = tmpUsedMem;
			_alloc = tmpAlloc;
			_data = tmpData;
		}
		void 	assign(size_t n, T const & value){
			if (n > _hitpoint){
				_hitpoint = n << 1;
				_alloc.deallocate(_data, _hitpoint);
				_data = _alloc.allocate(_hitpoint);
				if (!_data)
					throw runtime_error(NO_MEM_SPACE);
			}
			for (size_t i = 0; i < n; i++)
				_data[i] = value;
			_usedMem = n;
		}
		template<class Iterator>
		void	assign(Iterator start, Iterator finish){
			while(start != finish)
				push_back(*start++);
		}
		void	reserve(size_t n){_reserve = n;}
		void	resize(size_t n, T const & val = T()){
			if (n < 1)
				throw runtime_error("э, пошол отсюда!!! что за ресайз??");
			if (_usedMem > n)
				_usedMem = n;
			T * tmpData = _alloc.allocate(max(n << 1, _reserve));
			if (!tmpData)
				throw runtime_error(NO_MEM_SPACE);
			for (size_t i = _usedMem - 1; i >= 0; i--)
				tmpData = _data[i];
			for (size_t i = n - 1; i >= _usedMem - 1; i--)
				tmpData = val;
			_alloc.deallocate(_data, _hitpoint);
			_hitpoint = max(n << 1, _reserve);
			_data = tmpData;
		}
	private:
		void replaceFromOth(ft::vector<T> const & oth){
			if (_data)
				_alloc.deallocate(_data, _hitpoint);
			_hitpoint = oth._hitpoint;
			_usedMem = oth._usedMem;
			_data = _alloc.allocate(_hitpoint);
			for (size_t i = 0; i < _usedMem; i++)
				_data[i] = oth._data[i];
		}
	// * Iterators
	public:
		class Iterator{
			friend class vector;
			T		const * _data;
			size_t	const _usedMem;
			size_t	_Iter;
			Iterator(T * data, size_t usedMem, size_t currentIter)
				: _data(data), _usedMem(usedMem), _Iter(currentIter){}
		public:
			Iterator()
				: _data(NULL), _usedMem(0), _Iter(0){}
			Iterator(Iterator const & iter)
				: _data(iter._data)
				, _usedMem(iter._usedMem)
				, _Iter(iter._Iter){}
			~Iterator(){}
		// * operator ++ -- *
			Iterator operator++(void){_Iter++; return *this;}
			Iterator operator++(int){Iterator tmp(*this); _Iter++; return tmp;}
			Iterator operator--(void){_Iter--; return *this;}
			Iterator operator--(int){Iterator tmp(*this); _Iter--; return tmp;}
			Iterator&operator*(){if (_Iter > _usedMem) _Iter = _usedMem; return _data[_Iter];}
		// * bool operator
		private:
			void	compare(Iterator const & oth){
				if (oth._data != _data)
					throw runtime_error(NO_COMPARE_DATA);
			}
		public:
			bool operator>	(Iterator const & oth){compare(oth); return _Iter >  oth._Iter;}
			bool operator>=	(Iterator const & oth){compare(oth); return _Iter >= oth._Iter;}
			bool operator<	(Iterator const & oth){compare(oth); return _Iter <  oth._Iter;}
			bool operator<=	(Iterator const & oth){compare(oth); return _Iter <= oth._Iter;}
			bool operator==	(Iterator const & oth){compare(oth); return _Iter == oth._Iter;}
			bool operator!=	(Iterator const & oth){compare(oth); return _Iter != oth._Iter;}
		};

	// * begin and end
	Iterator begin(){return Iterator(_data, _usedMem, 0);}
	Iterator end(){return Iterator(_data, _usedMem, _usedMem - 1);}
	};
};