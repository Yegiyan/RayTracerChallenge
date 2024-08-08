#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

struct Tuple
{
    static constexpr float EPSILON = 0.00001f;
    float x, y, z;
    int w;

    Tuple();
    Tuple(float x, float y, float z, int w);

    static Tuple Vector(float x, float y, float z);
    static Tuple Point(float x, float y, float z);

    bool operator==(const Tuple& other) const;
    Tuple operator+(const Tuple& other) const;
    Tuple operator-(const Tuple& other) const;
    Tuple operator*(const float other) const;
    Tuple operator/(const float other) const;
    Tuple operator-() const;

    static float dot(const Tuple& a, const Tuple& b);
    static Tuple cross(const Tuple& a, const Tuple& b);

    float magnitude();
    Tuple normalize();
    bool is_point() const;
    bool is_vector() const;
    
    void print() const;
};