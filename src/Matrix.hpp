#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <initializer_list>

#include "Tuple.hpp"

struct Matrix
{
    static constexpr float EPSILON = 0.00001f;
    int rows, cols;
    std::vector<std::vector<float>> elements;

    Matrix();
    Matrix(int rows, int cols);
    Matrix(std::initializer_list<std::initializer_list<float>> values);

    int determinant() const;
    Matrix identity() const;
    Matrix transpose() const;
    Matrix submatrix(int row, int col) const;
    int minor(int row, int col) const;
    int cofactor(int row, int col) const;

    bool operator==(const Matrix &other) const;
    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Tuple operator*(const Tuple &tuple) const;
    Matrix operator*(float scalar) const;
    Matrix operator/(float scalar) const;
    Matrix operator-() const;

    float &at(int row, int col);
    const float &at(int row, int col) const;
    bool is_invertible() const;
    bool is_square() const;

    void print() const;
};