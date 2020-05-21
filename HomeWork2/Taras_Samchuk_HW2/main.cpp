// #include "unique_ptr.hpp"
#include <fstream>
#include "../../HomeWork1/Taras_Samchuk_HW1/DEBUG1.code.hpp"
#include "shared_ptr.hpp"
#include "unique_ptr.hpp"
int main(int argc, char const *argv[]) {
  DEBUG;
  {
    LogMessage("UniquePtr<int> ptr1{new int{}}\n");
    UniquePtr<int> ptr1{new int{}};  // use ~Unique_ptr() {delete ptr;}
  }

  {
    LogMessage("UniquePtr<int[]> ptr2{new int[200]{}};\n");
    // UniquePtr<int[]> ptr2{new int[200]{}};  // use ~Unique_ptr() {delete[]
    // ptr;}
  }
  {
    LogMessage("Unique_ptr<File> ptr{file, fclose};\n");
    auto file = fopen("Makefile", "r");
    // UniquePtr<std::FILE> ptr{file, fclose};  // use ~Unique_ptr()
    // {fclose(ptr);}
  }
  {
    LogMessage("UniquePtr<int> ptr_{new int{}};\n");
    UniquePtr<int> ptr{new int{}};

    LogMessage(
        "UniquePtr<int> ptr_copy{ptr};              // compiler error\n"
        "UniquePtr<int> ptr_copy{std::move(ptr)};   // compiler OK}\n");
    // UniquePtr<int> ptr_copy{ptr};             // compiler error
    UniquePtr<int> ptr_copy{std::move(ptr)};  // compiler OK}
  }
  //==================================================================
  {
    SharedPtr<int> ptr1{new int{}};  // use ~Shared_ptr() {delete ptr;}
  }
  {
    // SharedPtr<int[]> ptr2{new int[200]{}};  // use ~Shared_ptr() {delete[] ptr;}
  }

  {
    // auto file = fopen(file_name);
    // SharedPtr<File> ptr{file, fclose};  // use ~Shared_ptr() {fclose(ptr);}
  }

  {
    // SharedPtr<int> ptr_{new int{}};

    // std::cout << ptr.count() << std::endl;  // print 1

    // SharedPtr<int> ptr_copy{ptr};

    // std::cout << ptr_copy.count() << std::endl;  // print 2
    // SharedPtr<int> ptr_move{std::move(ptr)};

    // std::cout << ptr_copy.count() << std::endl;  // print 2
    // std::cout << ptr.count() << std::endl;       // print 0
  }

  return 0;
};
