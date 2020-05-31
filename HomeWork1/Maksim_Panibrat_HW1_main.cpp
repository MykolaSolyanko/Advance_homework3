#include "Functions_List.h"

int main(int argc, char const* argv[])
{
    std::cout << "This program realizes vector\n";
    std::cout << std::boolalpha;

    for (char select{ 'y' }; select == 'y'; std::cin >> select) {
        try {
            guide();
        }
        catch (const std::bad_alloc & e) {
            std::cout << "Bad Alloc Error\n" << e.what() << std::endl;
        }
        catch (const std::logic_error& e) {
            std::cout << "Logic Error\n" << e.what() << std::endl;
        }
        catch (const std::runtime_error& e) {
            std::cout << "Runtime Error\n" << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Error, undefined exception catched\n";
        }
        std::cout << "Recall guide y/n ?\n";
    }

    std::cout << "End of program\n";
    return 0;
}


