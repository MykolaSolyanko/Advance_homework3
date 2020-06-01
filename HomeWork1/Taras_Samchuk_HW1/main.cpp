/*
    Used for testing
*/

#include <iostream>
#  include "vektor.hpp"
#  include "stek.hpp"

template <typename... Args>
void LogMessage(Args... Values) {
  (std::cout << ... << Values);
}

using DEBUGER = int;

static constexpr size_t k_TryCount1{33};
static constexpr size_t k_TryCount2{50};
static constexpr size_t k_TestSize1{20};
static constexpr size_t k_TestSize2{10};

// Parameters not used  -Wextra -Werror 
int main(/*int argc, char const *argv[]*/) {
  std::cout<<R"(
+----------------------------------------------------+
|             TRY VECTOR                             |
+----------------------------------------------------+
  )"<<std::endl;
  {
      // Vector<DEBUGER> TEST;//no default constructor
  } {
    Vector<DEBUGER> TEST{k_TestSize1};
  }
  {
    LogMessage("\t\t\tTest methods\n");
    Vector<DEBUGER> TEST{k_TestSize2};
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
  }
  std::cout << R"(
+----------------------------------------------------+
|             TRY STACK                              |
+----------------------------------------------------+
  )" << std::endl;
  {
      // Stack<DEBUGER> test;  //no default constructor
  } {
    LogMessage("\t\t\tTest with param\n");
    Stack<DEBUGER, Vector<DEBUGER>> test(k_TestSize1);
  }

  {
    LogMessage("\t\t\tTest methods\n");
    Stack<DEBUGER> test(k_TestSize2);
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
