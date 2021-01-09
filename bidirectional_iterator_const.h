//
// Created by Qsymond on 2021-01-09.
//

#ifndef FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_CONST_H
#define FT_CONTAINERS_BIDIRECTIONAL_ITERATOR_CONST_H


namespace ft {

    template<typename T>
    class bidirectional_iterator_const {
    private:
        list_t <T> *_ptr;
    public:
        typedef ft::bidirectional_iterator<T> bidirectional_iterator;

        explicit bidirectional_iterator_const(void) : _ptr(nullptr) {};

        explicit bidirectional_iterator_const(list_t <T> *ptr) : _ptr(ptr) {};

        bidirectional_iterator_const(
                const bidirectional_iterator_const &bidirectionalIteratorConst) { *this = bidirectionalIteratorConst; };

        bidirectional_iterator_const &operator=(bidirectional_iterator_const const &bidirectionalIteratorConst) {
            _ptr = bidirectionalIteratorConst._ptr;
            return (*this);
        };

        bidirectional_iterator_const &operator=(const bidirectional_iterator &bidirectional_iterator) {
            _ptr = bidirectional_iterator.getCell();
            return (*this);
        };

        virtual ~bidirectional_iterator_const() {};

        bidirectional_iterator_const &operator++() {
            _ptr++;
            return (*this);
        }

        bidirectional_iterator_const &operator--() {
            _ptr--;
            return (*this);
        }

        bool operator==(bidirectional_iterator_const const &bidirectionalIteratorConst) {
            return (_ptr == bidirectionalIteratorConst._ptr);
        };

        bool operator!=(bidirectional_iterator_const const &bidirectionalIteratorConst) {
            return (_ptr != bidirectionalIteratorConst._ptr);
        };

        T &operator*() { return *(_ptr->data); };

        T *operator->() { return (_ptr->data); };

        list_t <T> *getCell() { return (_ptr); }
    };
}


#endif
