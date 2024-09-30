#include <iostream>

#include "Tuple.hpp"
#include "Color.hpp"
#include "Canvas.hpp"
#include "Matrix.hpp"

#include "Test.hpp"

int main()
{
    int input = 0;
    std::cout << "Choose Operation" << std::endl;
    std::cout << "1. Run Tests" << std::endl;
    std::cout << "2. Run Ray Tracer" << std::endl;
    std::cout << "> ";
    std::cin >> input;

    switch(input)
    {
        case 1:
            run_tests();
            break;
        case 2:
            //run_ray_tracer();
            std::cout << "Coming soon!" << std::endl;
            break;
        default:
            std::cout << "Invalid command!" << std::endl;
            break;
    }

    return 0;
}