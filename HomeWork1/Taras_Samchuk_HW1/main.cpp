/*
    Used for testing
*/

#include <iostream>
#include "stack.hpp"
#include "vector.hpp"

template <typename... Args>
void LogMessage(Args&&... Values) {
  (std::cout << ... << Values);
}

using TypeForTest = int;

constexpr size_t k_TryCount1{33};
constexpr size_t k_TryCount2{50};
constexpr size_t k_TestSize1{20};
constexpr size_t k_TestSize2{10};

// Parameters not used  -Wextra -Werror
int main(/*int argc, char const *argv[]*/) {
  std::cout << R"(
+----------------------------------------------------+
|             TRY VECTOR                             |
+----------------------------------------------------+
  )" << std::endl;
  { Vector<TypeForTest> TEST; }
  { Vector<TypeForTest> TEST{k_TestSize1}; }
  {
    LogMessage("\t\t\tTest methods\n");
    LogMessage("==========================================\n");
    Vector<TypeForTest> TEST;  //{k_TestSize2};
    TEST.push_back(3);
    LogMessage("TEST.push_back(3)\n");
    LogMessage("begin():", TEST.begin(), "\n");
    LogMessage("end():", TEST.end(), "\n");
    LogMessage("count():", TEST.size(), "\n");
    LogMessage("capacity():", TEST.capacity(), "\n");
    // TEST.insert(std::to_string(3));
    //   LogMessage("insert(3)://todo\n");
    for (size_t i{0}; i < k_TryCount1; i++) {
      TEST.push_front(3);
    };
    LogMessage("count():", TEST.size(), "\n");
    TEST.erase(TEST.begin(), TEST.end());
    LogMessage("begin():", TEST.begin(), "\n");
    LogMessage("end():", TEST.end(), "\n");
    LogMessage("count():", TEST.size(), "\n");
    LogMessage("capacity():", TEST.capacity(), "\n");
    for (size_t i{0}; i < k_TryCount2; i++) {
      TEST.push_back(3);
    };
    for (size_t i{0}; i < TEST.capacity(); i++) {
      TEST[i] = i * 10;
    }
    for (size_t i{0}; i < TEST.capacity(); i++) {
      LogMessage("ellem[", i, "]=", TEST[i], " ");
    }
    LogMessage("\n");
    Vector<TypeForTest> TEST2;
    TEST2 = TEST;
    LogMessage("begin():", TEST2.begin(), "\n");
    LogMessage("end():", TEST2.end(), "\n");
    LogMessage("count():", TEST2.size(), "\n");
    LogMessage("capacity():", TEST2.capacity(), "\n");
  }
  std::cout << R"(
+----------------------------------------------------+
|             TRY STACK                              |
+----------------------------------------------------+
  )" << std::endl;
  { Stack<TypeForTest> test; }
  {
    LogMessage("\t\t\tTest with param\n");
    Stack<TypeForTest, Vector<TypeForTest>> test(k_TestSize1);
  }

  {
    LogMessage("\t\t\tTest methods\n");
    Stack<TypeForTest> test(k_TestSize2);
    LogMessage("Empty:", test.isEmpty(), " Count:", test.getCount(),
               " Size:", test.getMaxSize(), "\n");
    for (size_t i{0}; i < k_TryCount1; i++) {
      test.push(i);
    };
    LogMessage("stack.top():", test.top(), "\n");
    for (size_t i{0}; i < k_TryCount2; i++) {
      LogMessage("test.pop():", test.pop(), " \n");
    };
    LogMessage("\n");
  };
  return 0;
}
