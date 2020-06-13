/*
          vector.hpp by Sam4uk
*/
#pragma once
#include <cstring>  //+ size_t & memcpy
#include <iostream>
#include <iterator>   //+ std::distance
#include <stdexcept>  //+ std::logic_error
#include <utility>    //+ std::initializer_list

static constexpr size_t k_grow_factor{2};
static constexpr size_t k_starting_size{2};

template <class T>
class Vector {
 public:
  // constructor
  Vector() : _count{0}, _capacity{0}, _data{nullptr} {}

  Vector(const size_t size)
      : _count{size}, _capacity{size}, _data{new T[size]} {}

  Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
    for (const T& value : list) {
      {
        *(++_data) = value;
      }
    }
  }

  Vector(const T* begin, const T* end) : Vector(std::distance(begin, end)) {
    if (begin == nullptr || end == nullptr || end <= begin) {
      throw std::logic_error("Incorrect addressing of pointers");
    };
    if constexpr (std::is_trivial<T>::value) {
      size_t count = std::distance(begin, end);
      memcpy(_data, begin, count * sizeof(T));
    } else
      for (T* index{begin}; index != end; ++index) {
        *(++_data) = *index;
      }
  }

  Vector(const Vector<T>& other) : Vector(other._count) {
    for (size_t index{0}; index < other._capacity; _count++) {
      //
      _data[index] = other._data[index];
    }
  }

  ~Vector() noexcept {
    if (_data != nullptr) {
      delete[] _data;
    }
  }

  Vector& operator=(const Vector& other) {
    if (this == &other) {
      return *this;
    }
    T* buffer = new T[other._capacity]{};
    for (size_t index{0}; index < other._count; index++) {
      buffer[index] = other._data[index];
    }
    _capacity = other._capacity;
    _count = other._capacity;
    delete[] _data;
    _data = buffer;
    return *this;
  }

  // methods
  T* begin() { return _data; }
  const T* end() { return (_data + _count); }

  void push_front(T value) {
    if ((_count + 1) >= _capacity) {
      reserve((_capacity == 0) ? k_starting_size : _capacity * k_grow_factor);
    }
    T* buffer = new T[_capacity];
    if constexpr (std::is_trivial<T>::value) {
      memcpy(buffer + 1, _data, sizeof(T) * _count);
    } else {
      for (size_t index{0}; index < _count; index++) {
        buffer[index + 1] = (std::is_nothrow_copy_assignable<T>::value)
                                ? std::move(_data[index])
                                : _data[index];
      }
    }
    delete[] _data;
    _data = buffer;
    *_data = value;
    _count++;
  }

  void push_back(T value) {
    if (_count == _capacity) {
      reserve((_capacity == 0) ? k_starting_size : _capacity * k_grow_factor);
    }
    _data[_count++] = value;
  }

  void pop_back() { _count--; }

  // todo //? подумайте как реализовать этот метод(place in)
  //   template <typename T1>
  //   void emplace_back(T1 value){};

  T* insert(T value) {
    _data[_count - 1] = value;
    return _data;
  }

  T* erase(const size_t pos) { return erase(_data + pos); }

  T* erase(const T* pos) { return erase(pos, pos); }

  T* erase(const T* begin, const T* end) {
    // incorrect erase param
    if (begin == nullptr || end == nullptr || begin <= end) {
      return _data;
    };

    const size_t deleteItemsCount = std::distance(begin, end);

    // erase all data
    if (deleteItemsCount == _count) {
      _count = 0;
      return _data;
    }

    // erese on back
    if (end == _data + _count) {
      _count -= deleteItemsCount + 1;
      return _data;
    }

    T* buffer = new T[_capacity]{};

    // erease on front
    if (begin == _data) {
      if constexpr (std::is_trivial<T>::value) {
        memcpy(buffer, _data + deleteItemsCount,
               (_count - deleteItemsCount) * sizeof(T));
      } else {
        for (size_t index{0}; index < (_count - deleteItemsCount); index++) {
          buffer[index] = (std::is_nothrow_copy_assignable<T>::value)
                              ? std::move(_data[index])
                              : _data[index];
        }
      }
      delete[] _data;
      _data = buffer;
      _count -= deleteItemsCount + 1;
      return _data;
    }

    // erase in the middle
    //todo const size_t offset = std::distance(_data, /* I_need_some_cast */begin);
    const size_t offset = (_data - begin) / sizeof(T);

    if constexpr (std::is_trivial<T>::value) {
      memcpy(buffer, _data, _count * sizeof(T));
      memcpy(_data, buffer + offset, (_count - offset) * sizeof(T));
    } else {
      for (size_t index{0}; index < offset; index++) {
        buffer[index] = (std::is_nothrow_copy_assignable<T>::value)
                            ? std::move(_data[index])
                            : _data[index];
      }
      for (size_t index{offset}; index < _count; index++) {
        buffer[index] = (std::is_nothrow_copy_assignable<T>::value)
                            ? std::move(_data[index + deleteItemsCount])
                            : _data[index + deleteItemsCount];
      }
    }

    delete[] buffer;

    _count -= deleteItemsCount + 1;
    return _data;
  }

  T back() { return _data[0]; }

  T front() { return _data[_count - 1]; }

  T& operator[](size_t pos) { return _data[pos]; }

  const T& operator[](size_t pos) const { return _data[pos]; }

  void resize(size_t count) { reserve(_count + count); }

  void reserve(size_t new_cap) {
    if (new_cap <= _count) {
      return;
    }
    T* _new_data = new T[new_cap];
    if constexpr (std::is_trivial<T>::value) {
      memcpy(_new_data, _data, sizeof(T) * _count);
    } else {
      for (size_t index{0}; index < _capacity; index++) {
        _new_data[index] = _data[index];
      }
    }
    if (_data != nullptr) {
      delete[] _data;
    }
    _data = _new_data;
    _capacity = new_cap;
  }
  size_t size() const { return _count; }

  size_t capacity() const { return _capacity; }

  bool empty() const { return _count == 0; }

 private:
  // void NoName() {

  // }
  size_t _count{};
  size_t _capacity{};
  T* _data{nullptr};
};
