#include "Deleter.hpp"
#include "Unique_ptr.hpp"
#include <fstream>
#include <iostream>
#include <utility>

int main() {

  Unique_ptr<int, Deleter<int>> Uptr(new int{11});
  std::cout << Uptr.ptr << std::endl;
  Unique_ptr<int, Deleter<int[]>> Uptr1(new int[5]{1, 2, 3, 4, 5});

  int i = 111;
  int *a{&i};
  Unique_ptr<int, Deleter<int>> Uptr2 = a;
  std::cout << *Uptr2.ptr << std::endl;
  Unique_ptr<int, Deleter<int>> Uptr3(std::move(Uptr2));
  std::cout << Uptr2.ptr << std::endl;
  std::cout << Uptr3.ptr << std::endl;

  return 0;
}
