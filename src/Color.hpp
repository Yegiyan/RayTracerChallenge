#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

struct Color
{
    static constexpr float EPSILON = 0.00001f;
    float r, g, b;

    Color();
    Color(float r, float g, float b);

    bool operator==(const Color& other) const;
    Color operator+(const Color& other) const;
    Color operator-(const Color& other) const;
    Color operator*(const Color& other) const;
    Color operator*(const float scalar) const;
    Color operator/(const float scalar) const;

    void print() const;
};