#include <deque>

namespace ft{
	template<typename T, class Container = deque<T>>
	class stack{
	public:
		typedef Container									container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;
		typedef typename container_type::size_type			size_type;
	
	protected:
		container_type	c;
	
	public:
		stack() = default;
		~stack() = default;
		stack(const stack& q) = default;
		stack(stack&& q) = default;

		stack& operator=(const stack & q) = default;
		stack& operator=(stack && q) = default;
		
		stack& operator=(stack && q) = default;
		explicit stack(const container_type& c);
		explicit stack(container_type&& c);
		template <class Alloc> explicit stack(const Alloc& a);
		template <class Alloc> stack(const container_type& c, const Alloc& a);
		template <class Alloc> stack(container_type& c, const Alloc& a);
		template <class Alloc> stack(const stack& c, const Alloc& a);
		template <class Alloc> stack(stack& c, const Alloc& a);

		bool empty() const;
		size_type size() const;
		reference top();
		const_reference top() const;

		void push(const value_type& x);
		void push(value_type& x);
		template <class... Args> reference emplace(Args&&... args);
		void pop();
		void swap(stack& c) noexcept(is_nothrow_swapable_v<Container>);
	};
}