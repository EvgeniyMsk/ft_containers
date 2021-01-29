/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:42:48 by qsymond           #+#    #+#             */
/*   Updated: 2021/01/25 13:55:07 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP
#include "vector.hpp"
// Реализация двусторонней очереди (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/deque/deque/
namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class deque : public ft::vector<T, Alloc>
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef random_access_iterator<T> iterator;
		typedef const_random_access_iterator<T> const_iterator;
		typedef reverse_random_access_iterator<T> reverse_iterator;
		typedef const_reverse_random_access_iterator<T> const_reverse_iterator;
	private:
		value_type *ptr;
		size_type length;
		size_type realLength;
		allocator_type _Alloc;
		//	Request a change in capacity
		void reserve(size_type n)
		{
			ft::vector<T>::reserve(n);
		}
	public:
		//	Member functions
		//	Constructs an empty container, with no elements.
		explicit deque(const allocator_type &alloc = allocator_type()) :
				length(0), realLength(0)
		{
			_Alloc = alloc;
			ptr = nullptr;
		}

		//	Constructs a container with n elements. Each element is a copy of val.
		explicit deque(size_type n, const value_type &val = value_type(),
					   const allocator_type &alloc = allocator_type()) :
					   ft::vector<T, Alloc>(n, val, alloc)
		{
		}

		//	Constructs a container with as many elements as the range [first,last), with each
		//	element constructed from its corresponding element in that range, in the same order.
		template<class InputIterator>
		deque(InputIterator first, typename enable_if<std::is_class<InputIterator>::value, InputIterator>::type last,
			  const allocator_type &alloc = allocator_type()) :
			  ft::vector<T, Alloc>(first, last, alloc)
		{
		}

		//	Constructs a container with a copy of each of the elements in x, in the same order.
		deque(const deque &x) 
		{
			_Alloc = x._Alloc;
			length = 0;
			realLength = 0;
			*this = x;
		}

		//	Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		deque &operator=(const deque &other)
		{
			this->clear();
			if (other.empty())
				return (*this);
			for (const_iterator it = other.begin(); it != other.end(); it++)
				this->push_back(*it);
			return (*this);
		}

		//	This destroys all container elements, and deallocates all the storage capacity allocated
		//	by the vector using its allocator.
		virtual ~deque()
		{
			if (realLength > 0)
				_Alloc.deallocate(ptr, realLength);
		}

		void push_front (const value_type& val)
		{
			this->insert(this->begin(), val);
		}

		void pop_front()
		{
			this->erase(this->begin());
		}

		friend void swap(ft::deque<T, Alloc> &lhs, ft::deque<T, Alloc> &rhs)
		{
			lhs.swap(rhs);
		}

		friend bool operator==(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			if (lhs.size() == 0 && rhs.size() == 0)
				return (true);
			typename ft::deque<T>::const_iterator beginLhs = lhs.begin();
			typename ft::deque<T>::const_iterator beginRhs = rhs.begin();
			typename ft::deque<T>::const_iterator endLhs = lhs.end();
			typename ft::deque<T>::const_iterator endRhs = rhs.end();
			while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
			{
				beginLhs++;
				beginRhs++;
			}
			return beginLhs == endLhs && beginRhs == endRhs;
		}

		friend bool operator!=(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
		{
			return (!(lhs == rhs));
		}

		friend bool operator<(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
		{
			if (lhs.size() < rhs.size())
				return (true);
			if (lhs.size() > rhs.size() || (lhs.size() == 0 && rhs.size() == 0))
				return (false);
			typename ft::deque<T>::const_iterator beginLhs = lhs.begin();
			typename ft::deque<T>::const_iterator beginRhs = rhs.begin();
			typename ft::deque<T>::const_iterator endLhs = lhs.end();
			typename ft::deque<T>::const_iterator endRhs = rhs.end();

			while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
			{
				beginLhs++;
				beginRhs++;
			}
			return !((beginLhs == endLhs && beginRhs == endRhs) || beginRhs == endRhs || *beginLhs >= *beginRhs);
		}

		friend bool operator<=(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
		{
			return (lhs < rhs || lhs == rhs);
		}

		friend bool operator>(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs){
			if (lhs.size() > rhs.size())
				return (true);
			if (lhs.size() < rhs.size() || (lhs.size() == 0 && rhs.size() == 0))
				return (false);
			typename ft::deque<T>::const_iterator beginLhs = lhs.begin();
			typename ft::deque<T>::const_iterator  beginRhs = rhs.begin();
			typename ft::deque<T>::const_iterator  endLhs = lhs.end();
			typename ft::deque<T>::const_iterator  endRhs = rhs.end();

			while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
			{
				beginLhs++;
				beginRhs++;
			}
			return !((beginLhs == endLhs && beginRhs == endRhs) || beginLhs == endLhs || *beginLhs <= *beginRhs);
		}

		friend bool operator>=(const ft::deque<T, Alloc> &lhs, const ft::deque<T, Alloc> &rhs)
		{
			return (lhs > rhs || lhs == rhs);
		}
	};
}
#endif