#include "Tuple.hpp"
#include "Color.hpp"
#include "Canvas.hpp"
#include "Matrix.hpp"
#include "Test.hpp"

#include <iostream>

int main()
{
    Matrix matrix;
    matrix.matrix.push_back({ 3, 4, 1 });
    matrix.matrix.push_back({ 3, 4, 1 });
    matrix.matrix.push_back({ 3, 4, 1 });

    int input = 0;
    std::cout << "Choose operation" << std::endl;
    std::cout << "1. Run tests" << std::endl;
    std::cout << "2. Use interface" << std::endl;
    std::cout << "> ";
    std::cin >> input;

    switch(input)
    {
        case 1:
            run_tests();
            break;
        case 2:
            use_interface();
            break;
        default:
            std::cout << "Invalid command!" << std::endl;
            break;
    }
    return 0;
}