#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

// Реализация очереди (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/queue/
namespace ft
{
	template<class T, class Container = ft::list<T> >
	class queue
	{
	public:
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
	private:
		container_type defaultClass;
		size_type _length;
	public:
		explicit queue(const container_type &ctnr = container_type()) : defaultClass(ctnr), _length(0)
		{}

		queue(const queue &x) : _length(0)
		{ *this = x; }

		queue &operator=(const queue &other)
		{
			defaultClass = other.defaultClass;
			_length = other._length;
			return (*this);
		}

		virtual ~queue()
		{}

		/* Member functions */

		bool empty() const
		{ return (_length == 0); }

		size_type size() const
		{ return (_length); }

		value_type &front()
		{ return (defaultClass.front()); }

		const value_type &front() const
		{ return (defaultClass.front()); }

		value_type &back()
		{ return (defaultClass.back()); }

		const value_type &back() const
		{ return (defaultClass.back()); }

		void push(const value_type &val)
		{
			_length++;
			return (defaultClass.push_back(val));
		}

		void pop()
		{
			if (_length)
				_length--;
			return (defaultClass.pop_front());
		}

	};
}

template <class T, class Container>
bool operator==(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
{
	return (lhs.defaultClass == rhs.defaultClass);
}

template <class T, class Container>
bool operator!=(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
{
	return (lhs.defaultClass != rhs.defaultClass);
}

template <class T, class Container>
bool operator<(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
{
	return (lhs.defaultClass < rhs.defaultClass);
}

template <class T, class Container>
bool operator<=(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
{
	return (lhs.defaultClass <= rhs.defaultClass);
}

template <class T, class Container>
bool operator>(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
{
	return (lhs.defaultClass > rhs.defaultClass);
}

template <class T, class Container>
bool operator>=(const ft::queue<T, Container> &lhs, const ft::queue<T, Container> &rhs)
{
	return (lhs.defaultClass >= rhs.defaultClass);
}

#endif