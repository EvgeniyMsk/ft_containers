#ifndef MAP_HPP
#define MAP_HPP
#include "utils.hpp"
// Реализация упорядоченного ассоциативного контейнера (в соответствии со стандартом C++98)
// http://www.cplusplus.com/reference/map/map/
namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef map_iterator<Key, T, Compare> iterator;
		typedef const_map_iterator<Key, T, Compare> const_iterator;
		typedef reverse_map_iterator<Key, T, Compare> reverse_iterator;
		typedef const_reverse_map_iterator<Key, T, Compare> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;
	private :
		Cell<key_type, mapped_type, key_compare, allocator_type> cell;
		allocator_type _alloc;
		size_type _size;
		key_compare _key_compare;

		template<class Cmp>
		class value_cmp
		{
			friend class map;

		protected:
			Cmp comp;
			value_cmp(Cmp c) : comp(c)
			{}
		public:
			typedef bool result_type;
			typedef std::pair<const Key, T> first_argument_type;
			typedef std::pair<const Key, T> second_argument_type;

			bool operator()(const first_argument_type &x, const second_argument_type &y) const
			{
				return comp(x.first, y.first);
			}
		};

	public:
		typedef value_cmp<key_compare> value_compare;

		//	Member functions
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
				cell(alloc), _alloc(alloc), _key_compare(comp)
		{
			_size = 0;
		}

		template<class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type()) : cell(alloc), _alloc(alloc), _key_compare(comp)
		{
			_key_compare = comp;
			_size = 0;
			_alloc = alloc;
			insert(first, last);
		}

		map(const map &x)
		{
			*this = x;
		}

		map &operator=(const map &other)
		{
			clear();
			_key_compare = other._key_compare;
			_alloc = other._alloc;
			const_iterator begin = other.begin();
			const_iterator end = other.end();
			while (begin != end)
			{
				insert(*begin);
				++begin;
			}
			return (*this);
		}

		virtual ~map()
		{};

		//	Iterators
		//	Return iterator to beginning
		iterator begin()
		{
			if (!_size)
				return (end());
			return iterator(cell.cell_min());
		}

		//	Return iterator to beginning
		const_iterator begin() const
		{
			if (!_size)
				return (end());
			return const_iterator(cell.cell_min());
		}

		//	Return iterator to end
		iterator end()
		{ return iterator(cell.getend()); }

		//	Return iterator to end
		const_iterator end() const
		{ return const_iterator(cell.getend()); }

		//	Return reverse iterator to reverse beginning
		reverse_iterator rbegin()
		{
			if (!_size)
				return (rend());
			return reverse_iterator(cell.cell_max());
		}

		//	Return reverse iterator to reverse beginning
		const_reverse_iterator rbegin() const
		{
			if (!_size)
				return (rend());
			return reverse_iterator(cell.cell_max());
		}

		//	Return reverse iterator to reverse end
		reverse_iterator rend()
		{ return reverse_iterator(cell.getRend()); }

		//	Return reverse iterator to reverse end
		const_reverse_iterator rend() const
		{ return const_reverse_iterator(cell.getRend()); }

		//	Test whether container is empty
		bool empty() const
		{ return !_size ? 1 : 0; }

		//	Return container size
		size_type size() const
		{ return (_size); }

		//	Return maximum size
		size_type max_size() const
		{
			return (std::numeric_limits<size_type>::max() /
					(2 * (sizeof(cell_t<key_type, size_type>) - sizeof(pointer))));
		}

		//	Element access:
		//	Access element
		mapped_type &operator[](const key_type &k)
		{
			cell_t<Key, T> *tmp = cell.cell_search(k);
			if (!tmp)
			{
				_size++;
				return ((cell.cell_add(std::pair<key_type, mapped_type>(k, T())))->value->second);
			}
			return (tmp->value->second);
		}

		//	Modifiers:
		//	Insert elements
		std::pair<iterator, bool> insert(const value_type &val)
		{
			if (!cell.cell_search(val))
			{
				_size++;
				return (std::pair<iterator, bool>(iterator(cell.cell_add(val)), true));
			}
			return (std::pair<iterator, bool>(iterator(cell.cell_search(val)), false));
		}

		//	Insert elements
		iterator insert(iterator hint, const value_type &val)
		{
			(void) hint;
			if (!cell.cell_search(val))
			{
				_size++;
				return (iterator(cell.cell_add(val)));
			}
			return (iterator(cell.cell_search(val)));
		}

		//	Insert elements
		template<class InputIterator>
		void insert(InputIterator first, typename enable_if<std::is_class<InputIterator>::value, InputIterator>::type last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		//	Erase elements
		void erase(iterator position)
		{
			if (_size)
			{
				cell.cell_delete(cell.getBase(), (*position).first);
				cell.cell_set_end();
				cell.cell_set_rend();
				_size--;
			}
		}

		//	Erase elements
		size_type erase(const key_type &k)
		{
			cell_t<Key, T> *tmp = cell.cell_search(k);
			if (tmp)
			{
				cell.cell_delete(cell.getBase(), k);
				cell.cell_set_end();
				cell.cell_set_rend();
				_size--;
				return (1);
			}
			return (0);
		}

		//	Erase elements
		void erase(iterator first, iterator last)
		{
			iterator tmp = first;
			while (first != last)
			{
				tmp++;
				cell.cell_delete(cell.getBase(), (*first).first);
				_size--;
				first = tmp;
			}
		}

		//	Swap content
		void swap(map &x)
		{
			cell_t<Key, T> *base;
			base = x.cell.getBase();
			x.cell.setBase(cell.getBase());
			cell.setBase(base);
			allocator_type alloc;
			alloc = _alloc;
			_alloc = x._alloc;
			x._alloc = alloc;
			size_type size;
			size = x._size;
			x._size = _size;
			_size = size;
			key_compare key;
			key = _key_compare;
			_key_compare = x._key_compare;
			x._key_compare = key;
		}

		//	Clear content
		void clear()
		{
			_size = 0;
			cell.cell_clear();
		}

		//	Observers:
		//	Return key comparison object
		key_compare key_comp() const
		{
			return (_key_compare);
		}

		//	Return value comparison object
		value_compare value_comp() const
		{
			return (value_compare(_key_compare));
		}

		//	Operations:
		//	Get iterator to element
		iterator find(const key_type &k)
		{
			cell_t<Key, T> *tmp = cell.cell_search(k);
			if (!tmp)
				return (end());
			return (iterator(tmp));
		}

		//	Get iterator to element
		const_iterator find(const key_type &k) const
		{
			cell_t<Key, T> *tmp;
			tmp = cell.cell_search(k);
			if (!tmp)
				return (end());
			return (const_iterator(tmp));
		}

		//	Count elements with a specific key
		size_type count(const key_type &k) const
		{
			if (cell.cell_search(k))
				return (1);
			return (0);
		}

		//	Return iterator to lower bound
		iterator lower_bound(const key_type &k)
		{
			cell_t<Key, T> *tmp = cell.cell_search(k);
			if (tmp)
				return (iterator(tmp));
			iterator begin = this->begin();
			iterator end = this->end();
			while (begin != end)
			{
				if (!_key_compare((*begin).first, k))
					return (begin);
				begin++;
			}
			return (iterator(cell.getBase()));
		}

		//	Return iterator to lower bound
		const_iterator lower_bound(const key_type &k) const
		{
			cell_t<Key, T> *tmp = cell.cell_search(k);
			if (tmp)
				return (iterator(tmp));
			iterator begin = this->begin();
			iterator end = this->end();
			while (begin != end)
			{
				if (!_key_compare((*begin).first, k))
					return (begin);
				begin++;
			}
			return (const_iterator(cell.getBase()));
		}

		//	Return iterator to upper bound
		iterator upper_bound(const key_type &k)
		{
			iterator begin = this->begin();
			iterator end = this->end();
			while (begin != end)
			{
				if (_key_compare(k, (*begin).first))
					break;
				begin++;
			}
			return (begin);
		}

		//	Return iterator to upper bound
		const_iterator upper_bound(const key_type &k) const
		{
			const_iterator begin = this->begin();
			const_iterator end = this->end();
			while (begin != end)
			{
				if (_key_compare(k, (*begin).first))
					break;
				begin++;
			}
			return (begin);
		}

		//	Get range of equal elements
		std::pair<iterator, iterator> equal_range(const key_type &k)
		{
			return (std::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
		}

		//	Get range of equal elements
		std::pair<const_iterator, const_iterator> equal_range(const key_type &k) const
		{
			return (std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
		}

		friend bool operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
		{

			if (lhs.size() != rhs.size())
				return (false);
			typename ft::map<Key, T, Compare, Alloc>::const_iterator beginLhs = lhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator begRhs = rhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator endLhs = lhs.end();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator endRhs = rhs.end();
			while (beginLhs != endLhs && begRhs != endRhs && *beginLhs == *begRhs)
			{
				beginLhs++;
				begRhs++;
			}
			return beginLhs == endLhs && begRhs == endRhs;
		}

		friend bool operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return (!(lhs == rhs));
		}

		friend bool operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
		{

			if (lhs.size() < rhs.size())
				return (true);
			if (lhs.size() > rhs.size())
				return (false);
			typename ft::map<Key, T, Compare, Alloc>::const_iterator beginLhs = lhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator begRhs = rhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator endLhs = lhs.end();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator endRhs = rhs.end();

			while (beginLhs != endLhs && begRhs != endRhs && *beginLhs == *begRhs)
			{
				beginLhs++;
				begRhs++;
			}
			return !((beginLhs == endLhs && begRhs == endRhs) || begRhs == endRhs || *beginLhs >= *begRhs);
		}

		friend bool operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return (lhs < rhs || lhs == rhs);
		}

		friend bool operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			if (lhs.size() > rhs.size())
				return (true);
			if (lhs.size() < rhs.size())
				return (false);
			typename ft::map<Key, T, Compare, Alloc>::const_iterator beginLhs = lhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator begRhs = rhs.begin();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator endLhs = lhs.end();
			typename ft::map<Key, T, Compare, Alloc>::const_iterator endRhs = rhs.end();
			while (beginLhs != endLhs && begRhs != endRhs && *beginLhs == *begRhs)
			{
				beginLhs++;
				begRhs++;
			}
			return !((beginLhs == endLhs && begRhs == endRhs) || beginLhs == endLhs || *beginLhs <= *begRhs);
		}

		friend bool operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs)
		{
			return (lhs > rhs || lhs == rhs);
		}

		void swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs)
		{
			lhs.swap(rhs);
		}
	};
}
#endif
