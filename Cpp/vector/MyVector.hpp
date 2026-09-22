#pragma once

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class MyVector {
public:
    MyVector<T>() = default;

    MyVector<T>(std::size_t size) : _capacity(size), _item_count(size), _arr(new T[size]) {}
    MyVector<T>(std::size_t size, const T& value) : _capacity(size), _item_count(size), _arr(new T[size]) {
        for(size_t i=0; i<size; i++) {
            _arr[i] = value;
        }
    }

    MyVector<T>(const MyVector<T>& other)
    : _capacity(other._capacity), _item_count(other._item_count) {
        _arr = new T[other._capacity];

        for(size_t i=0; i<other._item_count; i++) {
            _arr[i] = other._arr[i];
        }
    }

    MyVector<T>(std::initializer_list<T> init): _capacity(init.size()), _item_count(init.size()) {
        T* new_arr = new T[_capacity];
        std::copy(init.begin(), init.end(), new_arr);
        _arr = new_arr;
    }

    ~MyVector() { delete [] _arr; }

    void push_back(T& item) {
        if(_item_count == _capacity) {
            _realloc_arr();
        }

        _arr[_item_count] = item;
        _item_count++;
    }

    void pop_back() {
        _assert_not_empty();
        _item_count--;
    }

    void reserve(size_t size) {
        if(size <= _capacity) return;
        _realloc_arr(size);
    }

    void shrink_to_fit() {
        if(_item_count == _capacity) return;
        if(_item_count == 0) {
            _capacity = 0;
            delete [] _arr;
            _arr = nullptr;
            return;
        }

        // the name here deceives , i should've named it better
        // even though it says expand array, it doesn't really expand here
        // basically shrink to fit also chanegs the capacity
        // which means it requires reallocation
        // now since expand array does the reallocation we are essentially doing that but with a lesser value than capacity
        // if capacity -> 20, item_count -> 10, shrink_to_fit() -> cap: 10, item_count: 10
        // we do need to destory the items prior to that 
        _realloc_arr(_item_count);
    }

    void resize(const size_t size) {
        if(size > _capacity) {
            _realloc_arr(size);
            _item_count = size;
            return;
        }

        _item_count = size;
    }

    void clear() { _item_count = 0; }

    size_t size() const { return _item_count; }
    size_t capacity() const { return _capacity; }

    T& at(size_t index) {
        _assert_index_in_bound(index);
        return _arr[index];
    }

    const T& at(size_t index) const {
        _assert_index_in_bound(index);
        return _arr[index];
    }

    bool empty() const { return _item_count == 0; }

    T& front() { _assert_not_empty(); return _arr[0]; }
    const T& front() const { _assert_not_empty(); return _arr[0]; }

    T& back() { _assert_not_empty(); return _arr[_item_count - 1]; }
    const T& back() const { _assert_not_empty(); return _arr[_item_count - 1]; }

    T& operator[](size_t index) { return _arr[index]; }
    const T& operator[](size_t index) const { return _arr[index]; }

    MyVector<T>& operator=(const MyVector<T>& other) {

        if(this == &other) return *this;

        _realloc_arr(other._capacity, other._arr, other._item_count);

        _item_count = other._item_count;

        return *this;
    }


private:
    size_t _capacity = 0;
    size_t _item_count = 0;
    const size_t _growth_factor = 2;

    T* _arr = nullptr;

    void _realloc_arr(size_t new_capacity = 0) {
        if(! (new_capacity > 0))
            new_capacity = !_capacity ? _capacity + 1 : _capacity * _growth_factor;

        T* new_arr = new T[new_capacity];
        _copy_items(new_arr);

        delete [] _arr;
        _arr = new_arr;

        _capacity = new_capacity;
    }

    void _realloc_arr(const size_t new_capacity, const T* const source, const size_t source_item_count) {
        T* new_arr = new T[new_capacity];
        _copy_items(new_arr, source, source_item_count);

        delete [] _arr;
        _arr = new_arr;

        _capacity = new_capacity;
    }

    void _copy_items(T* const dest) const {
        for(size_t i=0; i<_item_count; i++) {
            dest[i] = _arr[i];
        }
    }

    void _copy_items(T* const dest, const T* const source, size_t item_count) const {
        for(size_t i=0; i<item_count; i++) {
            dest[i] = source[i];
        }
    }

    inline void _assert_index_in_bound(size_t index) const {
        if(index >= _item_count) {
            throw std::out_of_range("Index out of bound");
        }
    }

    inline void _assert_not_empty() const {
        if(empty()) {
            throw std::out_of_range("Container is empty");
        }
    }
};
