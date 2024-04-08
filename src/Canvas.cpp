#include "Canvas.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

Canvas::Canvas() {}

Canvas::Canvas(int width, int height) : width(width), height(height)
{
    pixels.resize(width, std::vector<Color>(height));
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            pixels[x][y] = Color(0, 0, 0);
}

bool Canvas::operator==(const Canvas& other) const
{
    return width == other.width && height == other.height;
}

void Canvas::write_pixel(int x, int y, Color color)
{
    if(x >= 0 && x < width && y >= 0 && y < height)
        pixels[x][y] = color;
}

Color Canvas::pixel_at(int x, int y) const
{
    if(x >= 0 && x < width && y >= 0 && y < height)
        return pixels[x][y];
    return Color();
}

void Canvas::canvas_to_ppm(std::string fileName)
{
    std::ofstream file(fileName);
    file << "P3" << std::endl;
    file << width << " " << height << std::endl;
    file << "255" << std::endl;

    for (int y = 0; y < height; y++)
    {
        int lineLength = 0;
        for (int x = 0; x < width; x++)
        {
            Color color = pixel_at(x, y);
            std::string pixelData = std::to_string(std::clamp(static_cast<int>(std::round(color.r * 255)), 0, 255)) + " " +
                                    std::to_string(std::clamp(static_cast<int>(std::round(color.g * 255)), 0, 255)) + " " +
                                    std::to_string(std::clamp(static_cast<int>(std::round(color.b * 255)), 0, 255));
            
            // for all pixels after first, check if adding this pixel would exceed the line length limit
            if (x > 0 && lineLength + pixelData.length() + 1 > 70) // +1 for the space before the pixelData
            {
                file << std::endl;
                lineLength = 0;
            } 
            else if (x > 0) // add a space before the pixel data if it's not the first pixel in a row
            {
                file << " ";
                lineLength++;
            }
            file << pixelData;
            lineLength += pixelData.length();
        }
        file << std::endl; // "some image programs (notably ImageMagick2) won’t process PPM files correctly unless the files are terminated by a newline character"
    }

    file.close();
}