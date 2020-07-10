#pragma once
#include <iostream>
template <class T, class Cont = Vector<T>> class Stack {

public:
  Stack() = default;
  Stack(const size_t new_capacity) { proxy.reserve(new_capacity); };
  ~Stack() = default;
  bool empty() const { return proxy.empty(); };
  size_t size() const { return proxy.size(); };
  size_t capacity() const { return proxy.capacity(); };
  T top() { return proxy.back(); };
  void push(const T &value) { proxy.push_back(value); };
  void push(T &&value) { proxy.push_back(std::move(value)); };

  T pop() {
    T stack_top = top();
    proxy.erase(proxy.end());
    return stack_top;
  };
  template <typename... Rest> void emplace(Rest &&... rest) {
    push({std::forward<Rest>(rest)...});
  }

private:
  Cont proxy;
};
