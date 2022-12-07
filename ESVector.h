#ifndef ESVECTOR_H
#define ESVECTOR_H

#include <iostream>
#include <initializer_list>

using namespace std;

template<class t>
class ESVector {
private:
    t *arr;
    int _size;
    int _capacity;

    void expand(int n = 0);

public:

    using iterator = t *;

    ESVector(initializer_list<t> another);

    ESVector() : ESVector(0) {}

    ESVector(int n);

    ESVector(t *another, int n);

    ESVector(const ESVector<t> &another);

    virtual ~ESVector();

    ESVector<t> &operator=(const ESVector &another);

    ESVector<t> &operator=(ESVector<t> &&another) noexcept;

    int push_back(t value);

    t pop_back();

    void erase(iterator it);

    void erase(iterator it1, iterator it2); //eslam done partially

    void clear();

    void insert(iterator it, t al); //saikoo-empty

    iterator begin();

    iterator end();

    bool operator==(const ESVector<t> &another);

    bool operator<(const ESVector<t> &another);

    int size();

    int capacity() const;

    bool resize(int n);

    bool empty();

    t &operator[](int item);

    template<class u>
    friend ostream &operator<<(ostream &out, ESVector<u> another);
};

#endif

template<class u>
ostream &operator<<(ostream &out, ESVector<u> another) {
    for (int i = 0; i < another._size; i++) {
        out << another.arr[i];
        if (i != another._size - 1)
            out << " ";
    }
    return out;
}

template<class t>
ESVector<t>::ESVector(initializer_list<t> another) {
    this->_size = another.size();
    this->_capacity = this->_size * 2;

    arr = new t[_capacity];

    auto it = another.begin();
    for (int i = 0; i < _size; ++i) {
        arr[i] = *(it++);
    }
    for (int i = _size; i < _capacity; ++i) {
        arr[i] = 0;
    }
}


template<class t>
ESVector<t>::ESVector(int n) {
    _size = n;
    _capacity = n * 2;
    arr = new t[_capacity];

    for (int i = 0; i < _size; ++i)
        arr[i] = 0;
}


template<class t>
ESVector<t>::ESVector(const ESVector &another) {
    this->_size = another._size;
    this->_capacity = another._capacity;
    arr = new t[_capacity];

    for (int i = 0; i < _size; i++)
        arr[i] = another.arr[i];
}


template<class t>
ESVector<t> &ESVector<t>::operator=(const ESVector<t> &another) {
    if (this != &another) {
        delete[] arr;
        this->_size = another._size;
        this->_capacity = another._capacity;
        arr = new t[_capacity];

        for (int i = 0; i < _size; i++)
            arr[i] = another.arr[i];
    }
    return *this;
}


template<class t>
t ESVector<t>::pop_back() {
    if (_size != 0) {
        return arr[--_size];
    }
}


template<class t>
void ESVector<t>::clear() {
    _size = 0;
}


template<class t>
bool ESVector<t>::operator<(const ESVector<t> &another) {
    if (this->_size >= another._size)
        return false;

    for (int i = 0; i < _size; i++) {
        if (arr[i] >= another.arr[i])
            return false;
    }

    return true;
}


template<class t>
int ESVector<t>::size() {
    return this->_size;
}


template<class t>
bool ESVector<t>::empty() {
    return (_size == 0);
}


template<class t>
void ESVector<t>::erase(ESVector<t>::iterator it) {

    if (it >= arr + _size || it < arr)
        return;                // throw exception

    for (int i = (it - arr); i < _size - 1; i++)
        arr[i] = arr[i + 1];

    --_size;
}


template<class t>
void ESVector<t>::insert(ESVector<t>::iterator it, t val) {

    int len = (it - arr);
    if (len < 0)
        return;  //throw exception

    int old_size = _size;
    int new_size = max(len + 1, _size + 1);
    if ((len + 1) > _capacity) {
        t *temp = new t[_size];
        for (int i = 0; i < _size; i++)
            temp[i] = arr[i];
        delete[] arr;
        _size = (len + 1);
        _capacity = _size * 2;
        arr = new t[_capacity];
        for (int i = 0; i < old_size; i++)
            arr[i] = temp[i];
        for (int i = old_size; i < _capacity; i++)
            arr[i] = 0;
        new_size = len + 1;
    }
    for (int i = _size; i > len; i--)
        arr[i] = arr[i - 1];
    arr[len] = val;
    _size = new_size;


}

template<class t>
ESVector<t>::ESVector(t *another, int n) {
    _size = n;
    _capacity = n * 2;
    arr = new t[_capacity];
    for (int i = 0; i < n; ++i) {
        arr[i] = another[i];
    }
}

template<class t>
ESVector<t>::~ESVector() {
    delete[] arr;

}

template<class t>
ESVector<t> &ESVector<t>::operator=(ESVector<t> &&another) noexcept {
    if (this != &another) {
        delete[] arr;
        _size = another._size;
        _capacity = another._capacity;
        arr = new t[_capacity];
        for (int i = 0; i < _size; ++i) {
            arr[i] = another.arr[i];
        }
        another._size = 0;
        another._capacity = 0;
        another.arr = nullptr;
    }
    return *this;

}

template<class t>
void ESVector<t>::expand(int n) {
    int oldSize = _size;
    if (n) {
        _size = n;
        _capacity = 2 * _size;
    } else {
        _capacity *= 2;
    }


    t *temp = new t[oldSize];
    for (int i = 0; i < oldSize; ++i) {
        temp[i] = arr[i];
    }
    delete[]arr;
    arr = new t[_capacity];
    for (int i = 0; i < oldSize; ++i) {
        arr[i] = temp[i];
    }
    for (int i = oldSize; i < _capacity; ++i) {
        arr[i] = 0;
    }
}

template<class t>
int ESVector<t>::push_back(t value) {
    if (_size == _capacity)
        expand();
    arr[_size++] = value;
    return _size;
}

template<class t>
void ESVector<t>::erase(ESVector::iterator it1, ESVector::iterator it2) {
    if (it1 > it2)
        return;
    if (it1 < arr || it1 > arr + _size || it2 < arr || it2 > arr + _size) {
        return; // throw exception
    }
    int j = 0;
    for (int i = (it2 - arr); i < _size; ++i) {
        arr[it1 - arr + (j++)] = arr[i];
    }
    _size -= (it2 - it1);
}

template<class t>
bool ESVector<t>::operator==(const ESVector<t> &another) {
    if (this->_size != another._size)
        return false;

    for (int i = 0; i < _size; i++) {
        if (arr[i] != another.arr[i])
            return false;
    }

    return true;
}

template<class t>
int ESVector<t>::capacity() const {
    return _capacity;
}

template<class t>
bool ESVector<t>::resize(int n) {
    if (n >= _size) {
        expand(n);
        return true;
    }
    return false;
}

template<class t>
t &ESVector<t>::operator[](int item) {
    return arr[item];
}

template<class t>
t *ESVector<t>::begin() {
    return arr;
}

template<class t>
t *ESVector<t>::end() {
    return arr + _size;
}





