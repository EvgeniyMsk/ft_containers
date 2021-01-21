#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

// Реализация стека (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/stack/stack/
namespace ft
{
	template<class T, class Container = ft::list<T> >
	class stack
	{
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
	protected:
		container_type defaultClass;
		size_type length;
	public:
		explicit stack(const container_type &ctnr = container_type()) : defaultClass(ctnr), length(0)
		{}

		stack(const stack &x) : length(0)
		{ *this = x; }

		stack &operator=(const stack &other)
		{
			defaultClass = other.defaultClass;
			length = other.length;
			return (*this);
		}

		virtual ~stack()
		{}

		//	Member functions
		//	Test whether container is empty
		bool empty() const
		{ return (length == 0); }

		//	Return size
		size_type size() const
		{ return (length); }

		//	Access next element
		value_type &top()
		{ return (defaultClass.back()); }

		const value_type &top() const
		{ return (defaultClass.back()); }

		//	Insert element
		void push(const value_type &val)
		{
			length++;
			return (defaultClass.push_back(val));
		}

		//	Remove top element
		void pop()
		{
			if (length)
				length--;
			return (defaultClass.pop_back());
		}

		friend bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
		{
			return (lhs.defaultClass == rhs.defaultClass);
		}

		friend bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
		{
			return (lhs.defaultClass != rhs.defaultClass);
		}

		friend bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
		{
			return (lhs.defaultClass < rhs.defaultClass);
		}

		friend bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
		{
			return (lhs.defaultClass <= rhs.defaultClass);
		}

		friend bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
		{
			return (lhs.defaultClass > rhs.defaultClass);
		}

		friend bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
		{
			return (lhs.defaultClass >= rhs.defaultClass);
		}
	};
}

#endif
