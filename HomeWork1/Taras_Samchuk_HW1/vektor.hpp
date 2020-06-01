/*
          vector.hpp by Sam4uk
*/
#pragma once
#include <cstring>    //+ size_t & memcpy
#include <iterator>   //+ std::distance
#include <stdexcept>  //+ std::logic_error
#include <utility>    //+ std::initializer_list

static constexpr size_t k_grow_factor{2};
static constexpr size_t k_starting_size{2};

template <class T>
class Vector {
 public:
  // constructor
  Vector() = default;
  Vector(size_t size) : _capacity{size} {};

  Vector(std::initializer_list<T> list) {
    _capacity = list.size();
    delete[] _data;
    _data = new T[_capacity];
    for (auto&& i : list) {
      {
        _data[_count++] = i;
      }
    }
  }
  Vector(T* begin, T* end) {
    if (begin == nullptr || end == nullptr || end <= begin) {
      // return;
      throw std::logic_error("Incorrect addressing of pointers");
    };

    for (T* index{begin}; index != end; index++) {
      _data[_count++] = *index++;
    }
  };
  Vector(const Vector& other)
      : _capacity(other._capacity),
        _count(other._count),
        _data(new T[_capacity]) {
    if (*this == other) {
      throw std::logic_error("Logical copy error");
    }
    for (auto&& i : _data) {
      _data[i] = other._data[i];
    }
    return *this;
  };
  ~Vector() { delete[] _data; };

  Vector& operator=(const Vector& other) {
    if (*this == other) {
      throw std::logic_error("Logical copy error");
    }
    delete[] _data;
    _capacity = other._capacity;
    _count = other._capacity;
    _data = new T[_capacity]{};
    for (auto&& i : _data) {
      _data[i] = other._data[i];
    }
    return *this;
  };

  // methods
  T* begin() { return _data; };
  const T* end() { return (_data + _count); };

  void push_front(T value) {
    if (_count >= _capacity - 1) {
      reserve(_capacity * k_grow_factor);
    }
    T* buffer = new T[_capacity];
    if (std::is_trivial<T>::value) {
      memcpy(buffer + 1, _data, sizeof(T) * _count);
    } else {
      for (size_t index{0}; index < _count; index++) {
        buffer[index + 1] = std::move(_data[index]);
      }
    }
    delete[] _data;
    _data = buffer;
    *_data = value;
    _count++;
  };

  void push_back(T value) {
    if (_count == _capacity) {
      reserve(_capacity * k_grow_factor);
    }
    _data[_count++] = value;
  };

  void pop_back() { _count--; }

  // todo //? подумайте как реализовать этот метод(place in)
  //   template <typename T1>
  //   void emplace_back(T1 value){};

  T* insert(T value) {
    _data[_count - 1] = value;
    return _data;
  };
  T* erase(const size_t pos) { return erase(_data + pos); };
  T* erase(const T* pos) { return erase(pos, pos); };
  T* erase(const T* begin, const T* end) {
    // incorrect erase param
    if (begin == nullptr || end == nullptr || begin <= end) {
      throw std::logic_error("Incorrect addressing of pointers");
    };

    const size_t deleteItemsCount = std::distance(begin, end);

    // erase all data
    if (deleteItemsCount == _count) {
      _count = 0;
      return _data;
    }

    T* buffer = new T[_capacity]{};

    // erese on back
    if (end == _data + _count) {
      _count -= deleteItemsCount + 1;
      return _data;
    }

    // erease on front
    if (begin == _data) {
      if (std::is_trivial<T>::value) {
        memcpy(buffer, _data + deleteItemsCount,
               (_count - deleteItemsCount) * sizeof(T));
      } else {
        for (size_t index{0}; index < (_count - deleteItemsCount); index++) {
          buffer[index] = std::move(_data[index]);
        }
      }
      delete[] _data;
      _data = buffer;
      _count -= deleteItemsCount + 1;
      return _data;
    }

    // erase in the middle
    const size_t offset = (_data - begin) / sizeof(T);

    if (std::is_trivial<T>::value) {
      memcpy(buffer, _data, _count * sizeof(T));
      memcpy(_data, buffer + offset, (_count - offset) * sizeof(T));
    } else {
      const size_t between_begin = std::distance(_data, begin);
      const size_t between_end = std::distance(begin, end);

      for (size_t index{0}; index < between_begin; index++) {
        buffer[index] = std::move(_data[index]);
      }
      for (size_t index{between_begin}; index < _count; index++) {
        buffer[index] = std::move(_data[index + between_end]);
      }
    }

    delete[] buffer;

    _count -= deleteItemsCount + 1;
    return _data;
  };

  T back() { return _data[0]; };
  T front() { return _data[_count - 1]; };

  T& operator[](size_t pos) { return _data[pos]; };
  const T& operator[](size_t pos) const { return _data[pos]; };

  void resize(size_t count) { reserve(_count + count); };
  void reserve(size_t new_cap) {
    if (new_cap <= _capacity) {
      throw std::logic_error("Incorrect resizing.");
    }
    T* _new_data = new T[new_cap];
    if (std::is_trivial<T>::value) {
      memcpy(_new_data, _data, sizeof(T) * _count);
    } else {
      for (size_t index{0}; index < _capacity; index++) {
        _new_data[index] = std::move(_data[index]);
      }
    }
    T* old = _data;
    _data = _new_data;
    delete[] old;
    _capacity = new_cap;
  };
  size_t size() const { return _count; };
  size_t capacity() const { return _capacity; };
  bool empty() const { return _count == 0; };

 private:
  size_t _capacity{k_starting_size};
  size_t _count{0};
  T* _data = new T[_capacity]{};
};
