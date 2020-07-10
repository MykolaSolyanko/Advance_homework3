#pragma once

template <typename T> class Deleter {
public:
  void operator()(T *data) {
    std::cout << __FUNCSIG__ << std::endl;
    delete data;
  }
};

template <typename T> class Deleter<T[]> {
public:
  void operator()(T *data) {
    std::cout << __FUNCSIG__ << std::endl;
    delete[] data;
  }
};
template <typename T> class FDeleter {
public:
  void close_file(std::FILE *fp) {
    std::cout << __FUNCSIG__ << std::endl;
    std::fclose(fp);
  }
};
