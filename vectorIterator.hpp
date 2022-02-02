#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

namespace ft
{
	template <class T>
	class vIterator
	{
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::random_access_iterator_tag iterator_category;
		protected:
			pointer _ptr;
		public:
			 vIterator(void)
			{};
			 vIterator(const vIterator &other)
			{
				*this = other;
			};
			 vIterator(pointer ptr)
			: _ptr(ptr)
			{};
			 ~vIterator(void)
			{};
			vIterator &operator=(const vIterator &other)
			{
				_ptr = other._ptr;
				return (*this);
			};
			vIterator &operator++(void)
			{
				_ptr++;
				return (*this);
			};
			vIterator &operator--(void)
			{
				_ptr--;
				return (*this);
			};
			vIterator operator++(int)
			{
				vIterator tmp(*this);
				operator++();
				return (tmp);
			};
			vIterator operator--(int)
			{
				vIterator tmp(*this);
				operator--();
				return (tmp);
			};
			bool operator==(const vIterator &other) const
			{
				return (_ptr == other._ptr);
			};
			bool operator!=(const vIterator &other) const
			{
				return (_ptr != other._ptr);
			};
			bool operator>(const vIterator &other) const
			{
				return (_ptr > other._ptr);
			};
			bool operator>=(const vIterator &other) const
			{
				return (_ptr >= other._ptr);
			};
			bool operator<(const vIterator &other) const
			{
				return (_ptr < other._ptr);
			};
			bool operator<=(const vIterator &other) const
			{
				return (_ptr <= other._ptr);
			};
			value_type &operator*(void)
			{
				return (*_ptr);
			};
			value_type *operator->(void)
			{
				return (_ptr);
			};
			vIterator operator+(int n) const
			{
				vIterator tmp(*this);
				tmp += n;
				return (tmp);
			};
			vIterator operator-(int n) const
			{
				vIterator tmp(*this);
				tmp -= n;
				return (tmp);
			};
			vIterator &operator+=(int n)
			{
				while (n < 0)
				{
					(*this)--;
					n++;
				}
				while (n > 0)
				{
					(*this)++;
					n--;
				}
				return (*this);
			};
			vIterator &operator-=(int n)
			{
				while (n > 0)
				{
					operator--();
					n--;
				}
				while (n < 0)
				{
					operator++();
					n++;
				}
				return (*this);
			};
			value_type &operator[](int n) const
			{
				return (*(*this + n));
			}
	};
	template <class T>
	class rvIterator : public vIterator<T>
	{
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::random_access_iterator_tag iterator_category;
			rvIterator(void)
			{};
			rvIterator(const rvIterator &other)
			{
				*this = other;
			};
			rvIterator(pointer ptr)
			{
				this->_ptr = ptr;
			};
			~rvIterator(void)
			{};
			rvIterator &operator=(const rvIterator &other)
			{
				this->_ptr = other._ptr;
				return (*this);
			};
			rvIterator &operator++(void)
			{
				this->_ptr--;
				return (*this);
			};
			rvIterator operator++(int)
			{
				rvIterator tmp(*this);
				this->_ptr--;
				return (tmp);
			};
			rvIterator &operator--(void)
			{
				this->_ptr++;
				return (*this);
			};
			rvIterator operator--(int)
			{
				rvIterator tmp(*this);
				tmp._ptr++;
				rteurn (tmp);
			};
			rvIterator operator+=(int n)
			{
				while (n > 0)
				{
					operator++();
					n--;
				}
				while (n < 0)
				{
					operator--();
					n++;
				}
				return (*this);
			};
			rvIterator operator-=(int n)
			{
				while (n > 0)
				{
					operator--();
					n--;
				}
				while (n < 0)
				{
					operator++();
					n++;
				}
				return (*this);
			};
			bool operator==(const rvIterator &other) const
			{
				return (this->_ptr == other._ptr);
			};
			bool operator!=(const rvIterator &other) const
			{
				return (this->_ptr != other._ptr);
			};
			bool operator>(const rvIterator &other) const
			{
				return (this->_ptr > other._ptr);
			};
			bool operator>=(const rvIterator &other) const
			{
				return (this->_ptr >= other._ptr);
			};
			bool operator<(const rvIterator &other) const
			{
				return (this->_ptr < other._ptr);
			};
			bool operator<=(const rvIterator &other) const
			{
				return (this->_ptr <= other._ptr);
			};
			value_type &operator*(void)
			{
				return (*this->_ptr);
			};
			value_type *operator->(void)
			{
				return (this->_ptr);
			};
			rvIterator operator+(int n) const
			{
				rvIterator tmp(*this);
				tmp += n;
				return (tmp);
			};
			rvIterator operator-(int n) const
			{
				rvIterator tmp(*this);
				tmp -= n;
				return (tmp);
			};
			value_type &operator[](int n) const
			{
				std::cout << "eeeeee" << std::endl;
				return (*(*this - n));
			};
	};
	template <class T>
	class cvIterator : public vIterator<T>
	{
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::random_access_iterator_tag iterator_category;
			cvIterator(void)
			{};
			cvIterator(pointer ptr)
			{
				this->_ptr = ptr;
			};
			cvIterator(const cvIterator &other)
			{
				*this = other;
			};
			~cvIterator(void)
			{};
			cvIterator &operator=(const cvIterator &other)
			{
				this->_ptr = other._ptr;
				return (*this);
			};
			const value_type &operator*(void)
			{
				return (*this->_ptr);
			};
			const value_type &operator[](int n) const
			{
				return (*(*this + n));
			}
	};
	template <class T>
	class crvIterator : public rvIterator<T>
	{
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::random_access_iterator_tag iterator_category;
			crvIterator(void)
			{};
			crvIterator(pointer ptr)
			{
				this->_ptr = ptr;
			};
			crvIterator(const crvIterator &other)
			{
				*this = other;
			};
			~crvIterator(void)
			{};
			crvIterator &operator=(const crvIterator &other)
			{
				this->_ptr = other._ptr;
				return (*this);
			};
			const value_type &operator*(void)
			{
				return (*this->_ptr);
			};
			const value_type &operator[](int n) const
			{
				return (*(*this - n));
			}
	};
};

#endif