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
		size_type length;
	public:
		//	Construct queue
		explicit queue(const container_type &ctnr = container_type()) : defaultClass(ctnr), length(0)
		{}

		//	Construct queue
		queue(const queue &x) : length(0)
		{ *this = x; }

		//	Assignation
		queue &operator=(const queue &other)
		{
			defaultClass = other.defaultClass;
			length = other._length;
			return (*this);
		}

		//	Destructor
		virtual ~queue()
		{}

		//	Member functions
		//	Test whether container is empty
		bool empty() const
		{ return (length == 0); }

		//	Return size
		size_type size() const
		{ return (length); }

		//	Access next element
		value_type &front()
		{ return (defaultClass.front()); }

		//	Access next element
		const value_type &front() const
		{ return (defaultClass.front()); }

		//	Access last element
		value_type &back()
		{ return (defaultClass.back()); }

		//	Access last element
		const value_type &back() const
		{ return (defaultClass.back()); }

		//	Insert element
		void push(const value_type &val)
		{
			length++;
			return (defaultClass.push_back(val));
		}

		//	Remove next element
		void pop()
		{
			if (length)
				length--;
			return (defaultClass.pop_front());
		}

	};
}

//	Non-member function overloads
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