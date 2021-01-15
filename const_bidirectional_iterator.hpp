//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_CONST_BIDIRECTIONAL_ITERATOR_HPP
#define FT_CONTAINERS_CONST_BIDIRECTIONAL_ITERATOR_HPP

#include "bidirectional_iterator.hpp"

namespace ft
{
	template<class T>
	class const_bidirectional_iterator
	{
	private:
		list_t<T> *_ptr;
	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		explicit const_bidirectional_iterator() : _ptr(nullptr)
		{};

		explicit const_bidirectional_iterator(list_t<T> *ptr) : _ptr(ptr)
		{};

		const_bidirectional_iterator(const_bidirectional_iterator const &constBidirectionalIterator) :
				_ptr(constBidirectionalIterator._ptr)
		{}

		const_bidirectional_iterator(bidirectional_iterator<T> const &bidirectionalIterator) :
				_ptr(bidirectionalIterator.getCell())
		{}

		virtual ~const_bidirectional_iterator()
		{}

		const_bidirectional_iterator &operator=(const_bidirectional_iterator const &constBidirectionalIterator)
		{
			_ptr = constBidirectionalIterator._ptr;
			return (*this);
		}

		const_bidirectional_iterator &operator=(bidirectional_iterator<T> const &bidirectionalIterator)
		{
			_ptr = bidirectionalIterator.getCell();
			return (*this);
		}

		const_bidirectional_iterator &operator++()
		{
			_ptr = _ptr->next;
			return (*this);
		}

		const const_bidirectional_iterator operator++(int)
		{
			const_bidirectional_iterator it(_ptr);
			_ptr = _ptr->next;
			return (it);
		}

		const_bidirectional_iterator &operator--()
		{
			_ptr = _ptr->prev;
			return (*this);
		}

		const const_bidirectional_iterator operator--(int)
		{
			const_bidirectional_iterator it(_ptr);
			_ptr = _ptr->prev;
			return (it);
		}

		bool operator==(const_bidirectional_iterator const &constBidirectionalIterator)
		{
			return (_ptr == constBidirectionalIterator._ptr);
		}

		bool operator!=(const_bidirectional_iterator const &constBidirectionalIterator)
		{
			return (_ptr != constBidirectionalIterator._ptr);
		}

		reference operator*() const
		{
			return (*_ptr->data);
		}

		pointer operator->() const
		{
			return (_ptr->data);
		}
	};
}

#endif