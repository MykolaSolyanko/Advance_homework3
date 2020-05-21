#include "Stack.hpp"
#include "Vector.hpp"
#include <iostream>

int main(int argc, char const *argv[]) {
  std::cout << "This program realizes vector\n";
  std::cout << std::boolalpha;
  {
    std::cout << "V1 - size init\n";
    Vector<pair> v1{3};
    v1.analize();

    std::cout << "V2 - initializer_list\n";
    Vector<pair> v2{{true, "1"}, {false, "2"}, {true, "3"}};
    v2.analize();
    v2.resize(5);
    v2.analize();

    {
      std::cout << "V3 - int array begin, end init\n";
      int array[5]{5, 4, 3, 2, 1};
      int *ar_begin = {array};
      int *ar_end = {array + 5};
      Vector<int> v3(ar_begin, ar_end);
      std::cout << "CHECK: Analize? \n";
      v3.analize();

      Vector<int> vec{v3};
      vec.push_front(10);
      vec.resize(11);
      vec.analize();
      std::cout << "VEC emplace back\n";
      vec.emplace_back(1, 2, 3, 1);
      vec.analize();
    }

    std::cout << "V4 - Vector <Pair> begin, end init\n";
    Vector<pair> v4(v2.begin(), v2.end());
    v4.analize();

    std::cout << "V5 - Vector init\n";
    Vector<pair> v5(v2);
    v5.analize();
    v5.resize(2);
    v5.analize();

    std::cout << "V6 - Vector move init\n";
    Vector<pair> v6(std::move(v5));
    v6.analize();
    std::cout << "CHECK: Analize moved Vector? \n";
    v5.analize();

    std::cout << "V5 Operators\n";
    v5 = v6;
    std::cout << "CHECK: After opertor=? \n";
    v5.analize();
    v5 = std::move(v4);
    std::cout << "CHECK: Vector after move opertor? \n";
    v5.analize();
    std::cout << "CHECK: Moved Vector? \n";
    v4.analize();

    std::cout << "V5 Front and back\n";
    std::cout << "CHECK: Vector before front/back? \n";
    v5.analize();
    std::cout << "Front: " << (v5.front()).second << std::endl;
    std::cout << "Back: " << (v5.back()).second << std::endl;

    std::cout << "V5 push front/back\n";
    std::cout << "Push FRONT\n";
    v5.push_front({false, "0.1"});
    v5.push_front({true, "0.2"});
    std::cout << "CHECK: Vector after push front? \n";
    v5.analize();
    std::cout << "Push BACK\n";
    v5.push_back({false, "0.4"});
    std::cout << "CHECK: Vector after push back? \n";
    v5.analize();
  }

  {
    std::cout << "V7 insert\n";
    Vector<pair> v7{2};
    v7.analize();
    v7.resize(6);
    v7.insert(0, {true, "0"});
    v7.insert(1, {false, "1"});
    v7.insert(3, {true, "4"});
    v7.insert(0, {false, "0.1"});
    v7.insert(4, {true, "3"});
    v7.insert(6, {false, "6"});
    v7.insert(7, {true, "7"});
    std::cout << "CHECK: Vector after inserts? \n";
    v7.analize();

    std::cout << "V7 erase\n";
    v7.erase(1);
    std::cout << "CHECK: Vector after erase pos? \n";
    v7.analize();
    v7.erase(v7.begin() + 1);
    std::cout << "CHECK: Vector after *erase? \n";
    v7.analize();
    v7.erase(v7.begin() + 1, (v7.end() - 1));
    std::cout << "CHECK: Vector after begin/end erase? \n";
    v7.analize();

    std::cout << "V7 operator []\n";
    std::cout << v7[0].second << std::endl;
    std::cout << v7[1].second << std::endl;
    v7[1].second = "1";
    std::cout << v7[1].second << std::endl;
    v7.analize();

    std::cout << "V7 emplace back\n";
    v7.emplace_back(true, "16");
    v7.emplace_back(false, "34");
    v7.analize();
    
    std::cout << "V7 clear\n";
    v7.clear();
    v7.analize();
  }
  
  {
   std::cout << "Reserve V8\n";
   Vector<int> v8{1, 2, 3, 4, 5};
   v8.analize();
   v8.reserve(sizeof(int) * 10);
   v8.analize();
   std::cout << "V8 adress:\n" << &v8 << std::endl;

   Vector<int> *v_ptr = new (&v8) Vector<int>{10, 11, 12, 13, 14};
   td::cout << "v_ptr placement new v9 adress:\n" << v_ptr << std::endl;
   v_ptr->analize();
  }
  
  {
    std::cout << "Stack-Adapter\n";
    Stack<pair, Vector<pair>> st;
    std::cout << "Adapter capacity: " << st.GetCapacity() << std::endl;
    std::cout << "Adapter size: " << st.GetSize() << std::endl;
    std::cout << "Vector analize call thought Stack\n";
    st.analize();

    std::cout << "Steck PUSH\n";
    pair st_check = st.push({false, "10"});
    std::cout << "Push result? " << st_check.second << std::endl;
    st.analize();
    for (size_t i{}; i != 4; i++) {
      st.push({true, "11"});
    }
    st.push({true, "16"});
    st.push({false, "37"});
    st.push({true, "29"});
    st.analize();

    {
      std::cout << "Popping start\n";
      size_t tmp_size{st.GetSize()};
      for (size_t i{}; i != tmp_size; i++) {
        pair st_check = st.pop();
        std::cout << st_check.second << std::endl;
        if (st.GetSize() != 0) {
          std::cout << "Top element: " << st.top().first
                    << st.top().second.second << std::endl;
        }
      }
      st.analize();
    }

    st.emplace<pair>({true, "16"}, {false, "37"});
    st.analize();
  }

  std::cout << "End of program\n";
  return 0;
}
