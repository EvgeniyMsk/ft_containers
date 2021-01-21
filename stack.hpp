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
	private:
		container_type defaultClass;
		size_type _length;
	public:
		explicit stack(const container_type &ctnr = container_type()) : defaultClass(ctnr), _length(0)
		{}

		stack(const stack &x) : _length(0)
		{ *this = x; }

		stack &operator=(const stack &other)
		{
			defaultClass = other.defaultClass;
			_length = other._length;
			return (*this);
		}

		virtual ~stack()
		{}

		//	Member functions
		//	Test whether container is empty
		bool empty() const
		{ return (_length == 0); }

		//	Return size
		size_type size() const
		{ return (_length); }

		//	Access next element
		value_type &top()
		{ return (defaultClass.back()); }

		const value_type &top() const
		{ return (defaultClass.back()); }

		//	Insert element
		void push(const value_type &val)
		{
			_length++;
			return (defaultClass.push_back(val));
		}

		//	Remove top element
		void pop()
		{
			if (_length)
				_length--;
			return (defaultClass.pop_back());
		}
	};
}

template <class T, class Container>
bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (lhs.defaultClass == rhs.defaultClass);
}

template <class T, class Container>
bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (lhs.defaultClass != rhs.defaultClass);
}

template <class T, class Container>
bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (lhs.defaultClass < rhs.defaultClass);
}

template <class T, class Container>
bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (lhs.defaultClass <= rhs.defaultClass);
}

template <class T, class Container>
bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (lhs.defaultClass > rhs.defaultClass);
}

template <class T, class Container>
bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (lhs.defaultClass >= rhs.defaultClass);
}

#endif