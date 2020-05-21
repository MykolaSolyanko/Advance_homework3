#pragma once
using pair = std::pair<bool, const char *>;

template <typename T, class Vector> class Stack {
public:
  pair push(T value) {
    if (vec.size_() > vec.capacity_()) {
      return {false, "Stack full"};
    }
    vec.push_back(value);
    return {true, "Push success"};
  }
  pair pop() {
    if (vec.size_() == 0) {
      return {false, "Stack clear"};
    }
    vec.erase(vec.end());
    return {true, "Pop success"};
  }

  void clear() {
    if (vec.size_() == 0) {
      return;
    }
    vec.clear();
  }

  std::pair<bool, T> top() {
    // runtime error if size == 0 because of no default init for clear T element
    if (vec.size_() == 0) {
      return {false, vec.back()};
    }

    return {true, vec.back()};
  }

template <typename... Rest> void emplace(Rest... rest) {
  std::cout << __FUNCTION__ << std::endl;
  vec.push_back(T{rest...});
}

  const unsigned long long GetSize() { return vec.size_(); }
  const unsigned long long GetCapacity() { return vec.capacity_(); }
  void analize() { vec.analize(); }

private:
  // vec size init to do default init for elements
  Vector vec{4};
};
