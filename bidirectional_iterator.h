//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_H
#define FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_H

namespace ft {
    template<typename T>
    struct list_t {
        T *data;
        struct list_t *next;
        struct list_t *prev;
    };

    template<typename T>
    class bidirectional_iterator {
    private:
        list_t<T> *_ptr;
    public:
        explicit bidirectional_iterator(void) : _ptr(nullptr) {};

        explicit bidirectional_iterator(list_t<T> *ptr) : _ptr(ptr) {};

        bidirectional_iterator(const bidirectional_iterator &bidirectionalIterator) { *this = bidirectionalIterator; };

        bidirectional_iterator &operator=(bidirectional_iterator const &bidirectionalIterator) {
            _ptr = bidirectionalIterator._ptr;
            return (*this);
        };

        virtual ~bidirectional_iterator() {};

        bidirectional_iterator &operator++() {
            _ptr++;
            return (*this);
        }

        bidirectional_iterator &operator--() {
            _ptr--;
            return (*this);
        }

        bool operator==(bidirectional_iterator const &bidirectionalIterator) {
            return (_ptr == bidirectionalIterator._ptr);
        };

        bool operator!=(bidirectional_iterator const &bidirectionalIterator) {
            return (_ptr != bidirectionalIterator._ptr);
        };

        T &operator*() { return *(_ptr->data); };

        T *operator->() { return (_ptr->data); };

        list_t<T> *getCell() { return (_ptr); }
    };
}
#endif
