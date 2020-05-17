#pragma once
#include "Deleters.hpp"

template <typename T, typename Del = Del_default<T>> class shared_ptr {
public:
  shared_ptr() = default;
  shared_ptr(T &value) : ptr(&value) { std::cout << __FUNCTION__ << std::endl; }
  shared_ptr(T *&value) : ptr(&value) {
    std::cout << __FUNCTION__ << std::endl;
  }

  ~shared_ptr() = default;

  T &operator*() { return *ptr; }
  void operator=(T &rhs) { ptr = &rhs; }
  void operator=(T *&rhs) { ptr = rhs; }

  T *ptr{};

private:
  Del del;
};

template <typename T, typename Del> class shared_ptr<T[], Del> {
public:
  shared_ptr() = default;
  shared_ptr(T &value) : ptr(&value) { std::cout << __FUNCTION__ << std::endl; }
  shared_ptr(T *&value) : ptr(&value) {
    std::cout << __FUNCTION__ << std::endl;
  }

  ~shared_ptr() = default;

  T &operator*() { return *ptr; }
  void operator=(T &rhs) { ptr = &rhs; }
  void operator=(T *&rhs) { ptr = rhs; }

  T *ptr{};

private:
  Del del;
};
