#pragma once
#include <utility>

template <typename T> class Vector {
public:
  Vector() = default;
  Vector(size_t size) {
    std::cout << __FUNCTION__ << std::endl;
    capacity = size;
    data = new T[capacity]{};
  }
  Vector(const std::initializer_list<T> &list) : Vector(list.size()) {
    std::cout << __FUNCTION__ << std::endl;
    T *i = begin();
    for (auto &element : list) {
      *i = std::move(element);
      i++;
      size++;
    }
  }
  Vector(T *rhs_begin, T *rhs_end) {
    std::cout << __FUNCTION__ << std::endl;
    capacity = std::distance(rhs_begin, rhs_end);
    data = new T[capacity]{};
    for (T *d_begin{data}; rhs_begin != rhs_end; d_begin++, rhs_begin++) {
      *d_begin = std::move(*rhs_begin);
      size++;
    }
  }
  Vector(const Vector &rhs)
      : capacity{rhs.capacity_()}, size{rhs.size_()}, data{new T[capacity]{}} {
    std::cout << __FUNCTION__ << std::endl;
    if constexpr (std::is_arithmetic<T>::value) {
      std::memcpy(&data, &rhs.data, size);
    }
    for (size_t i{}; i != size; i++) {
      data[i] = rhs.data[i];
    }
  }
  Vector(Vector &&rhs) noexcept
      : capacity{rhs.capacity_()}, size{rhs.size_()}, data{rhs.data} {
    std::cout << __FUNCTION__ << std::endl;
    rhs.data = nullptr;
    rhs.size = 0;
    rhs.capacity = 0;
  }
  ~Vector() = default;

  Vector &operator=(const Vector &rhs) {
    std::cout << __FUNCTION__ << std::endl;
    capacity = rhs.capacity_();
    size = rhs.size_();
    data = new T[capacity]{};
    if constexpr (std::is_arithmetic<T>::value) {
      std::memcpy(&data, &rhs.data, size);
      return *this;
    }
    for (size_t i{}; i != size; i++) {
      data[i] = rhs.data[i];
    }
    return *this;
  }

  Vector &operator=(Vector &&rhs) noexcept {
    std::cout << __FUNCTION__ << std::endl;
    capacity = rhs.capacity_();
    size = rhs.size_();
    data = new T[capacity]{};
    data = rhs.data;
    rhs.data = nullptr;
    rhs.size = 0;
    rhs.capacity = 0;
    return *this;
  }

  const T &operator[](size_t pos) const { return data[pos]; }
  T &operator[](size_t pos) { return data[pos]; }

  size_t capacity_() const { return capacity; }
  size_t size_() const { return size; }
  bool empty() {
    if (size == 0) {
      return true;
    }
    return false;
  }

  T *begin() { return {data}; }
  T *end() const { return {data + size}; }

  void push_front(T value) {
    std::cout << __FUNCTION__ << std::endl;
    if ((size + 1) >= capacity) {
      capacity *= 2;
    }
    T *tmp_array = new T[capacity]{};
    tmp_array[0] = value;
    for (int i{}; i != size; i++) {
      tmp_array[i + 1] = std::move(data[i]);
    }

    data = tmp_array;
    size++;
  }

  void push_back(T value) {
    std::cout << __FUNCTION__ << std::endl;
    if ((size + 1) >= capacity) {
      resize(capacity * 2);
    }
    data[size] = std::move(value);
    size++;
  }

  template <typename... Rest> void emplace_back(Rest... rest) {
    std::cout << __FUNCTION__ << std::endl;
    push_back(T{rest...});
  }

  void insert(size_t pos, T value) {
    std::cout << __FUNCTION__ << std::endl;
    if ((pos + 1) > size) {
      pos = size;
      size++;
      if (size > capacity) {
        resize(size);
      }
    }
    data[pos] = std::move(value);
  }

  void erase(size_t pos) {
    if ((pos + 1) > size) {
      pos = size;
    }
    T *tmp_arr = new T[capacity];

    size_t i{};
    for (; i != pos; i++) {
      tmp_arr[i] = std::move(data[i]);
    }
    for (; i != size; i++) {
      tmp_arr[i] = std::move(data[i + 1]);
    }
    data = tmp_arr;
    size--;
  }
  void erase(T *pos) {
    if (pos > end()) {
      pos = end();
    }
    T *tmp_arr = new T[capacity];

    T *tmp_ptr{tmp_arr};
    T *d_begin{data};
    for (; d_begin != pos; d_begin++, tmp_ptr++) {
      *tmp_ptr = std::move(*d_begin);
    }
    if (d_begin != end()) {
      d_begin++;
      for (T *d_end{data + size}; d_begin != d_end; d_begin++, tmp_ptr++) {
        *tmp_ptr = std::move(*d_begin);
      }
    }
    data = tmp_arr;
    size--;
  }
  void erase(T *begin, T *end) {
    size_t erase_distance = std::distance(begin, end);
    T *tmp_arr = new T[capacity];

    T *tmp_begin{tmp_arr};
    T *d_begin{data};
    for (; d_begin != begin; d_begin++, tmp_begin++) {
      *tmp_begin = std::move(*d_begin);
    }
    d_begin += erase_distance;
    for (T *d_end{data + size}; d_begin != d_end; d_begin++, tmp_begin++) {
      *tmp_begin = std::move(*d_begin);
    }
    data = tmp_arr;
    size -= erase_distance;
  }

void reserve(size_t new_cap) {
  std::cout << __FUNCTION__ << std::endl;

  T *tmp_arr = (T *)std::malloc(new_cap * sizeof(T));
  if (tmp_arr == nullptr) {
    std::cout << "alloc failure\n";
    exit('a');
  }

  tmp_arr = new (tmp_arr) T[capacity];
  // is it greater than just: tmp_arr = new T[capacity] ?

  if constexpr (std::is_arithmetic<T>::value) {
    std::memcpy(tmp_arr, data, sizeof(T) * size);
  } else {
    for (size_t i{}; i != size; i++) {
      tmp_arr[i] = std::move(data[i]);
    }
  }
  data = tmp_arr;
}


  void resize(size_t new_size) {
    std::cout << __FUNCTION__ << std::endl;
    if (new_size < size) {
      size = new_size;
    }
    capacity = new_size;
    T *tmp_arr = new T[capacity]{};
    if constexpr (std::is_arithmetic<T>::value) {
      std::memcpy(tmp_arr, data, sizeof(T)*size);
    }
    else {
      for (size_t i{}; i != size; i++) {
       tmp_arr[i] = std::move(data[i]);
      }
    }
    data = tmp_arr;
  }

  void clear() {
    size = 0;
    data = new T[capacity];
  }

  T &front() { return {data[0]}; }
  T &back() { return {data[size - 1]}; }

  void print_pair() {
    for (int i{}; i != size; i++) {
      std::cout << data[i].first << data[i].second << std::endl;
    }
  }
  void print_arithmetic() {
    for (int i{}; i != size; i++) {
      std::cout << data[i] << std::endl;
    }
  }

  void analize() {
    std::cout << "CHECK: Empty? " << empty() << std::endl;
    std::cout << "Capacity: " << capacity << std::endl;
    std::cout << "Size: " << size << std::endl;
    if (size != 0) {
      std::cout << "Print vector: \n";
      if constexpr (std::is_same<std::pair<bool, const char *>, T>::value) {
        print_pair();
        return;
      }
      else if constexpr (std::is_arithmetic<T>::value) {
        print_arithmetic();
        return;
      }
      else {
        std::cout << "Cant print\n";
      }
    }
  }

private:
  size_t capacity{4};
  T *data{};
  size_t size{};
};
