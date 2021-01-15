//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "bidirectional_iterator.hpp"
namespace ft
{
	template<typename T>
	class reverse_iterator
	{
	private:
		list_t<T> *_ptr;
	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		explicit reverse_iterator() : _ptr(nullptr)
		{}

		explicit reverse_iterator(list_t<T> *ptr) : _ptr(ptr)
		{}

		reverse_iterator(reverse_iterator const &reverseIterator) : _ptr(reverseIterator._ptr)
		{}

		virtual ~reverse_iterator()
		{}

		reverse_iterator &operator=(reverse_iterator const &reverseIterator)
		{
			_ptr = reverseIterator._ptr;
			return (*this);
		}

		reverse_iterator &operator++()
		{
			_ptr = _ptr->prev;
			return (*this);
		}

		const reverse_iterator operator++(int)
		{
			reverse_iterator it(_ptr);
			_ptr = _ptr->prev;
			return (it);
		}

		reverse_iterator &operator--()
		{
			_ptr = _ptr->next;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator it(_ptr);
			_ptr = _ptr->next;
			return (it);
		}

		bool operator==(reverse_iterator const &reverseIterator)
		{ return (_ptr == reverseIterator._ptr); }

		bool operator!=(reverse_iterator const &reverseIterator)
		{ return (_ptr != reverseIterator._ptr); }

		reference operator*() const
		{ return (*_ptr->data); }

		pointer operator->() const
		{ return (_ptr->data); }

		list_t<T> *getCell() const
		{
			return (_ptr);
		}
	};
}
#endif
