#include <memory>
#include <string>
#include "vectorException.hpp"

using std::allocator;

namespace ft{
	template <typename T>//	!!!!
	class vector{
	private:
		allocator<T> _alloc;
		size_t	_usedMem;
		size_t	_hitpoint;
		T * _data;
	public:
		vector(): _usedMem(0), _hitpoint(0){
			_data = NULL;
		}
		vector(vector const & oth){
			_hitpoint = oth._hitpoint;
			_usedMem = oth._usedMem;
			_alloc = oth._alloc;
			_data = oth._data;
		}
		~vector(){
			_alloc.deallocate(_data, _hitpoint);
		}
		void	push_back(const T & value){
			if (!_data){
				_hitpoint = 8;
				_data = _alloc.allocate(_hitpoint);
			}else if (_usedMem == _hitpoint){
				T * tmpData = _alloc.allocate(_hitpoint << 1);
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
				throw vectorException("Выход за пределы массива");
			return _data[i];
		}

		T & operator [](size_t i){return this->at(i);}

		void	swap(ft::vector<T> & oth){
			allocator<T> tmpAlloc = oth._alloc;
			size_t tmpHitPoint = oth._hitpoint;
			size_t tmpUsedMem = oth._usedMem;
			T * tmpData = oth._data;

			oth._hitpoint = _hitpoint;
			oth._usedMem = _usedMem;
			oth._alloc = _alloc;
			oth._data = _data;

			_hitpoint = tmpHitPoint;
			_usedMem = tmpUsedMem;
			_alloc = tmpAlloc;
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
	};
};