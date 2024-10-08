#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

const double PI = 3.141592653589793238463;

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

void test_matrix_multiplication()
{
    Matrix m1 = {{1, 2, 3, 4},
                 {5, 6, 7, 8},
                 {9, 8, 7, 6},
                 {5, 4, 3, 2}};

    Matrix m2 = {{-2, 1, 2, 3},
                 {3, 2, 1, -1},
                 {4, 3, 6, 5},
                 {1, 2, 7, 8}};

    int val = 2;
    Matrix m3 = {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}};

    Matrix key1 = {{2, 4, 6},
                   {8, 10, 12},
                   {14, 16, 18}};

    Matrix key2 = {{20, 22, 50, 48},
                   {44, 54, 114, 108},
                   {40, 58, 110, 102},
                   {16, 26, 46, 42}};

    Matrix m4 = m3 * val;
    Matrix m5 = m1 * m2;
    assert_equal((m4 == key1) && (m5 == key2), "Matrix Multiplication");
}

void test_matrix_multiplication_scalar()
{
    int val = 2;
    Matrix m = {{1, 2, 3},
                {4, 5, 6},
                {7, 8, 9}};

    Matrix ans = m * val;
    Matrix key = {{2, 4, 6},
                  {8, 10, 12},
                  {14, 16, 18}};

    assert_equal((ans == key), "Matrix & Scalar Multiplication");
}

void test_matrix_multiplication_tuple()
{
    Tuple t = Tuple::Point(1, 2, 3);
    Matrix m = {{1, 2, 3, 4},
                {2, 4, 4, 2},
                {8, 6, 4, 1},
                {0, 0, 0, 1}};

    Tuple ans = m * t;
    Tuple key = Tuple::Point(18, 24, 33);
    assert_equal(ans == key, "Matrix & Tuple Multiplication");
}

void test_matrix_identity()
{
    Matrix m = {{0, 1, 2, 4},
                {1, 2, 4, 8},
                {2, 4, 8, 16},
                {4, 8, 16, 32}};

    Matrix ans = m * m.identity();
    Matrix key = m;
    assert_equal(ans == key, "Matrix Identity Multiplication");
}

void test_matrix_transpose()
{
    Matrix m = {{0, 9, 3, 0},
                {9, 8, 0, 8},
                {1, 8, 5, 3},
                {0, 0, 5, 8}};

    Matrix key = {{0, 9, 1, 0},
                  {9, 8, 8, 0},
                  {3, 0, 5, 5},
                  {0, 8, 3, 8}};

    Matrix ans = m.transpose();
    assert_equal((ans == key) && (m.identity().transpose() == m.identity()), "Matrix Transposing");
}

void test_matrix_submatrix()
{
    Matrix m = {{-6, 1, 1, 6},
                {-8, 5, 8, 6},
                {-1, 0, 8, 2},
                {-7, 1, -1, 1}};

    Matrix key = {{-6, 1, 6},
                  {-8, 8, 6},
                  {-7, -1, 1}};

    Matrix ans = m.submatrix(2, 1);
    assert_equal(ans == key, "Matrix to Sub Matrix");
}

void test_matrix_minor()
{
    Matrix m = {{3, 5, 0},
                {2, -1, -7},
                {6, -1, 5}};

    int key = 25;
    int ans = m.minor(1, 0);
    assert_equal(ans == key, "Matrix Minor");
}

void test_matrix_cofactor()
{
    Matrix m = {{3, 5, 0},
                {2, -1, -7},
                {6, -1, 5}};

    int key1 = -12;
    int ans1 = m.cofactor(0, 0);
    int key2 = -25;
    int ans2 = m.cofactor(1, 0);
    assert_equal((ans1 == key1) && (ans2 == key2), "Matrix Cofactor");
}

void test_matrix_determinant_2x2()
{
    Matrix m = {{1, 5},
                {-3, 2}};

    int key = 17;
    int ans = m.determinant();
    assert_equal(ans == key, "Matrix Determinant 2x2");
}

void test_matrix_determinant_3x3()
{
    Matrix m = {{1, 2, 6},
                {-5, 8, -4},
                {2, 6, 4}};

    int key1 = 56, key2 = 12, key3 = -46, key4 = -196;

    int ans1 = m.cofactor(0, 0);
    int ans2 = m.cofactor(0, 1);
    int ans3 = m.cofactor(0, 2);
    int ans4 = m.determinant();
    assert_equal((ans1 == key1) && (ans2 == key2) && (ans3 == key3) && (ans4 == key4), "Matrix Determinant 3x3");
}

void test_matrix_determinant_4x4()
{
    Matrix m = {{-2, -8, 3, 5},
                {-3, 1, 7, 3},
                {1, 2, -9, 6},
                {-6, 7, 7, -9}};

    int key1 = 690, key2 = 447, key3 = 210, key4 = 51, key5 = -4071;
    int ans1 = m.cofactor(0, 0);
    int ans2 = m.cofactor(0, 1);
    int ans3 = m.cofactor(0, 2);
    int ans4 = m.cofactor(0, 3);
    int ans5 = m.determinant();
    assert_equal((ans1 == key1) && (ans2 == key2) && (ans3 == key3) && (ans4 == key4) && (ans5 == key5), "Matrix Determinant 4x4");
}

void test_matrix_invertibility()
{
    Matrix m1 = {{6, 4, 4, 4},
                {5, 5, 7, 6},
                {4, -9, 3, -7},
                {9, 1, 7, -6}};

    Matrix m2 = {{-4, 2, -2, 3},
                 {9, 6, 2, 6},
                 {0, -5, 1, -5},
                 {0, 0, 0, 0}};

    bool key1 = true, key2 = false;
    assert_equal((m1.is_invertible() == key1 && m2.is_invertible() == key2), "Matrix Invertibility");
}

void test_matrix_inverse()
{
    Matrix m1 = {{-5, 2, 6, -8},
                 {1, -5, 1, 8},
                 {7, 7, -6, -7},
                 {1, -3, 7, 4}};

    Matrix m2 = {{8, -5, 9, 2},
                 {7, 5, 6, 1},
                 {-6, 0, 9, 6},
                 {-3, 0, -9, -4}};

    Matrix m3 = {{9, 3, 0 ,9},
                 {-5, -2, -6, -3},
                 {-4, 9, 6, 4},
                 {-7, 6, 6, 2}};

    Matrix key1 = {{0.21805f, 0.45113f, 0.24060f, -0.04511f},
                   {-0.808279f, -1.45677f, -0.44361f, 0.52068f},
                   {-0.07895f, -0.22368f, -0.05263f, 0.19737f},
                   {-0.52256f, -0.81391f, -0.30075f, 0.30639f}};

    Matrix key2 = { {-0.15385, -0.15385, -0.28205, -0.53846},
                    {-0.07692, 0.12308, 0.02564, 0.03077},
                    {0.35897, 0.35897, 0.43590, 0.92308},
                    {-0.69231, -0.69231, -0.76923, -1.92308}};

    Matrix key3 = {{-0.04074, -0.07778, 0.14444, -0.22222},
                   {-0.07778, 0.03333, 0.36667, -0.33333},
                   {-0.02901, -0.14630, -0.10926, 0.12963},
                   {0.17778, 0.06667, -0.26667, 0.33333}};

    Matrix m4 = m1 * m2;
    Matrix key4 = m4 * m2.inverse();
    assert_equal((m1.inverse() == key1) && (m2.inverse() == key2) && (m3.inverse() == key3) && (m1 == key4), "Matrix Inversing");
}

void test_matrix_translation()
{
    Matrix transform(4, 4);
    transform = transform.identity();
    transform = transform.translate(5, -3, 2);

    Tuple point = Tuple::Point(-3, 4, 5);
    Tuple vector = Tuple::Vector(-3, 4, 5);

    Tuple ans1 = transform * point;
    Tuple key1 = Tuple::Point(2, 1, 7);

    Tuple ans2 = transform.inverse() * point;
    Tuple key2 = Tuple::Point(-8, 7, 3);

    Tuple ans3 = transform * vector;
    Tuple key3 = vector;

    assert_equal((ans1 == key1) && (ans2 == key2) && (ans3 == key3), "Matrix Translation");
}

void test_matrix_scaling()
{
    Matrix transform(4, 4);
    transform = transform.identity();
    transform = transform.scale(2, 3, 4);

    Tuple point = Tuple::Point(-4, 6, 8);
    Tuple vector = Tuple::Vector(-4, 6, 8);

    Tuple ans1 = transform * point;
    Tuple key1 = Tuple::Point(-8, 18, 32);

    Tuple ans2 = transform * vector;
    Tuple key2 = Tuple::Vector(-8, 18, 32);

    Tuple ans3 = transform.inverse() * vector;
    Tuple key3 = Tuple::Vector(-2, 2, 2);

    assert_equal((ans1 == key1) && (ans2 == key2) && (ans3 == key3), "Matrix Scaling");
}

void test_matrix_reflection()
{
    Matrix transform(4, 4);
    transform = transform.identity();
    transform = transform.scale(-1, 1, 1);

    Tuple point = Tuple::Point(2, 3, 4);

    Tuple ans = transform * point;
    Tuple key = Tuple::Point(-2, 3, 4);

    assert_equal(ans == key, "Matrix Reflection");
}

void test_tuple_rotation_x()
{
    Tuple point = Tuple::Point(0, 1, 0);
    Tuple half_quarter = point.rotate_x(PI / 4);
    Tuple full_quarter = point.rotate_x(PI / 2);

    Tuple ans1 = half_quarter;
    Tuple key1 = Tuple::Point(0, sqrt(2) / 2, sqrt(2) / 2);

    Tuple ans2 = full_quarter;
    Tuple key2 = Tuple::Point(0, 0, 1);

    assert_equal((ans1 == key1) && (ans2 == key2), "Tuple Rotation X");
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
    test_matrix_multiplication();
    test_matrix_multiplication_scalar();
    test_matrix_multiplication_tuple();
    test_matrix_identity();
    test_matrix_transpose();
    test_matrix_submatrix();
    test_matrix_minor();
    test_matrix_cofactor();
    test_matrix_determinant_2x2();
    test_matrix_determinant_3x3();
    test_matrix_determinant_4x4();
    test_matrix_invertibility();
    test_matrix_inverse();
    test_matrix_translation();
    test_matrix_scaling();
    test_matrix_reflection();
    test_tuple_rotation_x();
}