#include "Test_Functions_List.h"

enum TESTER {
    CHECK_VECTOR_CONSTRUCTORS = 1,
    CHECK_VECTOR_MEMORY,
    CHECK_VECTOR_OPERATORS,
    CHECK_VECTOR_FUNCTIONS,
    STACK_ADAPTER,
    ALL_FUNCTIONS,
    END_GUIDE
};

void tester() {
    std::cout << "What function need to be called?\n"
        "1 - check_vector_constructors\n"
        "2 - check_vector_memory\n"
        "3 - check_vector_operators\n"
        "4 - check_vector_functions\n"
        "5 - stack-adapter\n"
        "6 - all functions\n"
        "7 - end guide\n";
    short select_test_function{};
    std::cin >> select_test_function;
    if (select_test_function >= 1 && select_test_function <= 7) {
        switch (select_test_function) {
        case TESTER::CHECK_VECTOR_CONSTRUCTORS:
            std::cout << "You selected check_vector_constructors\n";
            check_vector_constructors();
            break;
        case TESTER::CHECK_VECTOR_MEMORY:
            std::cout << "You selected check_vector_memory\n";
            check_vector_memory();
            break;
        case TESTER::CHECK_VECTOR_OPERATORS:
            std::cout << "You selected check_vector_operators\n";
            check_vector_operators();
            break;
        case TESTER::CHECK_VECTOR_FUNCTIONS:
            std::cout << "You selected check_vector_functions\n";
            check_vector_functions();
            break;
        case TESTER::STACK_ADAPTER:
            std::cout << "You selected stack_adapter\n";
            check_stack_adapter();
            break;
        case TESTER::ALL_FUNCTIONS:
            std::cout << "You selected all functions\n";
            check_vector_constructors();
            check_vector_memory();
            check_vector_operators();
            check_vector_functions();
            check_stack_adapter();
            break;
        case TESTER::END_GUIDE:
            std::cout << "You selected end guide\n";
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
