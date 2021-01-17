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
			_end->previous = _end;
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
			_end->previous = _end;
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
			_end->previous = _end;
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
			_end->previous = _end;
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

		list &operator=(const list &x) {
			this->clear();
			if (x.empty())
				return (*this);
			for (const_iterator it = x.begin(); it != x.end(); it++)
				this->push_back(*it);
			return (*this);
		}

		//  Iterators:
		//	Return iterator to beginning
		iterator begin()
		{ return (iterator(_front)); }

		//	Return iterator to end
		iterator end()
		{ return (iterator(_end)); }

		//	Return reverse iterator to reverse beginning
		reverse_iterator rbegin()
		{ return (reverse_iterator(_back)); }

		//	Return reverse iterator to reverse end
		reverse_iterator rend()
		{ return (reverse_iterator(_end)); }

		//	Return const_iterator to beginning
		const_iterator begin() const
		{ return (const_iterator(_front)); }

		//	Return const_iterator to end
		const_iterator end() const
		{ return (const_iterator(_end)); }

		//	Return reverse iterator to reverse beginning
		const_reverse_iterator rbegin() const
		{ return (const_iterator(_back)); }

		//	Return reverse iterator to reverse end
		const_reverse_iterator rend() const
		{ return (const_reverse_iterator(_end)); }

		//  Capacity:
		//	Test whether container is empty
		bool empty() const
		{ return _length == 0; }

		//	Return size
		size_type size() const
		{ return (_length); }

		//	Return maximum size
		size_type max_size() const
		{ return (std::numeric_limits<size_type>::max()); };

		//  Element access:
		//	Access first element
		reference front()
		{ return (*_front->data); }

		//	Access last element
		reference back()
		{ return (*_back->data); }

		//	Access first element
		const_reference front() const
		{ return (*_front->data); }

		//	Access last element
		const_reference back() const
		{ return (*_back->data); }

		//  Modifiers:
		template<class InputIterator>
		//	Assign new content to container
		void assign(InputIterator first, InputIterator last)
		{
			clear();
			while (first != last)
				push_back(*first++);
		}

		//	Assign new content to container
		void assign(size_type n, const value_type &val)
		{
			clear();
			while (n--)
				push_back(val);
		}

		//	Insert element at beginning
		void push_front(const value_type &val)
		{
			insert(begin(), val);
		}

		//	Delete first element
		void pop_front()
		{
			list_t<T> *temp;

			if (_front == _end)
				return;
			temp = _front->next;
			_alloc.destroy(_front->data);
			_alloc.deallocate(_front->data, 1);
			_cellAlloc.destroy(_front);
			_cellAlloc.deallocate(_front, 1);
			if (temp == _end)
			{
				_back = _end;
				_front = _end;
			} else
			{
				_front = temp;
				_front->previous = _end;
			}
			_length--;
		}

		//	Add element at the end
		void push_back(const value_type &val)
		{
			size_type i = _length;
			iterator it = begin();
			while (i--)
				it++;
			insert(it, val);
		}

		//	Delete last element
		void pop_back()
		{
			list_t<T> *temp;

			if (_back == _end)
				return;
			temp = _back->previous;
			_alloc.destroy(_back->data);
			_alloc.deallocate(_back->data, 1);
			_cellAlloc.destroy(_back);
			_cellAlloc.deallocate(_back, 1);
			if (temp == _end)
			{
				_front = _end;
				_back = _end;
			} else
			{
				_back = temp;
				_back->next = _end;
				_end->previous = _back;
			}
			_length--;
		}

		//	Insert elements
		iterator insert(iterator position, const value_type &val)
		{
			list_t<T> *temp = _cellAlloc.allocate(1);
			_cellAlloc.construct(temp);
			temp->data = _alloc.allocate(1);
			_alloc.construct(temp->data, val);
			temp->next = position.getCell();
			temp->previous = position.getCell()->previous;
			temp->next->previous = temp;
			temp->previous->next = temp;
			if (temp->previous == _end)
				_front = temp;
			if (temp->next == _end)
				_back = temp;
			_length++;
			return (iterator(temp));
		}

		//	Insert elements
		void insert(iterator position, size_type n, const value_type &val)
		{
			while (n--)
				insert(position, val);
		}

		//	Insert elements
		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last)
		{
			for (InputIterator it = first; it != last; it++)
				insert(position, *it);
		}

		//	Erase elements
		iterator erase(iterator position)
		{
			list_t<T> *it = position.getCell();
			list_t<T> *next = it->next;
			list_t<T> *previous = it->previous;
			if (it == _end)
				return (iterator(_end));
			next->previous = previous;
			previous->next = next;
			_alloc.destroy(it->data);
			_alloc.deallocate(it->data, 1);
			_cellAlloc.destroy(it);
			_cellAlloc.deallocate(it, 1);
			if (previous == _end)
				_front = next;
			if (next == _end)
				_back = previous;
			_length--;
			return (iterator(next));
		}

		//	Erase elements
		iterator erase(iterator first, iterator last)
		{
			if (first == last)
				return last;
			while (first != last)
				first = this->erase(first);
			this->erase(first);
			if (last.getCell() == _end)
				return (iterator(_end));
			last++;
			return (iterator(last.getCell()));
		}

		//	Swap content
		void swap(list &x)
		{
			list_t<T> *temp;
			size_type length;
			allocator_type allocator;
			temp = x._back;
			x._back = _back;
			_back = temp;

			temp = x._front;
			x._front = _front;
			_front = temp;

			temp = x._end;
			x._end = _end;
			_end = temp;

			length = x._length;
			x._length = _length;
			_length = length;

			allocator = x._alloc;
			x._alloc = _alloc;
			_alloc = allocator;
		}

		//	Change size
		void resize(size_type n, value_type val = value_type())
		{
			int temp = (int) n;
			if (temp < 0)
				return;
			if (temp < _length)
				while (temp < _length)
					erase(begin());
			if (temp > _length)
				while (temp > _length)
					push_back(val);
		}

		//	Clear content
		void clear()
		{
			while (_front != _end)
				erase(begin());
		}

		//	Operations:
		void splice(iterator position, list &x)
		{
			for (iterator it = x.begin(); it != x.end(); it++)
				insert(position, *it);
			x.clear();
		}

		//	Transfer elements from list to list
		void splice(iterator position, list &x, iterator i)
		{
			insert(position, *i);
		}

		//	Transfer elements from list to list
		void splice(iterator position, list &x, iterator first, iterator last)
		{
			for (iterator it = first; it != last; it++)
				insert(position, *it);
			for (iterator it = first; it != last;)
				it = x.erase(it);
		}

		//	Remove elements with specific value
		void remove(const value_type &val)
		{
			for (iterator it = begin(); it != end();)
				if (val == *it)
					erase(it);
				else
					it++;
		}

		//	Remove elements fulfilling condition
		template<class Predicate>
		void remove_if(Predicate pred)
		{
			for (iterator it = begin(); it != end();)
				if (pred(*it))
					erase(it);
				else
					it++;
		}

		//	Remove duplicate values
		void unique()
		{
			iterator begin = this->begin();
			iterator end = this->end();
			T *temp = nullptr;

			while (begin != end)
			{
				if (temp && *temp == *begin)
					begin = erase(begin);
				else
				{
					temp = &(*begin);
					begin++;
				}
			}
		}

		template<class BinaryPredicate>
		//	Remove duplicate values
		void unique(BinaryPredicate binary_pred)
		{
			iterator begin = this->begin();
			iterator current = this->begin();
			iterator end = this->end();

			while (++current != end)
			{
				if (p(*begin, *current))
				{
					erase(current);
					current = begin;
				} else
					begin++;
			}
		}

		//	Merge sorted lists
		void merge(list &x)
		{
			iterator begin = this->begin();
			iterator end = this->end();
			iterator beginX = x.begin();
			iterator endX = x.end();
			iterator next;
			while (x._length)
			{
				if (*beginX < *begin || begin == endX)
				{
					next = beginX;
					next++;
					splice(begin, x, beginX);
					beginX = next;
				} else
					begin++;
			}
		}

		template<class Compare>
		//	Merge sorted lists
		void merge(list &x, Compare comp)
		{
			iterator begin = this->begin();
			iterator end = this->end();
			iterator beginComp = comp.begin();
			iterator endComp = comp.end();
			iterator next;
			while (comp._length)
			{
				if (comp(*beginComp, *begin) || begin == endComp)
				{
					next = beginComp;
					next++;
					splice(begin, comp, beginComp);
					beginComp = next;
				} else
					begin++;
			}
		}

		//	Sort elements in container
		void sort()
		{

			iterator begin = this->begin();
			iterator it = this->begin();
			iterator end = this->end();
			T *temp;

			while (++it != end)
			{
				if (*it < *begin)
				{
					temp = begin.getCell()->data;
					begin.getCell()->data = it.getCell()->data;
					it.getCell()->data = temp;
					begin = this->begin();
					it = this->begin();
				} else
					begin++;
			}
		}

		template<class Compare>
		//	Sort elements in container
		void sort(Compare comp)
		{

			iterator begin = this->begin();
			iterator beginComp = this->begin();
			iterator end = this->end();
			T *temp;
			while (++beginComp != end)
			{
				if (comp(*beginComp, *begin))
				{
					temp = begin.getCell()->data;
					begin.getCell()->data = beginComp.getCell()->data;
					beginComp.getCell()->data = temp;
					begin = this->begin();
					beginComp = this->begin();
				} else
					begin++;
			}
		}

		//	Reverse the order of elements
		void reverse()
		{
			iterator first = this->begin();
			iterator last = this->end();
			while ((first != last) && (first != --last))
			{
				std::swap(*first++, *last);
			}
		}
	};

	//	Exchanges the contents of two lists
	template<class T, class Alloc>
	void swap(list<T, Alloc> &x, list<T, Alloc> &y)
	{
		x.swap(y);
	}

	//	Non-member function overloads. Relational operators for list.
	template<class T, class Alloc>
	bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		ft::const_bidirectional_iterator<T> beginLhs = lhs.begin();
		ft::const_bidirectional_iterator<T> beginRhs = rhs.begin();
		ft::const_bidirectional_iterator<T> endLhs = lhs.end();
		ft::const_bidirectional_iterator<T> endRhs = rhs.end();
		while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
		{
			beginLhs++;
			beginRhs++;
		}
		return beginLhs == endLhs && beginRhs == endRhs;
	}

	template<class T, class Alloc>
	bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return (!(lhs == rhs));
	}

	template<class T, class Alloc>
	bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		if (lhs.size() < rhs.size())
			return (true);
		if (lhs.size() > rhs.size())
			return (false);
		ft::const_bidirectional_iterator<T> beginLhs = lhs.begin();
		ft::const_bidirectional_iterator<T> beginRhs = rhs.begin();
		ft::const_bidirectional_iterator<T> endLhs = lhs.end();
		ft::const_bidirectional_iterator<T> endRhs = rhs.end();
		while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
		{
			beginLhs++;
			beginRhs++;
		}
		return !((beginLhs == endLhs && beginRhs == endRhs) || beginRhs == endRhs || *beginLhs >= *beginRhs);
	}

	template<class T, class Alloc>
	bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template<class T, class Alloc>
	bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return !((lhs < rhs) || (lhs == rhs));
	}

	template<class T, class Alloc>
	bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs)
	{
		return ((lhs > rhs) || (lhs == rhs));
	}
}

#endif //FT_CONTAINERS_LIST_HPP
