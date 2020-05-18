/*
          stek.hpp by Sam4uk
*/
#pragma once
#include "vektor.hpp"

template <class T, class Cont = Vector<T>>
class Stack {
 public:
  // Stack() = default;
  Stack(const size_t size) { proxy.reserve(size); };
  ~Stack() = default;

  void push(const T& value) { proxy.push_front(value); };
  T top() {
    if (proxy.empty()) {
      return {};
    }
    return proxy.front();
  };
  T pop() {
    if (proxy.empty()) {
      return {};
    };
    T tmp = top();
    proxy.erase(proxy.end());
    return tmp;
  };

  void clear() {
    if (!proxy.empty()) {
      return;
    }
    proxy.erase(proxy.begin(), proxy.end());
  };

  bool isEmpty() const { return proxy.empty(); };

  size_t getCount() const { return proxy.size(); };
  size_t getMaxSize() const { return proxy.capacity(); };

 private:
  Cont proxy;
};
