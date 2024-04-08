#pragma once

#include "Color.hpp"
#include <vector>
#include <string>

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
