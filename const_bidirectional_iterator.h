//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_CONST_BIDIRECTIONAL_ITERATOR_H
#define FT_CONTAINERS_CONST_BIDIRECTIONAL_ITERATOR_H


namespace ft {

    template<typename T>
    class const_bidirectional_iterator {
    private:
        list_t <T> *_ptr;
    public:
        typedef ft::bidirectional_iterator<T> bidirectional_iterator;

        explicit const_bidirectional_iterator(void) : _ptr(nullptr) {};

        explicit const_bidirectional_iterator(list_t <T> *ptr) : _ptr(ptr) {};

        const_bidirectional_iterator(const const_bidirectional_iterator &constBidirectionalIterator) {
            *this = constBidirectionalIterator;
        };

        const_bidirectional_iterator(const bidirectional_iterator &bidirectionalIterator) {
            *this = bidirectionalIterator;
        }

        const_bidirectional_iterator &operator=(const_bidirectional_iterator const &constBidirectionalIterator) {
            _ptr = constBidirectionalIterator._ptr;
            return (*this);
        };

        const_bidirectional_iterator &operator=(bidirectional_iterator const &bidirectionalIterator) {
            _ptr = bidirectionalIterator.getCell();
            return (*this);
        }

        virtual ~const_bidirectional_iterator() {};

        const_bidirectional_iterator &operator++() {
            _ptr++;
            return (*this);
        }

        const_bidirectional_iterator &operator--() {
            _ptr--;
            return (*this);
        }

        bool operator==(const_bidirectional_iterator const &constBidirectionalIterator) {
            return (_ptr == constBidirectionalIterator._ptr);
        };

        bool operator!=(const_bidirectional_iterator const &constBidirectionalIterator) {
            return (_ptr != constBidirectionalIterator._ptr);
        };

        const T &operator*() { return *(_ptr->data); };
    };
}


#endif
