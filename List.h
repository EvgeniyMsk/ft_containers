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
        //  Empty container constructor (default constructor)
        List() : _length(0) {
            _end = _cellAlloc.allocate(1);
            _cellAlloc.construct(_end);
            _end->data = new T();
            _end->prev = _end;
            _end->next = _end;
            _front = _end;
            _back = _end;
        }

        explicit List(size_type n, const value_type &val = value_type(), const allocator_type& alloc = allocator_type())
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

    };
}

#endif //FT_CONTAINERS_LIST_H
