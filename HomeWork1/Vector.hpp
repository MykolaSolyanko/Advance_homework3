#pragma once
#include <iostream>
#include <utility>
const size_t MAX_CAPACITY = 100;
template <class T> class Vector {
public:
  Vector() = default;
  explicit Vector(size_t size);
  explicit Vector(const Vector &);
  Vector(std::initializer_list<T> list);
  Vector(T *begin, T *end);
  ~Vector();
  Vector &operator=(const Vector &);
  T &operator[](size_t pos) { return vdata[pos]; };
  const T &operator[](size_t pos) const { return vdata[pos]; };
  void insert(T *position, const T &value);
  void erase(T *begin, T *end);
  void erase(T *pos);
  void erase(size_t pos);
  void push_front(const T &value);
  void push_front(T &&value);
  T *begin();
  const T *end();
  void push_back(const T &value);
  void push_back(T &&value);
  T front();
  T back();
  void resize(size_t size);
  void reserve(size_t new_capacity);
  size_t size();
  size_t capacity();
  bool empty();
  template <typename... Rest> void emplace_back(Rest &&... rest) {
    push_back({std::forward<Rest>(rest)...});
  }

private:
  T *re_cap();
  size_t vsize{};
  size_t vcapacity{8};
  T *vdata = new T[vcapacity]{};
};

template <class T> Vector<T>::~Vector() { delete[] vdata; }
template <class T> T *Vector<T>::re_cap() {
  if (vsize == vcapacity) {
    if (vcapacity < (MAX_CAPACITY / 2)) {
      vcapacity = vcapacity * 2;

    } else if (vcapacity < MAX_CAPACITY) {
      vcapacity++;
    } else {
      std::cout << "no capacity" << std::endl;
      return vdata;
    }

    T *temp = new T[vcapacity]{};
    for (size_t i = 0; i < vsize; i++) {
      temp[i] = vdata[i];
    }
    std::cout << std::endl;
    return temp;
  } else {
    return vdata;
  }
};

template <class T>
Vector<T>::Vector(size_t size)
    : vsize{size}, vcapacity{size}, vdata{new T[size]{}} {};
template <class T>
Vector<T>::Vector(const Vector &rhs)
    : vsize{rhs.vsize}, vcapacity{rhs.vcapacity} {
  for (size_t i = 0; i < vsize; ++i) {
    vdata[i] = rhs.vdata[i];
  }
};
template <class T>
Vector<T>::Vector(std::initializer_list<T> list)
    : vsize{list.size()}, vcapacity{list.size() + 1} {
  int index{};
  for (auto i : list) {
    vdata[index] = i;
    index++;
  }
};
template <class T> Vector<T>::Vector(T *begin, T *end) {
  if (begin == nullptr || end == nullptr) {
    return;
  }
  if (std::distance(begin, end) > MAX_CAPACITY) {
    std::cout << "STACK overflow \n";
    return;
  };
  vsize = 0;
  while ((begin + vsize) != (end + 1)) {
    *(vdata + vsize) = *(begin + vsize);
    vsize++;
    vdata = re_cap();
  };
};
template <class T> Vector<T> &Vector<T>::operator=(const Vector &rhs) {
  if (this == &rhs) {
    return *this;
  }
  vsize = rhs.vsize;
  vcapacity = rhs.vcapacity;
  vdata = new T[vcapacity];
  for (size_t i = 0; i < vsize; ++i) {
    vdata[i] = rhs.vdata[i];
  }
  return *this;
};
template <class T> void Vector<T>::erase(size_t pos) {
  if (pos < vsize) {
    for (size_t i = pos; i < vsize - 1; i++) {
      vdata[i - 1] = vdata[i];
    }
    vsize--;
    for (size_t i = vsize; i < vcapacity; i++) {
      vdata[i] = 0;
    }
  }
}
template <class T> void Vector<T>::erase(T *begin, T *end) {
  if (begin == nullptr || end == nullptr) {
    return;
  }
  if (begin < (vdata + vsize) && (begin <= end)) {
    if (end < (vdata + vsize - 1)) {
      T *tmp = begin;
      for (auto it = end + 1; it != (vdata + vsize); it++) {
        *begin++ = *it;
      }
      vsize = vsize - std::distance(tmp, end) - 1;
    } else if (end >= (vdata + vsize - 1)) {
      vsize = vsize - std::distance(begin, vdata + vsize - 1);
    }
  }
};
template <class T> void Vector<T>::erase(T *pos) {
  if (pos == nullptr) {
    return;
  }
  if (pos < (vdata + vsize) && (pos >= vdata)) {
    for (auto it = pos; it != (vdata + vsize); it++) {
      *it = *(it + 1);
    }
    vsize--;
    for (auto it = (vdata + vsize); it != (vdata + vcapacity); it++) {
      *it = 0;
    }
  }
};

template <class T> void Vector<T>::insert(T *position, const T &value) {

  vdata = re_cap();
  ++vsize;
  if (position < (vdata + vsize)) {

    for (auto it = (vdata + vsize - 1); it != position; --it) {
      *(it) = *(it - 1);
    }
    *(position) = value;
  }
};

template <class T> void Vector<T>::push_front(const T &value) {

  vdata = re_cap();
  for (int i = vsize; i > 0; i--) {
    vdata[i] = vdata[i - 1];
  }
  vdata[0] = value;
  vsize++;
};
template <class T> void Vector<T>::push_front(T &&value) {

  vdata = re_cap();
  for (int i = vsize; i > 0; i--) {
    vdata[i] = vdata[i - 1];
  }
  vdata[0] = std::move(value);
  vsize++;
};

template <class T> T *Vector<T>::begin() { return vdata; };
template <class T> const T *Vector<T>::end() { return vdata + vsize - 1; };

template <class T> void Vector<T>::push_back(const T &value) {

  vdata = re_cap();
  vdata[vsize++] = value;
};
template <class T> void Vector<T>::push_back(T &&value) {
  vdata = re_cap();
  vdata[vsize++] = std::move(value);
};
template <class T> T Vector<T>::front() { return *vdata; };
template <class T> T Vector<T>::back() { return *(vdata + vsize - 1); };
template <class T> void Vector<T>::resize(size_t size) {

  if (vcapacity <= size) {
    vcapacity = size;
  }
  vsize = size;
};
template <class T> void Vector<T>::reserve(size_t new_capacity) {

  if (vcapacity < new_capacity) {
    vcapacity = new_capacity;
  }
};
template <class T> size_t Vector<T>::size() { return vsize; };
template <class T> size_t Vector<T>::capacity() { return vcapacity; };
template <class T> bool Vector<T>::empty() { return (vsize == 0); };
