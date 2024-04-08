#include "Color.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

bool Color::operator==(const Color& other) const
{
    return std::fabs(r - other.r) < EPSILON &&
           std::fabs(g - other.g) < EPSILON &&
           std::fabs(b - other.b) < EPSILON;
}

Color Color::operator+(const Color& other) const
{
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator-(const Color& other) const
{
    return Color(r - other.r, g - other.g, b - other.b);
}

Color Color::operator*(const Color& other) const
{
    return Color(r * other.r, g * other.g, b * other.b);
}

Color Color::operator*(const float scalar) const
{
    return Color(r * scalar, g * scalar, b * scalar);
}

Color Color::operator/(const float scalar) const
{
    if (std::fabs(scalar) < EPSILON) throw std::invalid_argument("Attempted to divide by zero!");
    return Color(r / scalar, g / scalar, b / scalar);
}

void Color::print() const
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    stream << "{ " << r << ", " << g << ", " << b << " | " << "COLOR" << " }";
    std::cout << stream.str() << std::endl;
}
