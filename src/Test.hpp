#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

void assert_equal(bool condition, const std::string& message)
{
    if (!condition)
        std::cout << "\033[1;31mTest Failed:\033[0m " << message << std::endl;
    else
        std::cout << "\033[1;32mTest Passed:\033[0m " << message << std::endl;
}

std::vector<int> extract_pixel_data_from_ppm(const std::string& path)
{
    std::ifstream file(path);
    std::vector<int> pixelData;
    std::string line;
    int lineCount = 0;
    while (getline(file, line))
    {
        // skip ppm header info
        if (++lineCount <= 3) continue;

        // split line by spaces and convert to integers
        std::istringstream iss(line);
        int value;
        while (iss >> value)
            pixelData.push_back(value);
    }
    return pixelData;
}

bool compare_ppm_pixel_data(const std::string& path1, const std::string& path2)
{
    auto data1 = extract_pixel_data_from_ppm(path1);
    auto data2 = extract_pixel_data_from_ppm(path2);
    return data1 == data2;
}

void test_tuple_creation()
{
    Tuple point = Tuple::Point(4, -4, 3);
    assert_equal(point.is_point() && !point.is_vector(), "Point Creation");

    Tuple vector = Tuple::Vector(4, -4, 3);
    assert_equal(!vector.is_point() && vector.is_vector(), "Vector Creation");
}

void test_tuple_addition()
{
    Tuple a1 = Tuple::Point(3, -2, 5);
    Tuple a2 = Tuple::Vector(-2, 3, 1);
    Tuple sum = a1 + a2;
    assert_equal(sum == Tuple::Point(1, 1, 6), "Tuple Addition");
}

void test_tuple_subtraction()
{
    Tuple p1 = Tuple::Point(3, 2, 1);
    Tuple p2 = Tuple::Point(5, 6, 7);
    Tuple vector = p1 - p2;
    assert_equal(vector == Tuple::Vector(-2, -4, -6), "Point Subtraction (Outputs Vector)");

    Tuple point = p1 - vector;
    assert_equal(point == p2, "Vector Subtraction (Outputs Point)");
}

void test_normalization()
{
    Tuple v = Tuple::Vector(1, 2, 3);
    assert_equal(std::fabs(v.magnitude() - std::sqrt(14)) < v.EPSILON, "Vector Magnitude");

    Tuple norm = v.normalize();
    assert_equal(norm == Tuple::Vector(1/std::sqrt(14), 2/std::sqrt(14), 3/std::sqrt(14)), "Vector Normalization");
}

void test_dot_product()
{
    Tuple a = Tuple::Vector(1, 2, 3);
    Tuple b = Tuple::Vector(2, 3, 4);
    float dot = Tuple::dot(a, b);
    assert_equal(std::fabs(dot - 20) < a.EPSILON, "Dot Product");
}

void test_cross_product()
{
    Tuple a = Tuple::Vector(1, 2, 3);
    Tuple b = Tuple::Vector(2, 3, 4);
    Tuple cross = Tuple::cross(a, b);
    assert_equal(cross == Tuple::Vector(-1, 2, -1), "Cross Product");
}

void test_color_addition()
{
    Color c1 = { 0.9, 0.6, 0.75 };
    Color c2 = { 0.7, 0.1, 0.25 };
    Color c3 = c1 + c2;
    assert_equal(c3 == Color(1.6, 0.7, 1.0), "Color Addition");
}

void test_color_subtraction()
{
    Color c1 = { 0.9, 0.6, 0.75 };
    Color c2 = { 0.7, 0.1, 0.25 };
    Color c3 = c1 - c2;
    assert_equal(c3 == Color(0.2, 0.5, 0.5), "Color Subtraction");
}

void test_color_multiplication()
{
    Color c1 = { 1, 0.2, 0.4 };
    Color c2 = { 0.9, 1, 0.1 };
    Color c3 = c1 * c2;
    assert_equal(c3 == Color(0.9, 0.2, 0.04), "Color Multiplication");
}

void test_color_scalar()
{
    Color c1 = { 0.2, 0.3, 0.4 };
    Color c2 = c1 * 2;
    assert_equal(c2 == Color(0.4, 0.6, 0.8), "Color Scalar Multiplication");
}

void test_canvas_creation()
{
    Canvas c;
    c.width = 10;
    c.height = 20;
    assert_equal(c == Canvas(10, 20), "Canvas Creation");
}

void test_canvas_pixel_assignment()
{
    Canvas c = { 10, 20 };
    Color red = { 1, 0, 0 };
    c.write_pixel(2, 3, red);
    assert_equal(c.pixel_at(2, 3) == Color(1, 0, 0), "Canvas Pixel Assignment");
}

void test_canvas_to_ppm()
{
    Canvas c = { 5, 3 };
    Color c1 = { 1.5, 0, 0 };
    Color c2 = { 0, 0.5, 0 };
    Color c3 = { -0.5, 0, 1 };

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);
    c.canvas_to_ppm("../test/imagetest.ppm");

    bool data_is_equal = compare_ppm_pixel_data("../test/imagetest.ppm", "../test/test.ppm");
    assert_equal(data_is_equal, "Canvas to PPM Conversion");
}

void run_tests()
{
    test_tuple_creation();
    test_tuple_addition();
    test_tuple_subtraction();
    test_normalization();
    test_dot_product();
    test_cross_product();
    test_color_addition();
    test_color_subtraction();
    test_color_multiplication();
    test_color_scalar();
    test_canvas_creation();
    test_canvas_pixel_assignment();
    test_canvas_to_ppm();
}

void use_interface()
{
    int input0 = 0, input1 = 0, input2 = 0;
    float x1 = 0, y1 = 0, z1 = 0;
    float x2 = 0, y2 = 0, z2 = 0;
    float mag = 0, scale = 0, dot = 0;
    Tuple a, b, c;

    std::cout << "Create 1 or 2 tuples?" << std::endl;
    std::cout << "1. Create one" << std::endl;
    std::cout << "2. Create two" << std::endl;
    std::cout << "> ";
    std::cin >> input0;

    if (input0 == 1)
    {
        std::cout << "Choose tuple type" << std::endl;
        std::cout << "1. Point" << std::endl;
        std::cout << "2. Vector" << std::endl;
        std::cout << "> ";
        std::cin >> input0;

        if (input0 == 1)
        {
            std::cout << "Create point (X, Y, Z)" << std::endl;
            std::cout << "X: ";
            std::cin >> x1;
            std::cout << "Y: ";
            std::cin >> y1;
            std::cout << "Z: ";
            std::cin >> z1;
            a = Tuple::Point(x1, y1, z1);

            std::cout << "Choose operation" << std::endl;
            std::cout << "1. Negate" << std::endl;
            std::cout << "> ";
            std::cin >> input0;

            if (input0 == 1)
            {
                a = -a;
                a.print();
            }
        }

        if (input0 == 2)
        {
            std::cout << "Create vector (X, Y, Z)" << std::endl;
            std::cout << "X: ";
            std::cin >> x1;
            std::cout << "Y: ";
            std::cin >> y1;
            std::cout << "Z: ";
            std::cin >> z1;
            a = Tuple::Vector(x1, y1, z1);

            std::cout << "Choose operation" << std::endl;
            std::cout << "1. Magnitude" << std::endl;
            std::cout << "2. Normalize" << std::endl;
            std::cout << "3. Negate" << std::endl;
            std::cout << "4. Scale" << std::endl;
            std::cout << "> ";
            std::cin >> input0;

            switch (input0)
            {
                case 1:
                    mag = a.magnitude();
                    std::cout << "Magnitude: " << mag << std::endl;
                    break;
                case 2:
                    a = a.normalize();
                    a.print();
                    break;
                case 3:
                    a = -a;
                    a.print();
                    break;
                case 4:
                    std::cout << "Input scale value" << std::endl;
                    std::cout << "> ";
                    std::cin >> scale;
                    a = a * scale;
                    a.print();
                    break;
                default:
                    std::cout << "Invalid command!" << std::endl;
                    break;
            }
        }
    }

    else if (input0 == 2)
    {
        std::cout << "Choose 1st tuple type" << std::endl;
        std::cout << "1. Point" << std::endl;
        std::cout << "2. Vector" << std::endl;
        std::cout << "> ";
        std::cin >> input1;

        std::cout << "Choose 2nd tuple type" << std::endl;
        std::cout << "1. Point" << std::endl;
        std::cout << "2. Vector" << std::endl;
        std::cout << "> ";
        std::cin >> input2;

        if (input1 == 1)
        {
            std::cout << "Create first tuple (point) (X, Y, Z)" << std::endl;
            std::cout << "X: ";
            std::cin >> x1;
            std::cout << "Y: ";
            std::cin >> y1;
            std::cout << "Z: ";
            std::cin >> z1;
            a = Tuple::Point(x1, y1, z1);
        }

        else if (input1 == 2)
        {
            std::cout << "Create first tuple (vector) (X, Y, Z)" << std::endl;
            std::cout << "X: ";
            std::cin >> x1;
            std::cout << "Y: ";
            std::cin >> y1;
            std::cout << "Z: ";
            std::cin >> z1;
            a = Tuple::Vector(x1, y1, z1);
        }

        if (input2 == 1)
        {
            std::cout << "Create second tuple (point) (X, Y, Z)" << std::endl;
            std::cout << "X: ";
            std::cin >> x2;
            std::cout << "Y: ";
            std::cin >> y2;
            std::cout << "Z: ";
            std::cin >> z2;
            b = Tuple::Point(x2, y2, z2);
        }

        else if (input2 == 2)
        {
            std::cout << "Create second tuple (vector) (X, Y, Z)" << std::endl;
            std::cout << "X: ";
            std::cin >> x2;
            std::cout << "Y: ";
            std::cin >> y2;
            std::cout << "Z: ";
            std::cin >> z2;
            b = Tuple::Vector(x2, y2, z2);
        }

        if (a.is_vector() && b.is_vector())
        {
            std::cout << "Choose operation" << std::endl;
            std::cout << "1. Add vectors" << std::endl;
            std::cout << "2. Subtract vectors" << std::endl;
            std::cout << "3. Dot product" << std::endl;
            std::cout << "4. Cross product" << std::endl;
            std::cout << "> ";
            std::cin >> input0;

            switch (input0)
            {
                case 1:
                    c = a + b;
                    c.print();
                    break;
                case 2:
                    std::cout << "Choose operation" << std::endl;
                    std::cout << "1. Vec1 - Vec2" << std::endl;
                    std::cout << "2. Vec2 - Vec1" << std::endl;
                    std::cout << "> ";
                    std::cin >> input0;
                    if (input0 == 1)
                        c = a - b;
                    else if (input0 == 2)
                        c = b - a;
                    break;
                case 3:
                    dot = Tuple::dot(a, b);
                    std::cout << "Dot Product: " << dot << std::endl;
                    break;
                case 4:
                    std::cout << "Choose operation" << std::endl;
                    std::cout << "1. Vec1 x Vec2" << std::endl;
                    std::cout << "2. Vec2 x Vec1" << std::endl;
                    std::cout << "> ";
                    std::cin >> input0;
                    if (input0 == 1)
                        c = Tuple::cross(a, b);
                    else if (input0 == 2)
                        c = Tuple::cross(b, a);
                    c.print();
                    break;
                default:
                    std::cout << "Invalid command!" << std::endl;
                    break;
            }
        }

        else if (a.is_point() && b.is_point())
        {
            std::cout << "Choose operation" << std::endl;
            std::cout << "1. Get vector from one point to another" << std::endl;
            std::cout << "> ";
            std::cin >> input0;

            switch (input0)
            {
                case 1:
                    std::cout << "Choose operation" << std::endl;
                    std::cout << "1. Point1 -> Point2" << std::endl;
                    std::cout << "2. Point2 -> Point1" << std::endl;
                    std::cout << "> ";
                    std::cin >> input0;
                    if (input0 == 1)
                        c = a - b;
                    else if (input0 == 2)
                        c = b - a;
                    c.print();
                    break;
                default:
                    std::cout << "Invalid command!" << std::endl;
                    break;
            }
        }

        else if ((a.is_point() && b.is_vector()) || (a.is_vector() && b.is_point()))
        {
            std::cout << "Choose operation" << std::endl;
            std::cout << "1. Add vector from point" << std::endl;
            std::cout << "2. Subtract vector from point" << std::endl;
            std::cout << "> ";
            std::cin >> input0;

            switch (input0)
            {
                case 1:
                    c = a + b;
                    c.print();
                    break;
                case 2:
                    if (a.is_point())
                        c = a - b;
                    else if (b.is_point())
                        c = b - a;
                    c.print();
                    break;
                default:
                    std::cout << "Invalid command!" << std::endl;
                    break;
            }
        }
    }
}