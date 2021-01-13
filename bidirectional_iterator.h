#ifndef FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_H
#define FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_H

#include <memory>

namespace ft
{
	template<typename T>
	struct list_t
	{
		T *data;
		struct list_t *next;
		struct list_t *prev;
	};

	template<class T>
	class bidirectional_iterator
	{
	private:
		list_t<T> *_ptr;
	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		explicit bidirectional_iterator() : _ptr(nullptr)
		{}

		explicit bidirectional_iterator(list_t<T> *ptr) : _ptr(ptr)
		{}

		bidirectional_iterator(bidirectional_iterator const &bidirectionalIterator) : _ptr(bidirectionalIterator._ptr)
		{}

		bidirectional_iterator &operator=(bidirectional_iterator const &bidirectionalIterator)
		{
			_ptr = bidirectionalIterator._ptr;
			return (*this);
		};

		virtual ~bidirectional_iterator()
		{}

		bidirectional_iterator &operator++()
		{
			_ptr = _ptr->next;
			return (*this);
		}

		const bidirectional_iterator operator++(int)
		{
			bidirectional_iterator it(_ptr);
			_ptr = _ptr->next;
			return (it);
		}

		bidirectional_iterator &operator--()
		{
			_ptr = _ptr->prev;
			return (*this);
		}

		const bidirectional_iterator operator--(int)
		{
			bidirectional_iterator it(_ptr);
			_ptr = _ptr->next;
			return (it);
		}

		bool operator==(bidirectional_iterator const &bidirectionalIterator)
		{
			return (_ptr == bidirectionalIterator._ptr);
		}

		bool operator!=(bidirectional_iterator const &bidirectionalIterator)
		{
			return (_ptr != bidirectionalIterator._ptr);
		}

		reference operator*() const
		{ return (*_ptr->data); }

		pointer operator->() const
		{ return (_ptr->data); }

		list_t<T> *getCell() const
		{ return (_ptr); }
	};
}

#endif
