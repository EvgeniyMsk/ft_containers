//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "bidirectional_iterator.hpp"
#include "const_bidirectional_iterator.hpp"
#include "reverse_iterator.hpp"
#include "const_reverse_iterator.hpp"
#include <limits>

    // Реализация двусвязного списка (в соответствии со стандартом C++98)
    // http://www.cplusplus.com/reference/list/list/list/
using namespace ft;
namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >

	class list
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef bidirectional_iterator<T> iterator;
		typedef const_bidirectional_iterator<T> const_iterator;
		typedef reverse_iterator<T> reverse_iterator;
		typedef const_reverse_iterator<T> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
	private:
		list_t<value_type> *_front;
		list_t<value_type> *_back;
		list_t<value_type> *_end;
		size_type _length;
		allocator_type _alloc;
		std::allocator<list_t<T> > _cellAlloc;
	public:
		//  Member functions
		//  Empty container constructor (default constructor). Constructs an empty container, with no elements.
		list() : _length(0)
		{
			_end = _cellAlloc.allocate(1);
			_cellAlloc.construct(_end);
			_end->data = new T();
			_end->prev = _end;
			_end->next = _end;
			_front = _end;
			_back = _end;
		}

		//  fill constructor. Constructs a container with n elements. Each element is a copy of val.
		explicit list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
		{
			_end = _cellAlloc.allocate(1);
			_cellAlloc.construct(_end);
			_end->data = new T();
			_end->prev = _end;
			_end->next = _end;
			_alloc = alloc;
			_front = _end;
			_back = _end;
			_length = 0;
			while (n--)
				push_back(val);
		}

		//  range constructor. Constructs a container with as many elements as the range [first,last), with each element
		//  constructed from its corresponding element in that range, in the same order.
		template<class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type())
		{
			_end = _cellAlloc.allocate(1);
			_cellAlloc.construct(_end);
			_end->data = new T();
			_end->prev = _end;
			_end->next = _end;
			_front = _end;
			_back = _end;
			_length = 0;
			_alloc = alloc;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//  copy constructor. Constructs a container with a copy of each of the elements in x, in the same order.
		list(list const &list) : _length(0)
		{
			_end = _cellAlloc.allocate(1);
			_cellAlloc.construct(_end);
			_end->data = new T();
			_end->prev = _end;
			_end->next = _end;
			_front = _end;
			_back = _end;
			*this = list;
		}

		virtual ~list()
		{
			clear();
			delete (_end->data);
			_cellAlloc.destroy(_end);
			_cellAlloc.deallocate(_end, 1);
		}

		//  Iterators:
		iterator begin()
		{ return (iterator(_front)); }

		iterator end()
		{ return (iterator(_end)); }

		reverse_iterator rbegin()
		{ return (reverse_iterator(_back)); }

		reverse_iterator rend()
		{ return (reverse_iterator(_end)); }

		const_iterator begin() const
		{ return (const_iterator(_front)); }

		const_iterator end() const
		{ return (const_iterator(_end)); }

		const_reverse_iterator rbegin() const
		{ return (const_iterator(_back)); }

		const_reverse_iterator rend() const
		{ return (const_reverse_iterator(_end)); }

		//  Capacity:
		bool empty() const
		{ return (_length > 0); }

		size_type size() const
		{ return (_length); }

		size_type max_size() const
		{ return (std::numeric_limits<size_type>::max()); };

		//  Element access:
		reference front()
		{ return (*_front->data); }

		reference back()
		{ return (*_back->data); }

		const_reference front() const
		{ return (*_front->data); }

		const_reference back() const
		{ return (*_back->data); }

		//  Modifiers:
		template<class InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			while (first != last)
				push_back(*first++);
		}

		void assign(size_type n, const value_type &val)
		{
			clear();
			while (n--)
				push_back(val);
		}

		void push_front(const value_type &val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			list_t<T> *tmp;

			if (_front == _end)
				return;
			tmp = _front->next;
			_alloc.destroy(_front->data);
			_alloc.deallocate(_front->data, 1);
			_cellAlloc.destroy(_front);
			_cellAlloc.deallocate(_front, 1);
			if (tmp == _end)
			{
				_back = _end;
				_front = _end;
			} else
			{
				_front = tmp;
				_front->prev = _end;
			}
			_length--;
		}

		void push_back(const value_type &val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			list_t<T> *tmp;

			if (_back == _end)
				return;
			tmp = _back->prev;
			_alloc.destroy(_back->data);
			_alloc.deallocate(_back->data, 1);
			_cellAlloc.destroy(_back);
			_cellAlloc.deallocate(_back, 1);
			if (tmp == _end)
			{
				_front = _end;
				_back = _end;
			} else
			{
				_back = tmp;
				_back->next = _end;
				_end->prev = _back;
			}
			_length--;
		}

		iterator insert(iterator position, const value_type &val)
		{
			list_t<T> *tmp = _cellAlloc.allocate(1);
			_cellAlloc.construct(tmp);
			tmp->data = _alloc.allocate(1);
			_alloc.construct(tmp->data, val);
			tmp->next = position.getCell();
			tmp->prev = position.getCell()->prev;
			tmp->next->prev = tmp;
			tmp->prev->next = tmp;
			if (tmp->prev == _end)
				_front = tmp;
			if (tmp->next == _end)
				_back = tmp;
			_length++;
			return (iterator(tmp));
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			while (n--)
				insert(position, val);
		}

		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++)
				insert(position, *it);
		}

		iterator erase(iterator position)
		{
			list_t<T> *it = position.getCell();
			list_t<T> *next = it->next;
			list_t<T> *prev = it->prev;
			if (it == _end)
				return (iterator(this->_end));
			next->prev = prev;
			prev->next = next;
			_alloc.destroy(it->data);
			_alloc.deallocate(it->data, 1);
			_cellAlloc.destroy(it);
			_cellAlloc.deallocate(it, 1);
			if (prev == _end)
				_front = next;
			if (next == _end)
				_back = prev;
			_length--;
			return (iterator(next));
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == last)
				return last;
			while (first != last)
				first = this->erase(first);
			this->erase(first);
			if (last.getNode() == _end)
				return (iterator(_end));
			last++;
			return (iterator(last.getCell()));
		}

		void swap(list &x)
		{
			list temp(*this);
			*this = x;
			x = temp;
			delete (temp);
		}

		void resize(size_type n, value_type val = value_type())
		{
			int tmp = (int) n;
			if (tmp < 0)
				return;
			if (tmp < _length)
				while (tmp < _length)
					erase(begin());
			if (tmp > _length)
				while (tmp > _length)
					push_back(val);
		}

		void clear()
		{
			while (_front != _end)
				erase(begin());
		}

		//	Operations:
		void splice (iterator position, list& x)
		{
			for (iterator it = x.begin(); it != x.end(); it++)
				insert(position, *it);
			x.clear();
		}

		void splice (iterator position, list& x, iterator i)
		{
			for (iterator it = i; i != x.end(); it++)
				insert(position, *it);
			for (iterator it = i; i != x.end();)
				it = x.erase(it);
		}

		void splice (iterator position, list& x, iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
				insert(position, *it);
			for (iterator it = first; it != last;)
				it = x.erase(it);
		}

		void remove (const value_type& val)
		{
			for (iterator it = begin(); it != end();)
				if (val == *it)
					erase(it);
				else
					it++;
		}

		template <class Predicate>
		void remove_if (Predicate pred)
		{
			for (iterator it = begin(); it != end();)
				if (pred(*it))
					erase(it);
				else
					it++;
		}

		void unique()
		{

		}

	};
}

#endif //FT_CONTAINERS_LIST_HPP