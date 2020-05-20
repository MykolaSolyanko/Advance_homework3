// #include "unique_ptr.hpp"
#include <fstream>
#include "../../HomeWork1/Taras_Samchuk_HW1/DEBUG1.code.hpp"
#include "unique_ptr.hpp"
int main(/* int argc, char const *argv[] */) {
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
    return 0;
  }
