#include "Vector.hpp"
#include "Stack.hpp"
#include "Functions_List.h"

void check_vector_constructors() {
    std::cout << "Vector constructors\n";
    std::cout << "V1 - size init\n";
    Vector <pair> v1{ 3 };
    v1.analize();

    std::cout << "V2 - initializer_list\n";
    Vector <pair> v2{ {true,"1"},{false,"2"},{true,"3"} };
    v2.analize();
    v2.resize(5);
    v2.analize();

    std::cout << "V3 - int array begin, end init\n";
    int array[5]{ 5,4,3,2,1 };
    int* ar_begin = { array };
    int* ar_end = { array + 5 };
    Vector <int> v3(ar_begin, ar_end);
    std::cout << "CHECK: Analize? \n";
    v3.analize();

    std::cout << "V4 - Vector <Pair> begin, end init\n";
    Vector <pair> v4(v2.begin(), v2.end());
    v4.analize();

    std::cout << "V5 - Vector init\n";
    Vector <pair> v5(v2);
    v5.analize();
    v5.resize(2);
    v5.analize();

    std::cout << "V6 - Vector move init\n";
    Vector <pair> v6(std::move(v5));
    v6.analize();
    std::cout << "CHECK: Analize moved Vector? \n";
    v5.analize();
}

void check_vector_memory() {
    std::cout << "Vector memory\n";
    Vector<pair> v11{ { true,"1" }, { false,"2" }, { true,"3" } };
    v11.analize();
    std::cout << "V11 resize\n";
    v11.resize(6);
    std::cout << "CHECK: v11 after resize\n";
    v11.analize();

    std::cout << "V11 reserve\n";
    v11.reserve(100);
    v11.analize();
    std::cout << "V11  new adress:\n" << &v11 << std::endl;

    Vector <int>* v_ptr = new (&v11)Vector<int>{10, 11, 12, 13, 14};
    std::cout << "v_ptr placement new v11 adress:\n" << v_ptr << std::endl;
    v_ptr->analize();
}

void check_vector_operators() {
    std::cout << "Vector operators\n";
    Vector<pair> v7;
    Vector<pair> v8{ { true,"1" }, { false,"2" }, { true,"3" } };
    std::cout << "Analize V8\n";
    v8.analize();
    std::cout << "V7 Operator '=' V8\n";
    v7 = v8;
    std::cout << "CHECK: V7 after operator '='\n";
    v7.analize();
    std::cout << "V9 Move operator '=' V7\n";
    Vector<pair> v9;
    v9 = std::move(v7);
    std::cout << "CHECK: V9 after move operator?\n";
    v9.analize();
    std::cout << "CHECK: Moved V7? \n";
    v7.analize();

    std::cout << "V9 operator []\n";
    std::cout << "Cout v9[0] and v9[1]\n";
    std::cout << v9[0].second << std::endl << v9[1].second << std::endl;
    std::cout << "V9[1] = 1\n";
    v9[1].second = "1";
    std::cout << "CHECK: v9[1]\n";
    std::cout << v9[1].second << std::endl;
    v9.analize();
}

void check_vector_functions() {
    std::cout << "Vector functions\n";
    Vector<pair> v10 { { true,"1" }, { false,"2" }, { true,"3" } };
    std::cout << "V10 Front and back\n";
    std::cout << "CHECK: Vector before front/back? \n";
    v10.analize();
    std::cout << "Front: " << (v10.front()).second << std::endl;
    std::cout << "Back: " << (v10.back()).second << std::endl;

    std::cout << "V10 push front/back\n";
    std::cout << "Push FRONT\n";
    v10.push_front({ false, "0.1" });
    std::cout << "CHECK: Vector after push front? \n";
    v10.analize();
    std::cout << "Push BACK\n";
    v10.push_back({ false, "0.4" });
    std::cout << "CHECK: Vector after push back? \n";
    v10.analize();

    std::cout << "V10 insert\n";
    v10.analize();
    v10.resize(6);
    v10.insert(0, { true, "8.5" });
    v10.insert(1, { false, "2.1" });
    v10.insert(3, { true, "4.4" });
    v10.insert(0, { false, "0.1" });
    std::cout << "CHECK: Vector after inserts? \n";
    v10.analize();

    std::cout << "V10 erase\n";
    v10.erase(1);
    std::cout << "CHECK: Vector after erase pos (1)? \n";
    v10.analize();
    v10.erase(v10.begin() + 1);
    std::cout << "CHECK: Vector after *erase + 1? \n";
    v10.analize();
    v10.erase(v10.begin() + 1, (v10.end() - 1));
    std::cout << "CHECK: Vector after (begin + 1)/(end - 1) erase? \n";
    v10.analize();

    std::cout << "V10 emplace back\n";
    v10.emplace_back(true, "1.65");
    v10.emplace_back(false, "3.42");
    v10.analize();
    std::cout << "V10 clear\n";
    v10.clear();
    v10.analize();
    std::cout << "V10 Push after clear\n";
    v10.push_back({ true, "5.6" });
    v10.push_back({ false, "11.4" });
    v10.analize();
}

void stack_adapter() {
    std::cout << "Stack-Adapter\n";
    Stack_ad<pair, Vector<pair>> st;
    std::cout << "Adapter capacity: " << st.GetCapacity() << std::endl;
    std::cout << "Adapter size: " << st.GetSize() << std::endl;
    std::cout << "Vector analize call thought Stack\n";
    st.analize();

    std::cout << "Steck PUSH\n";
    pair st_check_result = st.push({ false, "10" });
    std::cout << "Push result? " << st_check_result.second << std::endl;
    std::cout << "More pushes\n";
    st.push({ true, "16" });
    st.push({ false, "37" });
    st.push({ true, "29" });
    st.analize();

    {
        std::cout << "Popping all elements start\n";
        size_t tmp_size{ st.GetSize() };
        for (size_t i{};i != tmp_size;i++) {
            pair st_check_result = st.pop();
            std::cout << st_check_result.second << std::endl;
            if (st.GetSize() != 0) {
                std::cout << "Top element: " << st.top().first << st.top().second.second << std::endl;
            }
        }
        st.analize();

    }

    std::cout << "Stack emplace\n";
    st.emplace(true, "16");
    st.emplace(false, "38");
    std::cout << "Check emplace result: \n";
    st.analize();
}
