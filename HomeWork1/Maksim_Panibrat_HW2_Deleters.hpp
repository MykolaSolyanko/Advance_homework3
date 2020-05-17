#pragma once

template <typename T> struct Del_default {
  void operator()(T *data) {
    std::cout << "1" << std::endl;
    delete data;
  }
};

template <typename T> struct Del_default<T[]> {
  void operator()(T *data) {
    std::cout << "2" << std::endl;
    delete[] data;
  }
};
