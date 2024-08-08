#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

#include "Color.hpp"

struct Canvas
{
    int width, height;
    std::vector<std::vector<Color>> pixels;

    Canvas();
    Canvas(int width, int height);

    bool operator==(const Canvas& other) const;

    void write_pixel(int x, int y, Color color);
    Color pixel_at(int x, int y) const;
    void canvas_to_ppm(std::string fileName);
};
