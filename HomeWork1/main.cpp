#include "Stack.hpp"
#include "Vector.hpp"
#include <initializer_list>
#include <iostream>

class Test {
public:
  Test() = default;
  Test(int size) { std::cout << __FUNCSIG__ << std::endl; }
  Test(int size, bool b) { std::cout << __FUNCSIG__ << std::endl; }
  Test(const Test &) { std::cout << __FUNCSIG__ << std::endl; }
  Test(Test &&) noexcept { std::cout << __FUNCSIG__ << std::endl; }
  Test operator=(const Test &) noexcept {
    std::cout << __FUNCSIG__ << std::endl;
    return *this;
  }
  Test operator=(Test &&) noexcept {
    std::cout << __FUNCSIG__ << std::endl;
    return *this;
  }
  ~Test() { std::cout << __FUNCSIG__ << std::endl; };
};
int main() {
  Vector<Test> vt(10);
  Stack<Test> st(5);
  Test t;
  st.push(t);
  Vector<int> DfV;
  Vector<int> V(4);
  Vector<int> V2({11, 12, 13, 14});
  std::cout << V2.size() << std::endl;
  std::cout << V2.capacity() << std::endl;
  Vector<int> V1(V2);
  int *arr = new int[5]{99, 98, 97, 96, 95};
  Vector<int> Vbe(arr, arr + 4);
  V1 = Vbe;
  int *p1 = &Vbe[1];
  int *p2 = &Vbe[2];
  Vbe.erase(p1, p2);
  Vbe.emplace_back(22);
  Vbe.emplace_back(arr[0]);
  Vbe.insert(&Vbe[2], 100);
  Vbe.push_front(arr[1]);
  Vbe.push_front(101);
  int *ptr = Vbe.begin();
  Vbe.erase(ptr, (ptr + 2));
  delete[] arr;
  return 0;
}
