#ifndef VECTOR_HPP
# define VECTOR_HPP
#include "utils.hpp"
// Реализация вектора (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/vector/vector/
namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
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
	public:
		//	Member functions
		//	Constructs an empty container, with no elements.
		explicit vector(const allocator_type &alloc = allocator_type()) : length(0), realLength(0)
		{
			_Alloc = alloc;
			ptr = nullptr;
		}

		//	Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
		{
			_Alloc = alloc;
			if (n > 0)
			{
				length = n;
				realLength = n;
				ptr = _Alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					ptr[i] = val;
			} else
			{
				realLength = 0;
				length = 0;
				ptr = nullptr;
			}
		}

		//	Constructs a container with as many elements as the range [first,last), with each
		//	element constructed from its corresponding element in that range, in the same order.
		template<class InputIterator>
		vector(InputIterator first, typename enable_if<std::is_class<InputIterator>::value, InputIterator>::type last,
			   const allocator_type &alloc = allocator_type())
		{
			_Alloc = alloc;
			length = 0;
			realLength = 0;
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//	Constructs a container with a copy of each of the elements in x, in the same order.
		vector(const vector &x)
		{
			_Alloc = x._Alloc;
			length = 0;
			realLength = 0;
			*this = x;
		}

		//	Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
		vector &operator=(const vector &other)
		{
			clear();
			if (other.empty())
				return (*this);
			for (const_iterator it = other.begin(); it != other.end(); it++)
				push_back(*it);
			return (*this);
		}

		//	This destroys all container elements, and deallocates all the storage capacity allocated
		//	by the vector using its allocator.
		virtual ~vector()
		{
			if (realLength > 0)
				_Alloc.deallocate(ptr, realLength);
		}

		//	Iterators
		//	Return iterator to beginning
		iterator begin()
		{ return iterator(ptr); }

		//	Return iterator to beginning
		const_iterator begin() const
		{ return iterator(ptr); }

		//	Return iterator to end
		iterator end()
		{ return iterator(ptr + length); }

		//	Return iterator to end
		const_iterator end() const
		{ return iterator(ptr + length); }

		//	Return reverse iterator to reverse beginning
		reverse_iterator rbegin()
		{ return reverse_iterator(ptr + length - 1); }

		//	Return reverse iterator to reverse beginning
		const_reverse_iterator rbegin() const
		{ return reverse_iterator(ptr + length - 1); }

		//	Return reverse iterator to reverse end
		reverse_iterator rend()
		{ return reverse_iterator(ptr - 1); }

		//	Return reverse iterator to reverse end
		const_reverse_iterator rend() const
		{ return reverse_iterator(ptr - 1); }


		//	Capacity:
		//	Return size
		size_type size() const
		{ return (length); }

		//	Return maximum size
		size_type max_size() const
		{ return std::numeric_limits<size_type>::max(); }

		//	Change size
		void resize(size_type n, value_type val = value_type())
		{
			if (length == n)
				return;
			while (length != n)
			{
				if (length > n)
					pop_back();
				else
					push_back(val);
			}
		}

		//	Return size of allocated storage capacity
		size_type capacity() const
		{ return (realLength); }

		//	Test whether vector is empty
		bool empty() const
		{ return !length ? 1 : 0; }

		//	Request a change in capacity
		void reserve(size_type n)
		{
			value_type *temp;
			if (realLength >= n)
				return;
			temp = _Alloc.allocate(n);
			for (size_type i = 0; i < length; i++)
				temp[i] = ptr[i];
			if (realLength)
				_Alloc.deallocate(ptr, realLength);
			ptr = temp;
			realLength = n;
		}

		//	Element access
		//	Access element
		reference operator[](size_type i)
		{ return (ptr[i]); }

		//	Access element
		const_reference operator[](size_type i) const
		{ return (ptr[i]); }

		//	Access element
		reference at(size_type n)
		{
			if (n >= length)
				throw std::out_of_range("Out of range");
			return (ptr[n]);
		}

		//	Access element
		const_reference at(size_type n) const
		{ return (at(n)); }

		//	Access first element
		reference front()
		{ return (ptr[0]); }

		//	Access first element
		const_reference front() const
		{ return (ptr[0]); }

		//	Access last element
		reference back()
		{ return (ptr[length - 1]); }

		//	Access last element
		const_reference back() const
		{ return (ptr[length - 1]); }

		//	Modifiers:
		//	In the range version (1), the new contents are elements constructed from each of the elements
		//	in the range between first and last, in the same order.
		template<class InputIterator>
		void
		assign(InputIterator first, typename enable_if<std::is_class<InputIterator>::value, InputIterator>::type last)
		{
			clear();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		//	In the fill version (2), the new contents are n elements, each initialized to a copy of val.
		void assign(size_type n, const value_type &val)
		{
			clear();
			while (n--)
				push_back(val);
		}

		//	Add element at the end
		void push_back(const value_type &val)
		{
			if (length >= realLength)
				reserve(realLength + 50);
			ptr[length] = val;
			length++;
		}

		//	Delete last element
		void pop_back()
		{
			if (length)
				--length;
			if (realLength - length > 50)
			{
				pointer temp = _Alloc.allocate(realLength - 50);
				for (size_type i = 0; i < length; i++)
					temp[i] = ptr[i];
				_Alloc.deallocate(ptr, realLength);
				ptr = temp;
				realLength = realLength - 50;
			}
		}

		//	Insert elements
		iterator insert(iterator position, const value_type &val)
		{
			iterator begin = this->begin();
			size_type start = position - begin;
			size_type finish = this->length - start;
			size_type n = 1;
			if (length + n > realLength)
				reserve(realLength + n);
			for (size_type i = 0; i < finish; i++)
				ptr[(length + n - 1) - i] = ptr[(finish - 1) - i];
			for (size_type i = 0; i < n; i++)
				ptr[start + i] = val;
			length = length + n;
			return (iterator(ptr + start));
		}

		//	Insert elements
		void insert(iterator position, size_type n, const value_type &val)
		{
			iterator begin = this->begin();
			size_type start = position - begin;
			size_type tail = length - start;
			if (n == 0)
				return;
			if (length + n > realLength)
				reserve(realLength + n);
			for (size_type i = 0; i < tail; i++)
				ptr[(length + n - 1) - i] = ptr[(tail - 1) - i];
			for (size_type i = 0; i < n; i++)
				ptr[start + i] = val;
			length = length + n;
		}

		//	Insert elements
		template<class InputIterator>
		void insert(iterator position, InputIterator first,
					typename enable_if<std::is_class<InputIterator>::value, InputIterator>::type last)
		{
			iterator begin = this->begin();
			size_type start = position - begin;
			size_type finish = length - start;
			InputIterator it = first;
			size_type n = 0;
			while (it != last)
			{
				n++;
				it++;
			}
			if (n == 0)
				return;
			if (length + n > realLength)
				reserve(realLength + n);
			for (size_type i = 0; i < finish; i++)
				ptr[(length + n - 1) - i] = ptr[(finish - 1) - i];
			for (size_type i = 0; i < n; i++)
			{
				ptr[start + i] = *first;
				first++;
			}
			length = length + n;
		}

		//	Erase elements
		iterator erase(iterator position)
		{
			iterator end = this->end();
			iterator result = position;
			while (position != end)
			{
				if (position + 1 != end)
					*position = *(position + 1);
				++position;
			}
			length--;
			return (result);
		}

		//	Erase elements
		iterator erase(iterator first, iterator last)
		{
			iterator end = this->end();
			iterator result = (first == this->begin() ? first : first - 1);
			size_type difference = last - first;
			if (difference == length)
			{
				length = 0;
				return (last);
			}
			while (last != end)
			{
				*first = *last;
				last++;
				first++;
			}
			length -= difference;
			return (result);
		}

		//	Swap content
		void swap(vector &x)
		{
			value_type *valueType_temp = ptr;
			ptr = x.ptr;
			x.ptr = valueType_temp;
			size_type sizetype_temp = realLength;
			realLength = x.realLength;
			x.realLength = sizetype_temp;
			sizetype_temp = length;
			length = x.length;
			x.length = sizetype_temp;
			allocator_type allocatortype_temp = _Alloc;
			_Alloc = x._Alloc;
			x._Alloc = allocatortype_temp;
		}

		//	Clear content
		void clear()
		{
			if (length == 0)
				return;
			_Alloc.deallocate(ptr, realLength);
			ptr = nullptr;
			length = 0;
			realLength = 0;
		}

		friend void swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs)
		{
			lhs.swap(rhs);
		}

		friend bool operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);
			if (lhs.size() == 0 && rhs.size() == 0)
				return (true);
			typename ft::vector<T>::const_iterator beginLhs = lhs.begin();
			typename ft::vector<T>::const_iterator beginRhs = rhs.begin();
			typename ft::vector<T>::const_iterator endLhs = lhs.end();
			typename ft::vector<T>::const_iterator endRhs = rhs.end();
			while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
			{
				beginLhs++;
				beginRhs++;
			}
			return beginLhs == endLhs && beginRhs == endRhs;
		}

		friend bool operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		{
			return (!(lhs == rhs));
		}

		friend bool operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		{
			if (lhs.size() < rhs.size())
				return (true);
			if (lhs.size() > rhs.size() || (lhs.size() == 0 && rhs.size() == 0))
				return (false);
			typename ft::vector<T>::const_iterator beginLhs = lhs.begin();
			typename ft::vector<T>::const_iterator beginRhs = rhs.begin();
			typename ft::vector<T>::const_iterator endLhs = lhs.end();
			typename ft::vector<T>::const_iterator endRhs = rhs.end();

			while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
			{
				beginLhs++;
				beginRhs++;
			}
			return !((beginLhs == endLhs && beginRhs == endRhs) || beginRhs == endRhs || *beginLhs >= *beginRhs);
		}

		friend bool operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		{
			return (lhs < rhs || lhs == rhs);
		}

		friend bool operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs){
			if (lhs.size() > rhs.size())
				return (true);
			if (lhs.size() < rhs.size() || (lhs.size() == 0 && rhs.size() == 0))
				return (false);
			typename ft::vector<T>::const_iterator beginLhs = lhs.begin();
			typename ft::vector<T>::const_iterator  beginRhs = rhs.begin();
			typename ft::vector<T>::const_iterator  endLhs = lhs.end();
			typename ft::vector<T>::const_iterator  endRhs = rhs.end();

			while (beginLhs != endLhs && beginRhs != endRhs && *beginLhs == *beginRhs)
			{
				beginLhs++;
				beginRhs++;
			}
			return !((beginLhs == endLhs && beginRhs == endRhs) || beginLhs == endLhs || *beginLhs <= *beginRhs);
		}

		friend bool operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
		{
			return (lhs > rhs || lhs == rhs);
		}
	};
}

#endif