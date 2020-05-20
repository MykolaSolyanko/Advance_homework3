#pragma once
#include <iostream>

template <typename T>
class Deleter {
 public:
  typedef T* pointer;
  void operator()(pointer t) const {
    std::cout << "()-----------------\n";
    delete t;
  }
};
template <typename T>
class Deleter<T[]> {
 public:
  typedef T* pointer;
  void operator()(pointer t) const {
    std::cout << "()-------[]----------\n";
    delete[] t;
  }
};

template <typename T, typename F = Deleter<T>>
class UniquePtr;

template <typename T, typename F>
class UniquePtr {
 public:
  typedef T* pointer;

  UniquePtr() = default;
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(pointer ptr) : _ptr(ptr){};

  UniquePtr& operator=(pointer ptr) {
    free();
    _ptr = ptr;
    return *this;
  };

  UniquePtr(UniquePtr&& ptr) : _ptr(ptr._ptr) { ptr._ptr = nullptr; }

  pointer release() {
    pointer tmp = _ptr;
    _ptr = nullptr;
    return tmp;
  };  // Releases the ownership of the managed object
  void reset(pointer ptr) {
    free();
    _ptr = ptr;
  };                              // Replaces the managed object
  pointer get() { return _ptr; }  // Returns a pointer to the managed object
  explicit operator bool() const {
    return (_ptr != nullptr) ? true : false;
  }  // like get() != nullptr
  pointer operator->() const { return &(this->operator*()); }
  T& operator*() const { return *_ptr; }
  T& operator[](size_t index) { return &(_ptr + index); };
  ~UniquePtr() { free(); }

 private:
  pointer _ptr{nullptr};
  void free() {  F(_ptr);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
};
