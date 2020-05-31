#include "Functions_List.h"

enum GUIDE {
    CHECK_VECTOR_CONSTRUCTORS = 1,
    CHECK_VECTOR_MEMORY,
    CHECK_VECTOR_OPERATORS,
    CHECK_VECTOR_FUNCTIONS,
    STACK_ADAPTER,
    END_GUIDE,
};

void guide() {
    std::cout << "What function need to be called?\n"
        "1 - check_vector_constructors\n"
        "2 - check_vector_memory\n"
        "3 - check_vector_operators\n"
        "4 - check_vector_functions\n"
        "5 - stack-adapter\n"
        "6 - end guide\n";
    short select_function{};
    std::cin >> select_function;
    if (select_function >= 1 && select_function <= 6) {
        switch (select_function) {
        case(GUIDE::CHECK_VECTOR_CONSTRUCTORS):
            std::cout << "You selected check_vector_constructors\n";
            check_vector_constructors();
            break;
        case(GUIDE::CHECK_VECTOR_MEMORY):
            std::cout << "You selected check_vector_memory\n";
            check_vector_memory();
            break;
        case(GUIDE::CHECK_VECTOR_OPERATORS):
            std::cout << "You selected check_vector_operators\n";
            check_vector_operators();
            break;
        case(GUIDE::CHECK_VECTOR_FUNCTIONS):
            std::cout << "You selected check_vector_functions\n";
            check_vector_functions();
            break;
        case(GUIDE::STACK_ADAPTER):
            std::cout << "You selected stack_adapter\n";
            stack_adapter();
            break;
        case(GUIDE::END_GUIDE):
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
