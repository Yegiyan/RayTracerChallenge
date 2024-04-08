#include "Tuple.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

Tuple::Tuple() {}

Tuple::Tuple(float x, float y, float z, int w) : x(x), y(y), z(z), w(w)
{
    if (w != 0 && w != 1) throw std::invalid_argument("Attempted to create an invalid tuple type!");
}

Tuple Tuple::Vector(float x, float y, float z)
{
    return Tuple(x, y, z, 0);
}

Tuple Tuple::Point(float x, float y, float z)
{
    return Tuple(x, y, z, 1);
}

float Tuple::magnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Tuple Tuple::normalize()
{
    return Tuple::Vector(x / magnitude(), y / magnitude(), z / magnitude());
}

float Tuple::dot(const Tuple& a, const Tuple& b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Tuple Tuple::cross(const Tuple& a, const Tuple& b)
{
    return Tuple::Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

bool Tuple::operator==(const Tuple& other) const
{
    return std::fabs(x - other.x) < EPSILON &&
           std::fabs(y - other.y) < EPSILON &&
           std::fabs(z - other.z) < EPSILON &&
           w == other.w;
}

Tuple Tuple::operator+(const Tuple& other) const
{
    if (is_point() && other.is_point()) throw std::invalid_argument("Attempted to add two points!");
    return Tuple(x + other.x, y + other.y, z + other.z, w + other.w);
}

Tuple Tuple::operator-(const Tuple& other) const
{
    if (is_vector() && other.is_point()) throw std::invalid_argument("Attempted to subtract point from vector!");
    return Tuple(x - other.x, y - other.y, z - other.z, w - other.w);
}

Tuple Tuple::operator*(const float scalar) const
{
    return Tuple(x * scalar, y * scalar, z * scalar, w);
}

Tuple Tuple::operator/(const float scalar) const
{
    if (scalar == 0) throw std::invalid_argument("Attempted to divide by zero!");
    return Tuple(x / scalar, y / scalar, z / scalar, w);
}

Tuple Tuple::operator-() const
{
    return Tuple(-x, -y, -z, w);
}

bool Tuple::is_vector() const
{
    return w == 0;
}

bool Tuple::is_point() const
{
    return w == 1;
}

void Tuple::print() const
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2);
    stream << "{ " << x << ", " << y << ", " << z << " | " << (w == 0 ? "VECTOR" : w == 1 ? "POINT" : "UNDEFINED") << " }";
    std::cout << stream.str() << std::endl;
}