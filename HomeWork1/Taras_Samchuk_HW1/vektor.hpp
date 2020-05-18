/*
          vector.hpp by Sam4uk
*/
#pragma once
#include <cstring>   //+ size_t & memcpy
#include <iterator>  //+std::distance
#include <utility>   //+ std::initializer_list

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
    const size_t ItemsCount = std::distance(begin, end);
    if (begin == nullptr || end == nullptr || ItemsCount <= 0) {
      return;
    };
  };
  Vector(const Vector& other)
      : _capacity(other._capacity),
        _count(other._count),
        _data(new T[_capacity]) {
    for (auto&& i : _data) {
      _data[i] = other._data[i];
    }
    return *this;
  };
  ~Vector() { delete[] _data; };
  Vector& operator=(const Vector& other) {
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

  void push_back(T value) {
    if (_count >= _capacity - 1) {
      resize(_capacity);
    }
    T* buffer = new T[_capacity];
    memcpy(buffer + 1, _data, sizeof(T) * _count);
    T* old = _data;
    _data = buffer;
    delete[] old;
    *_data = value;
    _count++;
  };

  void push_front(T value) {
    if (_count == _capacity) {
      resize(_capacity);
    }
    _data[_count++] = value;
  };

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
    const size_t deleteItemsCount = std::distance(begin, end);

    if (begin == nullptr || end == nullptr || deleteItemsCount < 0) {
      // incorrect erase
      return _data;
    };

    if (deleteItemsCount == _count) {  // erase all data
      _count = 0;
      return _data;
    }

    T* buffer = new T[_capacity]{};

    if (end == _data + _count) {  // erese on front
      _count -= deleteItemsCount + 1;
      return _data;
    }

    if (begin == _data) {  // erease on back
      memcpy(buffer, _data + deleteItemsCount,
             (_count - deleteItemsCount) * sizeof(T));
      delete[] _data;
      _data = buffer;
      _count -= deleteItemsCount + 1;
      return _data;
    }

    // erase in the middle
    const size_t offset = (_data - begin) / sizeof(T);
    memcpy(buffer, _data, _count * sizeof(T));
    memcpy(_data, buffer + offset, (_count - offset) * sizeof(T));

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
      return;
    }
    T* _new_data = new T[new_cap];
    memcpy(_new_data, _data, sizeof(T) * _count);
    T* old = _data;
    _data = _new_data;
    delete[] old;
    _capacity = new_cap;
  };
  size_t size() const { return _count; };
  size_t capacity() const { return _capacity; };
  bool empty() const { return _count == 0; };

 private:
  size_t _capacity{1};
  size_t _count{0};
  T* _data = new T[_capacity]{};
};
