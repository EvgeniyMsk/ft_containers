//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_H
#define FT_CONTAINERS_REVERSE_ITERATOR_H

namespace ft {
    template<typename T>
    class reverse_iterator {
    private:
        list_t <T> *_ptr;
    public:
        explicit reverse_iterator() : _ptr(nullptr) {}

        explicit reverse_iterator(list_t <T> *ptr) : _ptr(ptr) {}

        reverse_iterator(reverse_iterator const &reverseIterator) {
            *this = reverseIterator;
        }

        reverse_iterator &operator=(reverse_iterator const &reverseIterator) {
            _ptr = reverseIterator._ptr;
            return (*this);
        }

        reverse_iterator &operator++() {
            _ptr = _ptr->prev;
            return (*this);
        }

        reverse_iterator &operator--() {
            _ptr = _ptr->next;
            return (*this);
        }

        bool &operator==(reverse_iterator const &reverseIterator) { return (_ptr == reverseIterator._ptr); }

        bool &operator!=(reverse_iterator const &reverseIterator) { return (_ptr != reverseIterator._ptr); }

        T &operator*() { return (*_ptr->data); }

        T *operator->() { return (_ptr->data); }

        list_t <T> *getCell() const {
            return (_ptr);
        }
    };
}
#endif //FT_CONTAINERS_REVERSE_ITERATOR_H
