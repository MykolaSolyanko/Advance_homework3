#include "Shared_ptr.hpp"
#include "Unique_ptr.hpp"
#include <iostream>
#include <utility>

using pair = std::pair<bool, const char *>;

int main() {
  std::cout << std::boolalpha;
  std::cout << "This program realizes unique and shared ptr\n";
  int val1 = 15;
  int val2 = 51;
  int *val_ptr = &val1;

  std::cout << "unique_ptr1 int\n";
  unique_ptr un_ptr1(val_ptr);

  std::cout << "operator * :  " << *un_ptr1 << std::endl;
  int new_val1 = 23;
  un_ptr1 = new_val1;
  std::cout << "operator = int val :  " << *un_ptr1 << std::endl;
  int new_val2 = 34;
  int *val_ptr2 = &new_val2;
  un_ptr1 = val_ptr2;
  std::cout << "operator = ptr :  " << *un_ptr1 << std::endl;

  std::cout << "shared_ptr1 int\n";
  shared_ptr sh_ptr1(val2);
  std::cout << "operator * :  " << *sh_ptr1 << std::endl;

  std::cout << "unique_ptr2 pair\n";
  pair pair1{true, "1"};
  unique_ptr un_ptr2(pair1);
  std::cout << "pair.first: " << (*un_ptr2).first
            << "\n pair.second: " << (*un_ptr2).second << std::endl;

  std::cout << "End of program\n";
  return 0;
}
