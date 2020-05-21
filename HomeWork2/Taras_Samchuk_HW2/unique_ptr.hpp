#pragma once
#include <iostream>

template <typename T>
struct uDeleter {
 public:
  // typedef T* pointer;
  void operator()(T* ptr){
    std::cout<<"this is funcor -"<<ptr<<std::endl;
    // std::cout << "()-----------------\n";
    delete ptr;
  }
};

template <typename T>
struct uDeleter<T[]> {
 public:
  // typedef T* pointer;
  void operator()(T* ptr) {
    std::cout << "this is funcor []" << ptr << std::endl;
    // std::cout << "()-----------------\n";
    delete[] ptr;
  }
};

template <typename T, typename F = uDeleter<T>>
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

  // Releases the ownership of the managed object
  pointer release() {
    pointer tmp = _ptr;
    _ptr = nullptr;
    return tmp;
  };
  // Replaces the managed object
  void reset(pointer ptr) {
    free();
    _ptr = ptr;
  };
  // Returns a pointer to the managed object
  pointer get() { return _ptr; }
  // like get() != nullptr
  explicit operator bool() const { return (_ptr != nullptr) ? true : false; }
  pointer operator->() const { return &(this->operator*()); }
  T& operator*() const { return *_ptr; }
  T& operator[](size_t index);  // {  };
  ~UniquePtr() { free(); }

 private:
  pointer _ptr{nullptr};
  void free() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    F DELER;
    DELER(_ptr);
  }
};

// template <typename T, typename F>
// T& UniquePtr<T, F> operator[](size_t index) = delete;

// template <typename T, typename F>
// T& UniquePtr<T*, F> operator[](size_t index) {
//   return &(_ptr + index);
// };
