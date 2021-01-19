#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include "list.hpp"

// Реализация стека (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/stack/stack/
namespace ft {
	template< class T, class Container = ft::list<T> >
	class stack {
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef	typename Container::size_type		size_type;
		typedef	typename Container::reference		reference;
		typedef	typename Container::const_reference const_reference;
	private:
		container_type	defaultClass;
		size_type		_length;
	public:
		explicit stack (const container_type& ctnr = container_type()) : defaultClass(ctnr), _length(0) {}

		stack(const stack& x): _length(0) { *this = x; }

		stack &operator=( const stack& other ) {
			defaultClass = other.defaultClass;
			_length = other._length;
			return (*this);
		}

		virtual ~stack(void) {}

		//	Member functions
		//	Test whether container is empty
		bool empty() const { return (this->_length == 0); }

		//	Return size
		size_type size(void) const { return (this->_length); }

		//	Access next element
		value_type& top(void) { return (this->defaultClass.back()); }

		const value_type& top(void) const { return (this->defaultClass.back()); }

		//	Insert element
		void push (const value_type& val) {
			this->_length++;
			return (this->defaultClass.push_back(val));
		}

		//	Remove top element
		void pop (void) {
			if (this->_length)
				this->_length--;
			return (this->defaultClass.pop_back());
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
