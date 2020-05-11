
#include <iostream>
#include "../../HomeWork1/Taras_Samchuk_HW1/DEBUG1.code.hpp"

template <typename T, typename F>
class UniquePtr {
 public:
  typedef T* pointer;

  UniquePtr() = default;
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr(pointer);

  pointer release() {
    pointer copy = ptr;
    ptr = nullptr;
    return copy;
  };  // Releases the ownership of the managed object
  void reset(pointer /* ptr */ t) {
    free();
    ptr = t;
  };                              // Replaces the managed object
  pointer get() { return ptr; };  // Returns a pointer to the managed object
  explicit operator bool() {
    return ptr ? true : false;
  };  // like get() != nullptr
  pointer operator->() { return &(this->operator*()); };
  T& operator*();
  T& operator[](size_t i);  // if Unique_ptr store array
 private:
  pointer ptr{nullptr};
  void free() { F(ptr); };
};

template <typename T>
class Deleter {
 public:
  void operator()(T* p) { delete p; }
};

template <typename T[]>
class Deleter {
 public:
  void operator()(UniquePtr<T>::pointer p) { delete[] p; }
};

template <typename T, typename F = Deleter<T>>
class UniquePtr;
