//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_CONST_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_CONST_REVERSE_ITERATOR_HPP

#include "reverse_iterator.hpp"

namespace ft
{
	template<typename T>
	class const_reverse_iterator
	{
	private:
		list_t<T> *_ptr;
	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		explicit const_reverse_iterator() : _ptr(nullptr)
		{}

		explicit const_reverse_iterator(list_t<T> *ptr) : _ptr(ptr)
		{}

		const_reverse_iterator(const_reverse_iterator const &constReverseIterator) : _ptr(constReverseIterator._ptr)
		{}

		const_reverse_iterator(reverse_iterator<T> const &reverseIterator) : _ptr(reverseIterator.getCell())
		{}

		virtual ~const_reverse_iterator()
		{}

		const_reverse_iterator &operator=(const_reverse_iterator const &constReverseIterator)
		{
			_ptr = constReverseIterator._ptr;
			return (*this);
		}

		const_reverse_iterator &operator=(reverse_iterator<T> const &reverseIterator)
		{
			_ptr = reverseIterator.getCell();
			return (*this);
		}

		const_reverse_iterator &operator++()
		{
			_ptr = _ptr->previous;
			return (*this);
		}

		const const_reverse_iterator operator++(int)
		{
			const_reverse_iterator it(_ptr);
			_ptr = _ptr->previous;
			return (it);
		}

		const_reverse_iterator &operator--()
		{
			_ptr = _ptr->next;
			return (*this);
		}

		const const_reverse_iterator operator--(int)
		{
			const_reverse_iterator it(_ptr);
			_ptr = _ptr->next;
			return (it);
		}

		bool operator==(const_reverse_iterator const &constReverseIterator)
		{
			return (_ptr == constReverseIterator._ptr);
		}

		bool operator!=(const_reverse_iterator const &constReverseIterator)
		{
			return (_ptr != constReverseIterator._ptr);
		}

		reference operator*()
		{
			return (*_ptr->data);
		}

		pointer operator->()
		{
			return (_ptr->data);
		}
	};
}
#endif //FT_CONTAINERS_CONST_REVERSE_ITERATOR_HPP
