/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:42:38 by qsymond           #+#    #+#             */
/*   Updated: 2021/01/25 13:52:54 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;
		container_type container;

		//Member function
		explicit queue(const container_type &ctnr = container_type())
		{ container = ctnr; }

		bool empty() const
		{ return (container.empty()); }

		size_type size() const
		{ return (container.size()); }

		value_type &front()
		{ return (container.front()); }

		const value_type &front() const
		{ return (container.front()); }

		value_type &back()
		{ return (container.back()); }

		const value_type &back() const
		{ return (container.back()); }

		void push(const value_type &val)
		{ container.push_back(val); }

		void pop()
		{ container.pop_back(); }

		friend bool operator==(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.container == rhs.container); }

		friend bool operator!=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.container != rhs.container); }

		friend bool operator<(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.container < rhs.container); }

		friend bool operator>(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.container > rhs.container); }

		friend bool operator<=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.container <= rhs.container); }

		friend bool operator>=(const queue<T, Container> &lhs, const queue<T, Container> &rhs)
		{ return (lhs.container >= rhs.container); }
	};
}

#endif