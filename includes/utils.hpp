/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:42:44 by qsymond           #+#    #+#             */
/*   Updated: 2021/01/25 13:45:58 by qsymond          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP

#include <memory>
#include <iostream>
#include <limits>

	template<typename T>
	struct list_t
	{
		T *data;
		struct list_t *next;
		struct list_t *previous;
	};

	template<class Key_type, class Value_type>
	struct cell_t
	{
		cell_t *parent;
		cell_t *previous;
		cell_t *next;
		bool end;
		std::pair<const Key_type, Value_type> *value;
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

		explicit bidirectional_iterator(list_t<T>
										*ptr) : _ptr(ptr)
		{}

		bidirectional_iterator(bidirectional_iterator const &bidirectionalIterator) : _ptr(
				bidirectionalIterator._ptr)
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

		explicit const_bidirectional_iterator(list_t<T>
											  *ptr) : _ptr(ptr)
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

		explicit reverse_iterator(list_t<T>
								  *ptr) : _ptr(ptr)
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

		explicit const_reverse_iterator(list_t<T>
										*ptr) : _ptr(ptr)
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

		random_access_iterator(
				const random_access_iterator &randomAccessIterator)
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

		explicit const_random_access_iterator(T
											  *p) : ptr(p)
		{}

		const_random_access_iterator(
				const const_random_access_iterator &constRandomAccessIterator)
		{ *this = constRandomAccessIterator; }

		const_random_access_iterator(
				const random_access_iterator<T> &randomAccessIterator)
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

		reverse_random_access_iterator(
				const reverse_random_access_iterator &reverseRandomAccessIterator)
		{ *this = reverseRandomAccessIterator; }

		reverse_random_access_iterator &operator=(const reverse_random_access_iterator &reverseRandomAccessIterator)
		{
			ptr = reverseRandomAccessIterator.ptr;
			return (*this);
		}

		virtual ~reverse_random_access_iterator()
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

		const_reverse_random_access_iterator(
				const const_reverse_random_access_iterator &constReverseRandomAccessIterator)
		{ *this = constReverseRandomAccessIterator; }

		const_reverse_random_access_iterator(
				const reverse_random_access_iterator<T> &reverseRandomAccessIterator)
		{ *this = reverseRandomAccessIterator; }

		const_reverse_random_access_iterator &
		operator=(const const_reverse_random_access_iterator &constReverseRandomAccessIterator)
		{
			ptr = constReverseRandomAccessIterator.ptr;
			return (*this);
		}

		const_reverse_random_access_iterator &
		operator=(const reverse_random_access_iterator<T> &reverseRandomAccessIterator)
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

	template<class Key, class T, class Compare, class Alloc = std::allocator<std::pair<const Key, T> > >
	class Cell
	{
	public:
		typedef cell_t<Key, T> _self;
		typedef Key key_type;
		typedef T mapped_type;
		typedef Alloc allocator_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare value_compare;
		typedef const value_type &const_reference;
		typedef _self *pointer;

	private:
		pointer _base;
		pointer _rend;
		pointer _end;
		allocator_type _alloc;
		value_compare _cmp;

	public:
		Cell()
		{
			_end = endCell(nullptr);
			_rend = endCell(nullptr);
			_base = nullptr;
		}

		Cell(
				const allocator_type &alloc)
		{
			_alloc = alloc;
			_end = endCell(nullptr);
			_rend = endCell(nullptr);
			_base = nullptr;
		}

		Cell(value_type *val)
		{
			_base = newCell(val);
			_end = endCell(nullptr);
			_rend = endCell(nullptr);
			_base->previous = _end;
			_base->next = _end;

		}

		Cell &operator=(const Cell &x)
		{
			_base = x._base;
			_alloc = x._alloc;
			_cmp = x._cmp;
			if (_base)
			{
				cell_set_rend();
				cell_set_end();
			}
			return (*this);
		}

		virtual ~Cell()
		{
			cell_clear();
			_alloc.deallocate(_end->value, 1);
			delete _end;
			_alloc.deallocate(_rend->value, 1);
			delete _rend;
		}

		pointer newCell(const_reference val)
		{
			pointer temp = new _self;
			temp->value = _alloc.allocate(1);
			_alloc.construct(temp->value, val);
			temp->parent = nullptr;
			temp->previous = nullptr;
			temp->next = nullptr;
			temp->end = false;
			return (temp);

		}

		pointer endCell(pointer par)
		{
			pointer temp = new _self;
			temp->value = _alloc.allocate(1);
			temp->parent = par;
			temp->previous = nullptr;
			temp->next = nullptr;
			temp->end = true;
			return temp;
		}

		void cell_set_rend()
		{
			cell_min()->previous = _rend;
			_rend->parent = cell_min();
		}

		void cell_set_end()
		{
			cell_max()->next = _end;
			_end->parent = cell_max();
		}

		pointer cell_add(const_reference value, pointer root = nullptr)
		{
			if (cell_search(value))
				return nullptr;
			pointer temp = newCell(value);
			if (_base == 0 || _base->end)
			{
				_base = temp;
				_base->previous = _rend;
				_rend->parent = _base;
				_base->next = _end;
				_end->parent = _base;
				return (temp);
			}
			if (!root)
				root = _base;
			while (root != nullptr && !root->end)
			{
				if (!_cmp(temp->value->first, root->value->first))
				{
					if (root->next != nullptr && !root->next->end)
						root = root->next;
					else
					{
						temp->parent = root;
						root->next = temp;
						break;
					}
				} else if (_cmp(temp->value->first, root->value->first))
				{
					if (root->previous != nullptr && !root->previous->end)
						root = root->previous;
					else
					{
						temp->parent = root;
						root->previous = temp;
						break;
					}
				}
			}
			cell_set_rend();
			cell_set_end();
			return (temp);
		}

		pointer cell_min(pointer root = nullptr, bool fst = true) const
		{
			if (fst && !root)
				root = _base;
			if (root->previous == nullptr || root->previous->end)
				return root;
			return (cell_min(root->previous, false));
		}

		pointer cell_max(pointer root = nullptr, bool fst = true) const
		{
			if (fst && !root)
				root = _base;
			if (root->next == nullptr || root->next->end)
				return root;
			return (cell_max(root->next, false));
		}

		pointer cell_search(const_reference val, pointer root = nullptr, bool fst = false)
		{
			if (!fst)
				root = _base;
			if (root == nullptr || root->end)
				return (nullptr);
			if (val.first == root->value->first)
				return (root);
			if (_cmp(val.first, root->value->first))
				return (cell_search(val, root->previous, true));
			else
				return (cell_search(val, root->next, true));
		}

		pointer cell_search(key_type key, pointer root = nullptr, bool fst = false) const
		{
			if (!fst)
				root = _base;
			if (root == nullptr || root->end)
				return (nullptr);
			if (key == root->value->first)
				return (root);
			if (_cmp(key, root->value->first))
				return (cell_search(key, root->previous, true));
			else
				return (cell_search(key, root->next, true));
		}

		pointer cell_delete(pointer root, const key_type key)
		{
			pointer tmp;
			if (root == nullptr || root->end)
				return root;
			if (_cmp(key, root->value->first))
				root->previous = cell_delete(root->previous, key);
			else if (!_cmp(key, root->value->first) && key != root->value->first)
				root->next = cell_delete(root->next, key);
			else if (root->previous != nullptr && !root->previous->end && root->next != nullptr && !root->next->end)
			{
				_alloc.destroy(root->value);
				_alloc.deallocate(root->value, 1);
				root->value = _alloc.allocate(1);
				_alloc.construct(root->value, *cell_min(root->next)->value);
				root->next = cell_delete(root->next, root->value->first);
			} else if (root->previous != nullptr && !root->previous->end)
			{
				if (_base == root)
					_base = root->previous;
				tmp = root->previous;
				root->previous->parent = root->parent;
				_alloc.destroy(root->value);
				_alloc.deallocate(root->value, 1);
				delete root;
				root = tmp;
			} else if (root->next != nullptr && !root->next->end)
			{
				if (_base == root)
					_base = root->next;
				tmp = root->next;
				root->next->parent = root->parent;
				_alloc.destroy(root->value);
				_alloc.deallocate(root->value, 1);
				delete root;
				root = tmp;
			} else
			{
				if (_base == root)
					_base = nullptr;
				if (root->previous)
					root->previous->parent = root->parent;
				if (root->next)
					root->next->parent = root->parent;
				_alloc.destroy(root->value);
				_alloc.deallocate(root->value, 1);
				delete root;
				root = nullptr;
			}
			return (root);
		}

		pointer cell_increment(pointer root)
		{
			Key k;
			if (root && root->end)
				return root->parent;
			if (!root || root->end)
				return root;
			if (root->next)
			{
				root = root->next;
				while (root->previous)
					root = root->previous;
			} else if (root->parent && root == root->parent->previous)
				root = root->parent;
			else if (!root->next)
			{
				k = root->value->first;
				while (root->parent)
				{
					root = root->parent;
					if (_cmp(k, root->value->first))
						break;
				}
				if (!root->parent && !_cmp(k, root->value->first))
					root = root->next;
			} else
				root = root->next;
			return (root);
		}

		pointer cell_decrement(pointer root)
		{
			Key k;
			if (root && root->end)
				return root->parent;
			if (!root || root->end)
				return root;
			if (root->previous)
			{
				root = root->previous;
				while (root->next)
					root = root->next;
			} else if (root->parent && root == root->parent->next)
				root = root->parent;
			else if (!root->previous)
			{
				k = root->value->first;
				while (root->parent)
				{
					root = root->parent;
					if (!_cmp(k, root->value->first))
						break;
				}
				if (!root->parent && _cmp(k, root->value->first))
					root = root->previous;
			} else
				root = root->previous;
			return (root);
		}

		pointer getBase() const
		{ return _base; }

		void setBase(pointer x)
		{
			_base = x;
			cell_set_rend();
			cell_set_end();
		}

		pointer getRend() const
		{ return _rend; }

		pointer getend() const
		{ return _end; }

		void cell_print_inorder(pointer x)
		{
			if (x != nullptr && !x->end)
			{
				cell_print_inorder(x->previous);
				std::cout << x->value->first << " ";
				cell_print_inorder(x->next);
			}
		}

		void cell_clear(pointer root = nullptr, bool fst = true)
		{
			if (fst)
			{
				root = _base;
				_base = nullptr;
			}
			if (root && !root->end)
			{
				cell_clear(root->previous, false);
				cell_clear(root->next, false);
				_alloc.destroy(root->value);
				_alloc.deallocate(root->value, 1);
				delete root;
			}
		}
	};

	template<class Key, class T, class Compare>
	class map_iterator
	{
	private:
		Cell<Key, T, Compare> base;
		cell_t<Key, T> *ptr;
	public:
		map_iterator() : ptr(nullptr)
		{}

		map_iterator(cell_t<Key, T> *p) : ptr(p)
		{}

		map_iterator(
				const map_iterator &iter)
		{ *this = iter; }

		map_iterator &operator=(const map_iterator &mapIterator)
		{
			ptr = mapIterator.ptr;
			return (*this);
		}

		virtual ~map_iterator()
		{}

		map_iterator &operator++()
		{
			ptr = base.cell_increment(ptr);
			return (*this);
		}

		const map_iterator operator++(int)
		{

			map_iterator ret = map_iterator(*this);
			ptr = base.cell_increment(ptr);
			return (ret);
		}

		map_iterator &operator--()
		{
			ptr = base.cell_decrement(ptr);
			return (*this);
		}

		const map_iterator operator--(int)
		{
			map_iterator ret = map_iterator(*this);
			ptr = base.cell_decrement(ptr);
			return (ret);
		}

		bool operator==(const map_iterator &mapIterator)
		{
			return (ptr == mapIterator.ptr);
		}

		bool operator!=(const map_iterator &mapIterator)
		{
			return (ptr != mapIterator.ptr);
		}

		bool operator!=(const map_iterator &mapIterator) const
		{
			return (ptr != mapIterator.ptr);
		}

		std::pair<const Key, T> &operator*()
		{
			return (*ptr->value);
		}

		std::pair<const Key, T> *operator->()
		{
			return (ptr->value);
		}

		cell_t<Key, T> *getCell() const
		{
			return ptr;
		}
	};

	template<class Key, class T, class Compare>
	class const_map_iterator
	{
	private:
		Cell<Key, T, Compare> base;
		cell_t<Key, T> *ptr;
	public:
		const_map_iterator() : ptr(nullptr)
		{}

		const_map_iterator(cell_t<Key, T> *p) : ptr(p)
		{}

		const_map_iterator(
				const const_map_iterator &constMapIterator)
		{ *this = constMapIterator; }

		const_map_iterator(
				const map_iterator<Key, T, Compare> &mapIterator)
		{ *this = mapIterator; }

		const_map_iterator &operator=(const const_map_iterator &constMapIterator)
		{
			ptr = constMapIterator.ptr;
			return (*this);
		}

		const_map_iterator &operator=(const map_iterator<Key, T, Compare> &mapIterator)
		{
			ptr = mapIterator.getCell();
			return (*this);
		}

		virtual ~const_map_iterator()
		{}

		const_map_iterator &operator++()
		{
			ptr = base.cell_increment(ptr);
			return (*this);
		}

		const const_map_iterator operator++(int)
		{
			const_map_iterator ret = *this;
			ptr = base.cell_increment(ptr);
			return (ret);
		}

		const_map_iterator &operator--()
		{
			ptr = base.cell_decrement(ptr);
			return (*this);
		}

		const const_map_iterator operator--(int)
		{
			const_map_iterator ret = *this;
			ptr = base.cell_decrement(ptr);
			return (ret);
		}

		bool operator==(const const_map_iterator &constMapIterator)
		{
			return (ptr == constMapIterator.ptr);
		}

		bool operator!=(const const_map_iterator &constMapIterator)
		{
			return (ptr != constMapIterator.ptr);
		}

		bool operator!=(const const_map_iterator &constMapIterator) const
		{
			return (ptr != constMapIterator.ptr);
		}

		const std::pair<const Key, T> &operator*()
		{
			return (*(ptr->value));
		}

		std::pair<const Key, T> *operator->()
		{
			return (ptr->value);
		}
	};

	template<class Key, class T, class Compare>
	class reverse_map_iterator
	{
	private:
		Cell<Key, T, Compare> base;
		cell_t<Key, T> *ptr;
	public:
		reverse_map_iterator(cell_t<Key, T> *p) : ptr(p)
		{};

		reverse_map_iterator(
				const reverse_map_iterator &iter)
		{
			*this = iter;
		}

		reverse_map_iterator &operator=(const reverse_map_iterator &reverseMapIterator)
		{
			ptr = reverseMapIterator.ptr;
			return (*this);
		}

		virtual ~reverse_map_iterator()
		{};

		reverse_map_iterator &operator++()
		{
			ptr = base.cell_decrement(ptr);
			return (*this);
		}

		const reverse_map_iterator operator++(int)
		{
			reverse_map_iterator ret = *this;
			ptr = base.cell_decrement(ptr);
			return ret;
		}

		reverse_map_iterator &operator--()
		{
			ptr = base.cell_increment(ptr);
			return (*this);
		}

		const reverse_map_iterator operator--(int)
		{
			reverse_map_iterator ret = *this;
			ptr = base.cell_increment(ptr);
			return ret;
		}

		bool operator==(const reverse_map_iterator &reverseMapIterator)
		{
			return (ptr == reverseMapIterator.ptr);
		}

		bool operator!=(const reverse_map_iterator &reverseMapIterator)
		{
			return (ptr != reverseMapIterator.ptr);
		}

		std::pair<const Key, T> &operator*()
		{
			return (*ptr->value);
		}

		std::pair<const Key, T> *operator->()
		{
			return (ptr->value);
		}

		cell_t<Key, T> *getCell() const
		{
			return ptr;
		}
	};

	template<class Key, class T, class Compare>
	class const_reverse_map_iterator
	{
	private:
		Cell<Key, T, Compare> base;
		cell_t<Key, T> *ptr;
	public:
		const_reverse_map_iterator(cell_t<Key, T> *p) : ptr(p)
		{};

		const_reverse_map_iterator(
				const const_reverse_map_iterator &constReverseMapIterator)
		{
			*this = constReverseMapIterator;
		}

		const_reverse_map_iterator(
				const reverse_map_iterator<Key, T, Compare> &reverseMapIterator)
		{
			*this = reverseMapIterator;
		}

		const_reverse_map_iterator &operator=(const const_reverse_map_iterator &constReverseMapIterator)
		{
			ptr = constReverseMapIterator.ptr;
			return (*this);
		}

		const_reverse_map_iterator &operator=(const reverse_map_iterator<Key, T, Compare> &reverseMapIterator)
		{
			ptr = reverseMapIterator.getCell();
			return (*this);
		}

		virtual ~const_reverse_map_iterator()
		{};

		const_reverse_map_iterator &operator++()
		{
			ptr = base.cell_decrement(ptr);
			return (*this);
		}

		const const_reverse_map_iterator operator++(int)
		{
			const_reverse_map_iterator ret = *this;
			ptr = base.cell_decrement(ptr);
			return ret;
		}

		const_reverse_map_iterator &operator--()
		{
			ptr = base.cell_increment(ptr);
			return (*this);
		}

		const const_reverse_map_iterator operator--(int)
		{
			const_reverse_map_iterator ret = *this;
			ptr = base.cell_increment(ptr);
			return ret;
		}

		bool operator==(const const_reverse_map_iterator &constReverseMapIterator)
		{
			return (ptr == constReverseMapIterator.ptr);
		}

		bool operator!=(const const_reverse_map_iterator &constReverseMapIterator)
		{
			return (ptr != constReverseMapIterator.ptr);
		}

		const std::pair<const Key, T> &operator*()
		{
			return (*ptr->value);
		}

		std::pair<const Key, T> *operator->()
		{
			return (ptr->value);
		}
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

#endif
