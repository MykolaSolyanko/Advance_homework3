// #include "unique_ptr.hpp"
#include "../../HomeWork1/Taras_Samchuk_HW1/DEBUG1.code.hpp"
#include "unique_ptr.code.hpp"
#include <array>
int main(/* int argc, char const *argv[] */) {
  DEBUG;
  {
    UniquePtr<int[5]> TEST;
    LogMessage(TEST.get(), "\n");
  }
  {
    UniquePtr<std::array<int,6>> TEST2;
    // TEST2[3];
  }
  return 0;
}
