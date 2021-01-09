//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_CONST_REVERSE_ITERATOR_H
#define FT_CONTAINERS_CONST_REVERSE_ITERATOR_H


namespace ft {
    template<typename T>
    class const_reverse_iterator {
    private:
        list_t <T> *_ptr;
    public:
        typedef ft::reverse_iterator<T> reverse_iterator;

        explicit const_reverse_iterator() : _ptr(nullptr) {}

        explicit const_reverse_iterator(list_t <T> *ptr) : _ptr(ptr) {}

        const_reverse_iterator(const_reverse_iterator const &constReverseIterator) { *this = constReverseIterator; }

        const_reverse_iterator(reverse_iterator const &reverseIterator) {
            _ptr = reverseIterator.getCell();
            return (*this);
        }

        virtual ~const_reverse_iterator() {}

        const_reverse_iterator &operator=(const_reverse_iterator const &constReverseIterator) {
            _ptr = constReverseIterator._ptr;
            return (*this);
        }

        const_reverse_iterator &operator=(reverse_iterator const &reverseIterator) {
            _ptr = reverseIterator.getCell();
            return (*this);
        }
    };
}
#endif //FT_CONTAINERS_CONST_REVERSE_ITERATOR_H
