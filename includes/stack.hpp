/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:42:41 by qsymond           #+#    #+#             */
/*   Updated: 2021/01/25 13:42:42 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"
// Реализация стека (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/stack/stack/
namespace ft
{
	template<class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
		container_type container;

		//Member function
		explicit stack(const container_type &ctnr = container_type())
		{ container = ctnr; }

		bool empty() const
		{ return (container.empty()); }

		size_type size() const
		{ return (container.size()); }

		value_type &top()
		{ return (container.back()); }

		const value_type &top() const
		{ return (container.back()); }

		void push(const value_type &val)
		{ container.push_back(val); }

		void pop()
		{ container.pop_back(); }

		friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{ return (lhs.container == rhs.container); }

		friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{ return (lhs.container != rhs.container); }

		friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{ return (lhs.container < rhs.container); }

		friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{ return (lhs.container > rhs.container); }

		friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{ return (lhs.container <= rhs.container); }

		friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
		{ return (lhs.container >= rhs.container); }
	};
}


#endif
