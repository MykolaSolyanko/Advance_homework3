#include "Vector.hpp"
#include "Stack.hpp"
#include "test_functions.h"
#include <utility>
#include <type_traits>

using test_pair = std::pair<bool, const char*>;

template <typename T>
void analize_vector(Vector<T>& vec) noexcept {
    std::cout << "CHECK: Empty? " << vec.empty() << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
    std::cout << "Size: " << vec.size() << std::endl;
    size_t vector_size = vec.size();
    if (vector_size != 0) {
        std::cout << "Print vector: \n";
        if constexpr (std::is_same<std::pair<bool, const char*>, T>::value) {
            const T* vec_begin = vec.begin();
            for (int i{}; i != vector_size;i++, vec_begin++) {
                std::cout << (*vec_begin).first << (*vec_begin).second << std::endl;
            }
            return;
        }
        else if constexpr (std::is_arithmetic<T>::value) {
            const T* vec_begin = vec.begin();
            for (int i{}; i != vector_size;i++, vec_begin++) {
                std::cout << *vec_begin << std::endl;
            }
            return;
        }
        else {
            std::cout << "Cant print\n";
        }
    }
}

void check_vector_constructors() {
    std::cout << "Vector constructors\n";
    std::cout << "V01 - size init\n";
    Vector<int> v01(5);
    analize_vector<int>(v01);

    std::cout << "V1 - fill size init\n";
    Vector <test_pair> v1{ 3 , {true,"1"} };
    analize_vector<test_pair>(v1);

    std::cout << "V2 - initializer_list\n";
    Vector <test_pair> v2{ {true,"1"},{false,"2"},{true,"3"} };
    analize_vector<test_pair>(v2);
    v2.resize(5, { true, "1" });
    analize_vector<test_pair>(v2);

    std::cout << "V3 - int array begin, end init\n";
    int array[5]{ 5,4,3,2,1 };
    int* ar_begin = { array };
    int* ar_end = { array + 5 };
    Vector <int> v3(ar_begin, ar_end);
    std::cout << "CHECK: Analize? \n";
    analize_vector<int>(v3);

    std::cout << "V4 - Vector <Pair> begin, end init\n";
    Vector <test_pair> v4(v2.begin(), v2.end());
    analize_vector<test_pair>(v4);

    std::cout << "V5 - Vector init\n";
    Vector <test_pair> v5(v2);
    analize_vector<test_pair>(v5);

    std::cout << "V6 - Vector move init\n";
    Vector <test_pair> v6(std::move(v5));
    analize_vector<test_pair>(v6);
    std::cout << "CHECK: Analize moved Vector? \n";
    analize_vector<test_pair>(v5);
}

void check_vector_memory() {
    std::cout << "Vector memory\n";
    Vector<test_pair> v11{ { true,"1" }, { false,"2" }, { true,"3" } };
    analize_vector<test_pair>(v11);
    std::cout << "V11 fill resize\n";
    v11.resize(5, { true, "1" });
    std::cout << "CHECK: v11 after resize\n";
    analize_vector<test_pair>(v11);

    Vector<int> v20{};
    v20.resize(3);
    analize_vector<int>(v20);

    std::cout << "V11 reserve\n";
    v11.reserve(100);
    analize_vector<test_pair>(v11);
    std::cout << "V11 adress:\n" << &v11 << std::endl;

    Vector <int>* v_ptr = new (&v11)Vector<int>{10, 11, 12, 13, 14};
    std::cout << "v_ptr placement new v11 adress:\n" << v_ptr << std::endl;
    analize_vector<int>(*v_ptr);
    v_ptr->resize(7);
    analize_vector<int>(*v_ptr);
}

void check_vector_operators() {
    std::cout << "Vector operators\n";
    Vector<test_pair> v7;
    Vector<test_pair> v8{ { true,"1" }, { false,"2" }, { true,"3" } };
    std::cout << "Analize V8\n";
    analize_vector<test_pair>(v8);
    std::cout << "V7 Operator '=' V8\n";
    v7 = v8;
    std::cout << "CHECK: V7 after operator '='\n";
    analize_vector<test_pair>(v7);
    std::cout << "V9 Move operator '=' V7\n";
    Vector<test_pair> v9;
    v9 = std::move(v7);
    std::cout << "CHECK: V9 after move operator?\n";
    analize_vector<test_pair>(v9);
    std::cout << "CHECK: Moved V7? \n";
    analize_vector<test_pair>(v7);

    std::cout << "V9 operator []\n";
    std::cout << "Cout v9[0] and v9[1]\n";
    std::cout << v9[0].second << std::endl << v9[1].second << std::endl;
    std::cout << "V9[1] = 1\n";
    v9[1].second = "1";
    std::cout << "CHECK: v9[1]\n";
    std::cout << v9[1].second << std::endl;
    analize_vector<test_pair>(v9);
}

void check_vector_functions() {
    std::cout << "Vector functions\n";
    Vector<test_pair> v10{ { true,"1" }, { false,"2" }, { true,"3" } };
    std::cout << "V10 Front and back\n";
    std::cout << "CHECK: Vector before front/back? \n";
    analize_vector<test_pair>(v10);
    std::cout << "Front: " << (v10.front()).second << std::endl;
    std::cout << "Back: " << (v10.back()).second << std::endl;

    std::cout << "V10 push front/back\n";
    std::cout << "Push FRONT\n";
    v10.push_front({ false, "0.1" });
    std::cout << "CHECK: Vector after push front? \n";
    analize_vector<test_pair>(v10);
    std::cout << "Push BACK\n";
    v10.push_back({ false, "0.4" });
    std::cout << "CHECK: Vector after push back? \n";
    analize_vector<test_pair>(v10);

    std::cout << "V10 insert\n";
    analize_vector<test_pair>(v10);
    v10.resize(6, { true, "1" });
    v10.insert(1, { true, "8.5" });
    v10.insert(2, { false, "2.1" });
    v10.insert(3, { true, "4.4" });
    v10.insert(1, { false, "0.1" });
    std::cout << "CHECK: Vector after inserts? \n";
    analize_vector<test_pair>(v10);

    std::cout << "Vector 10_1\n";
    Vector<int>v10_1{ 1,2,3,4,5 };
    analize_vector<int>(v10_1);
    v10_1.erase(3);
    analize_vector<int>(v10_1);

    std::cout << "V10 erase\n";
    v10.erase(1);
    std::cout << "CHECK: Vector after erase pos (1)? \n";
    analize_vector<test_pair>(v10);
    v10.erase(v10.begin() + 1);
    std::cout << "CHECK: Vector after *erase + 1? \n";
    analize_vector<test_pair>(v10);
    v10.erase(v10.begin() + 1, (v10.end() - 1));
    std::cout << "CHECK: Vector after (begin + 1)/(end - 1) erase? \n";
    analize_vector<test_pair>(v10);

    std::cout << "V10 emplace back\n";
    v10.emplace_back(true, "1.65");
    v10.emplace_back(false, "3.42");
    analize_vector<test_pair>(v10);
    std::cout << "V10 clear\n";
    v10.clear();
    analize_vector<test_pair>(v10);
    std::cout << "V10 Push after clear\n";
    v10.push_back({ true, "5.6" });
    v10.push_back({ false, "11.4" });
    analize_vector<test_pair>(v10);

    Vector<int>v11{ 1,2,3,4,5 };
    analize_vector<int>(v11);
    v11.insert(3, 11);
    analize_vector<int>(v11);
    v11.erase(v11.begin(), v11.end() - 2);
    analize_vector<int>(v11);
}

template <typename Value_Type, typename Container>
void stack_analize_vector(Stack_adapter <Value_Type, Container>& st) {
    std::cout << "CHECK: Empty? " << st.empty() << std::endl;
    std::cout << "Capacity: " << st.GetCapacity() << std::endl;
    std::cout << "Size: " << st.GetSize() << std::endl;
}

void check_stack_adapter() {
    std::cout << "Stack-Adapter\n";
    Stack_adapter<test_pair, Vector<test_pair>> st;
    std::cout << "Adapter capacity: " << st.GetCapacity() << std::endl;
    std::cout << "Adapter size: " << st.GetSize() << std::endl;
    std::cout << "Vector analize call thought Stack\n";
    stack_analize_vector<test_pair, Vector<test_pair>>(st);

    std::cout << "Steck PUSH\n";
    test_pair st_check_result = st.push({ false, "10" });
    std::cout << "Push result? " << st_check_result.second << std::endl;
    std::cout << "More pushes\n";
    st.push({ true, "16" });
    std::cout << "Pushed element: " << st.top().first << st.top().second.second << std::endl;
    st.push({ false, "37" });
    std::cout << "Pushed element: " << st.top().first << st.top().second.second << std::endl;
    st.push({ true, "29" });
    std::cout << "Pushed element: " << st.top().first << st.top().second.second << std::endl;
    stack_analize_vector<test_pair, Vector<test_pair>>(st);

    {
        std::cout << "Popping all elements start\n";
        size_t tmp_size{ st.GetSize() };
        for (size_t i{};i != tmp_size;i++) {
            test_pair st_check_result = st.pop();
            std::cout << st_check_result.second << std::endl;
            if (st.GetSize() != 0) {
                std::cout << "Top element: " << st.top().first << st.top().second.second << std::endl;
            }
        }
        stack_analize_vector<test_pair, Vector<test_pair>>(st);

    }

    std::cout << "Stack emplace\n";
    st.emplace(true, "16");
    std::cout << "Emplaced element: " << st.top().first << st.top().second.second << std::endl;
    st.emplace(false, "38");
    std::cout << "Emplaced element: " << st.top().first << st.top().second.second << std::endl;
    std::cout << "Check emplace result: \n";
    stack_analize_vector<test_pair, Vector<test_pair>>(st);
}

enum TestFunctions {
    kCheckVectorConstructors = 1,
    kCheckVectorMemory,
    kCheckVectorOperators,
    kCheckVectorFunctions,
    kStackAdapter,
    kAllFunctions,
    kEndTest
};

void test_functions_caller() {
    std::cout << "What function need to be called?\n"
        "1 - check vector constructors\n"
        "2 - check vector memory\n"
        "3 - check vector operators\n"
        "4 - check vector functions\n"
        "5 - stack-adapter\n"
        "6 - all functions\n"
        "7 - end test\n";
    short select_test_function{};
    std::cin >> select_test_function;
    if (select_test_function >= 1 && select_test_function <= 7) {
        switch (select_test_function) {
        case TestFunctions::kCheckVectorConstructors:
            std::cout << "You selected check vector constructors\n";
            check_vector_constructors();
            break;
        case TestFunctions::kCheckVectorMemory:
            std::cout << "You selected check vector memory\n";
            check_vector_memory();
            break;
        case TestFunctions::kCheckVectorOperators:
            std::cout << "You selected check vector operators\n";
            check_vector_operators();
            break;
        case TestFunctions::kCheckVectorFunctions:
            std::cout << "You selected check vector functions\n";
            check_vector_functions();
            break;
        case TestFunctions::kStackAdapter:
            std::cout << "You selected stack adapter\n";
            check_stack_adapter();
            break;
        case TestFunctions::kAllFunctions:
            std::cout << "You selected all functions\n";
            check_vector_constructors();
            check_vector_memory();
            check_vector_operators();
            check_vector_functions();
            check_stack_adapter();
            break;
        case TestFunctions::kEndTest:
            std::cout << "You selected end test\n";
            break;
        default:
            std::cout << "Error, undefined selection breaking\n";
            break;
        }
    }
    else {
        std::cout << "Error, out of range or not number\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}