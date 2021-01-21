//
// Created by Qsymond on 2021-01-21.
//

#ifndef FT_CONTAINERS_UTILS_HPP
#define FT_CONTAINERS_UTILS_HPP

#include <memory>
#include <iostream>
#include <limits>

namespace ft
{
	template<typename T>
	struct list_t
	{
		T *data;
		struct list_t *next;
		struct list_t *previous;
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
			_ptr = _ptr->previous;
			return (*this);
		}

		const bidirectional_iterator operator--(int)
		{
			bidirectional_iterator it(_ptr);
			_ptr = _ptr->previous;
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
		{
			return (*_ptr->data);
		}

		pointer operator->() const
		{
			return (_ptr->data);
		}

		list_t<T> *getCell() const
		{
			return (_ptr);
		}
	};

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
			_ptr = _ptr->previous;
			return (*this);
		}

		const const_bidirectional_iterator operator--(int)
		{
			const_bidirectional_iterator it(_ptr);
			_ptr = _ptr->previous;
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
			_ptr = _ptr->previous;
			return (*this);
		}

		const reverse_iterator operator++(int)
		{
			reverse_iterator it(_ptr);
			_ptr = _ptr->previous;
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

		reference operator*() const
		{
			return (*_ptr->data);
		}

		pointer operator->() const
		{
			return (_ptr->data);
		}
	};

	template<typename T>
	class random_access_iterator
	{

	private:
		T *ptr;

	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		random_access_iterator() : ptr(nullptr)
		{}

		random_access_iterator(T *p) : ptr(p)
		{}

		random_access_iterator(const random_access_iterator &randomAccessIterator)
		{ *this = randomAccessIterator; }

		random_access_iterator &operator=(const random_access_iterator &iter)
		{
			ptr = iter.ptr;
			return (*this);
		}

		virtual ~random_access_iterator()
		{}

		random_access_iterator &operator++()
		{
			ptr++;
			return (*this);
		}

		const random_access_iterator operator++(int)
		{
			random_access_iterator ret = random_access_iterator(*this);
			ptr++;
			return ret;
		}

		const random_access_iterator &operator--()
		{
			ptr--;
			return (*this);
		}

		const random_access_iterator operator--(int)
		{

			random_access_iterator ret = random_access_iterator(*this);
			ptr--;
			return ret;
		}

		bool operator==(random_access_iterator const &randomAccessIterator)
		{ return (ptr == randomAccessIterator.ptr); }

		bool operator!=(random_access_iterator const &randomAccessIterator)
		{ return (ptr != randomAccessIterator.ptr); }

		random_access_iterator operator+(std::ptrdiff_t n)
		{
			random_access_iterator temp = *this;
			return (temp += n);
		}

		random_access_iterator &operator+=(std::ptrdiff_t step)
		{
			std::ptrdiff_t i = step;
			if (i >= 0)
				while (i--)
					ptr++;
			else
				while (i++)
					ptr--;
			return (*this);
		}

		random_access_iterator operator-(long n)
		{
			random_access_iterator temp = *this;
			return temp -= n;
		}

		random_access_iterator &operator-=(std::ptrdiff_t n)
		{ return (*this += -n); }

		std::ptrdiff_t operator-(random_access_iterator &a)
		{ return (ptr - a.ptr); }

		reference &operator[](std::ptrdiff_t n)
		{ return (*(*this + n)); }

		reference &operator*() const
		{ return (*ptr); }

		pointer *operator->() const
		{ return (ptr); }

		T *getPtr() const
		{ return ptr; }
	};

	template<typename T>
	class const_random_access_iterator
	{
	private:
		T *ptr;
	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		const_random_access_iterator() : ptr(nullptr)
		{}

		explicit const_random_access_iterator(T *p) : ptr(p)
		{}

		const_random_access_iterator(const const_random_access_iterator &constRandomAccessIterator)
		{ *this = constRandomAccessIterator; }

		const_random_access_iterator(const random_access_iterator<T> &randomAccessIterator)
		{ *this = randomAccessIterator; }

		const_random_access_iterator &operator=(const const_random_access_iterator &constRandomAccessIterator)
		{
			ptr = constRandomAccessIterator.ptr;
			return (*this);
		}

		const_random_access_iterator &operator=(const random_access_iterator<T> &randomAccessIterator)
		{
			ptr = randomAccessIterator.getPtr();
			return (*this);
		}

		virtual ~const_random_access_iterator()
		{}

		const_random_access_iterator &operator++()
		{
			ptr++;
			return (*this);
		}

		const const_random_access_iterator operator++(int)
		{
			const_random_access_iterator ret = const_random_access_iterator(*this);
			ptr++;
			return ret;
		}

		const_random_access_iterator &operator--()
		{
			ptr--;
			return (*this);
		}

		const const_random_access_iterator operator--(int)
		{
			const_random_access_iterator ret = const_random_access_iterator(*this);
			ptr--;
			return ret;
		}

		bool operator==(const_random_access_iterator const &constRandomAccessIterator)
		{ return (ptr == constRandomAccessIterator.ptr); }

		bool operator!=(const_random_access_iterator const &constRandomAccessIterator)
		{ return (ptr != constRandomAccessIterator.ptr); }

		const_random_access_iterator operator+(std::ptrdiff_t n)
		{
			const_random_access_iterator temp = *this;
			return (temp += n);
		}

		const_random_access_iterator &operator+=(std::ptrdiff_t step)
		{

			std::ptrdiff_t i = step;
			if (i >= 0)
				while (i--)
					ptr++;
			else
				while (i++)
					ptr--;
			return (*this);
		}

		const_random_access_iterator operator-(long n)
		{
			const_random_access_iterator temp = *this;
			return temp -= n;
		}

		const_random_access_iterator &operator-=(std::ptrdiff_t n)
		{ return (*this += -n); }

		std::ptrdiff_t operator-(const_random_access_iterator &a)
		{ return (ptr - a.ptr); }

		reference &operator[](std::ptrdiff_t n)
		{ return (*(*this + n)); }

		const reference &operator*() const
		{ return (*ptr); }

		pointer *operator->() const
		{ return (ptr); }
	};

	template<typename T>
	class reverse_random_access_iterator
	{

	private:
		T *ptr;

	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		reverse_random_access_iterator() : ptr(nullptr)
		{}

		reverse_random_access_iterator(T *p) : ptr(p)
		{}

		reverse_random_access_iterator(const reverse_random_access_iterator &reverseRandomAccessIterator)
		{ *this = reverseRandomAccessIterator; }

		reverse_random_access_iterator &operator=(const reverse_random_access_iterator &reverseRandomAccessIterator)
		{
			ptr = reverseRandomAccessIterator.ptr;
			return (*this);
		}

		virtual ~reverse_random_access_iterator(void)
		{}

		reverse_random_access_iterator &operator++()
		{
			ptr--;
			return (*this);
		}

		const reverse_random_access_iterator operator++(int)
		{

			reverse_random_access_iterator ret = *this;
			ptr--;
			return ret;
		}

		reverse_random_access_iterator &operator--()
		{

			ptr++;
			return (*this);
		}

		const reverse_random_access_iterator operator--(int)
		{
			reverse_random_access_iterator ret = reverse_random_access_iterator(*this);
			ptr++;
			return ret;
		}

		bool operator==(reverse_random_access_iterator const &reverseRandomAccessIterator)
		{ return (ptr == reverseRandomAccessIterator.ptr); }

		bool operator!=(reverse_random_access_iterator const &reverseRandomAccessIterator)
		{ return (ptr != reverseRandomAccessIterator.ptr); }

		reverse_random_access_iterator operator+(std::ptrdiff_t n)
		{
			reverse_random_access_iterator temp = reverse_random_access_iterator(*this);
			return (temp -= n);
		}

		reverse_random_access_iterator &operator+=(std::ptrdiff_t step)
		{
			std::ptrdiff_t i = step;
			if (i >= 0)
				while (i--)
					ptr--;
			else
				while (i++)
					ptr++;
			return (*this);
		}

		reverse_random_access_iterator operator-(long n)
		{
			reverse_random_access_iterator temp = *this;
			return temp += n;
		}

		reverse_random_access_iterator &operator-=(std::ptrdiff_t n)
		{ return (*this -= -n); }

		std::ptrdiff_t operator-(reverse_random_access_iterator &a)
		{ return (ptr - a.ptr); }

		reference &operator[](std::ptrdiff_t n) const
		{ return (*(*this - n)); }

		reference &operator*() const
		{ return (*(ptr)); }

		pointer *operator->() const
		{ return (ptr); }

		T *getPtr() const
		{ return ptr; }
	};

	template<typename T>
	class const_reverse_random_access_iterator
	{

	private:
		T *ptr;

	public:
		typedef typename std::allocator<T>::reference reference;
		typedef typename std::allocator<T>::pointer pointer;

		const_reverse_random_access_iterator() : ptr(nullptr)
		{}

		const_reverse_random_access_iterator(T *p) : ptr(p)
		{}

		const_reverse_random_access_iterator(const const_reverse_random_access_iterator &constReverseRandomAccessIterator)
		{ *this = constReverseRandomAccessIterator; }

		const_reverse_random_access_iterator(const reverse_random_access_iterator<T> &reverseRandomAccessIterator)
		{ *this = reverseRandomAccessIterator; }

		const_reverse_random_access_iterator &operator=(const const_reverse_random_access_iterator &constReverseRandomAccessIterator)
		{
			ptr = constReverseRandomAccessIterator.ptr;
			return (*this);
		}

		const_reverse_random_access_iterator &operator=(const reverse_random_access_iterator<T> &reverseRandomAccessIterator)
		{
			ptr = reverseRandomAccessIterator.getPtr();
			return (*this);
		}

		virtual ~const_reverse_random_access_iterator()
		{}

		const_reverse_random_access_iterator &operator++()
		{
			ptr--;
			return (*this);
		}

		const const_reverse_random_access_iterator operator++(int)
		{
			const_reverse_random_access_iterator ret = *this;
			ptr--;
			return ret;
		}

		const_reverse_random_access_iterator &operator--()
		{
			ptr++;
			return (*this);
		}

		const const_reverse_random_access_iterator operator--(int)
		{
			const_reverse_random_access_iterator ret = *this;
			ptr++;
			return ret;
		}

		bool operator==(const_reverse_random_access_iterator const &constReverseRandomAccessIterator)
		{ return (ptr == constReverseRandomAccessIterator.ptr); }

		bool operator!=(const_reverse_random_access_iterator const &constReverseRandomAccessIterator)
		{ return (ptr != constReverseRandomAccessIterator.ptr); }

		const_reverse_random_access_iterator operator+(std::ptrdiff_t n)
		{
			const_reverse_random_access_iterator temp = *this;
			return (temp -= n);
		}

		const_reverse_random_access_iterator &operator+=(std::ptrdiff_t step)
		{
			std::ptrdiff_t i = step;
			if (i >= 0)
				while (i--)
					ptr--;
			else
				while (i++)
					ptr++;
			return (*this);
		}

		const_reverse_random_access_iterator operator-(long n)
		{
			const_reverse_random_access_iterator temp = const_reverse_random_access_iterator(*this);
			return temp += n;
		}

		const_reverse_random_access_iterator &operator-=(std::ptrdiff_t n)
		{ return (*this -= -n); }

		std::ptrdiff_t operator-(const_reverse_random_access_iterator &a)
		{ return (ptr - a.ptr); }

		reference &operator[](std::ptrdiff_t n) const
		{ return (*(*this - n)); }

		const reference &operator*() const
		{ return (*(ptr)); }

		pointer *operator->() const
		{ return (ptr); }
	};

	template<bool B, class T = void>
	struct enable_if
	{
	};
	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif //FT_CONTAINERS_UTILS_HPP
