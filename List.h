//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_LIST_H
#define FT_CONTAINERS_LIST_H

#include <memory>
#include "bidirectional_iterator.h"
#include "const_bidirectional_iterator.h"
#include "reverse_iterator.h"
#include "const_reverse_iterator.h"
    // Реализация двусвязного списка (в соответствии со стандартом C++98)
    // http://www.cplusplus.com/reference/list/list/list/

using namespace ft;
namespace ft {
    template<typename T, class Alloc = std::allocator<T> >

    class List {
    private:
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

        list_t<value_type> *_front;
        list_t<value_type> *_back;
        list_t<value_type> *_end;
        size_type _length;
        allocator_type _alloc;
        std::allocator<list_t<T> > _cellAlloc;

    public:

        //  Member functions
        //  Empty container constructor (default constructor). Constructs an empty container, with no elements.
        List() : _length(0) {
            _end = _cellAlloc.allocate(1);
            _cellAlloc.construct(_end);
            _end->data = new T();
            _end->prev = _end;
            _end->next = _end;
            _front = _end;
            _back = _end;
        }

        //  fill constructor. Constructs a container with n elements. Each element is a copy of val.
        explicit List(size_type n, const value_type &val = value_type(),
                      const allocator_type &alloc = allocator_type()) {
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
        List(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {
            _end = _cellAlloc.allocate(1);
            _cellAlloc.construct(_end);
            _end->data = new T();
            _end->prev = _end;
            _end->next = _end;
            _front = _end;
            _back = _end;
            _length = 0;
            _alloc = alloc;
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }

        //  copy constructor. Constructs a container with a copy of each of the elements in x, in the same order.
        List(List const &list) : _length(0) {
            _end = _cellAlloc.allocate(1);
            _cellAlloc.construct(_end);
            _end->data = new T();
            _end->prev = _end;
            _end->next = _end;
            _front = _end;
            _back = _end;
            *this = list;
        }

        virtual ~List() {
            clear();
            delete (_end->data);
            _cellAlloc.destroy(_end);
            _cellAlloc.deallocate(_end, 1);
        }

        List &operator=(List const &list) {
            clear();
            if (list.empty())
                return (*this);
            for (const_iterator it = list.)
        }


        //  Element access::
        reference front() { return (*_front->data); }

        const_reference front() const { return (*_front->data); }

        reference back() { return (*_back->data); }

        const_reference back() const { return (*_back->data); }

        //  Iterators:
        iterator begin() { return (iterator(_front)); }

        const_iterator begin() const { return (const_iterator(_front)); }

        iterator end() { return (iterator(_end)); }

        const_iterator end() const { return (const_iterator(_end)); }

        reverse_iterator rbegin() { return (reverse_iterator(_back));}

        const_reverse_iterator rbegin() const { return (const_reverse_iterator(_back)); }

        reverse_iterator rend() { return (reverse_iterator(_end));}

        const_reverse_iterator rend() const { return (const_reverse_iterator(_end)); }

        //  Capacity:
        bool empty() const { return (_length > 0); }

        size_type size() const { return (_length); }

        size_type max_size() const { return (std::numeric_limits<size_type>::max()); };

    };
}

#endif //FT_CONTAINERS_LIST_H
