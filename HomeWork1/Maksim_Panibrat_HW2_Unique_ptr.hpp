#pragma once
#include "Deleters.hpp"

template <typename T, typename Del = Del_default<T>> struct unique_ptr {
public:
  unique_ptr(T &value) {
    std::cout << __FUNCTION__ << std::endl;
    ptr = &value;
  }
  unique_ptr(T *&value) {
    std::cout << __FUNCTION__ << std::endl;
    ptr = value;
    value = nullptr;
  }

  ~unique_ptr() = default;

  T &operator*() { return *ptr; }
  void operator=(T &rhs) { ptr = &rhs; }
  void operator=(T *&rhs) {
    ptr = rhs;
    rhs = nullptr;
  }

  T *ptr;

private:
  Del del;
};

template <typename T, typename Del> struct unique_ptr<T[], Del> {
public:
  unique_ptr(T &value) {
    std::cout << __FUNCTION__ << std::endl;
    ptr = &value;
  }
  unique_ptr(T *&value) {
    std::cout << __FUNCTION__ << std::endl;
    ptr = &value;
    value = nullptr;
  }

  ~unique_ptr() {
    std::cout << __FUNCTION__ << std::endl;
    del(ptr);
  }

  T &operator*() { return *ptr; }
  void operator=(T &rhs) { ptr = &rhs; }
  void operator=(T *&rhs) {
    ptr = rhs;
    rhs = nullptr;
  }

  T *ptr;

private:
  Del del;
};
