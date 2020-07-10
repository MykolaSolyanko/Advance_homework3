#pragma once
#include <memory>

template <class T, class Del> class Unique_ptr {

public:
  Unique_ptr() = default;
  Unique_ptr(const Unique_ptr &) = delete;
  Unique_ptr &operator=(const Unique_ptr &) = delete;
  Unique_ptr(Unique_ptr &&rhs) {
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
    del = rhs.del;
  }
  Unique_ptr &operator=(Unique_ptr &&rhs) {
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
    del = rhs.del;
    return *this;
  }
  Unique_ptr(T *value) {

    ptr = value;
    value = nullptr;
  }
  Unique_ptr(T &value) { ptr = &value; }
  ~Unique_ptr() {
    del(ptr); // вываливаюсь в рантайм еррор почему-то delete_scalar.cpp
  };

  void operator=(T &rhs) { ptr = &rhs; }
  void operator=(T *&rhs) {
    ptr = rhs;
    rhs = nullptr;
  }
  T *operator->() const { return ptr; }
  T &operator*() const { return *ptr; }
  T *ptr{};

private:
  Del del;
};
