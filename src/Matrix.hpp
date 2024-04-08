#include <vector>

struct Matrix
{
    int rows = 3;
    int cols = 4; 
    int defaultValue = 0;
    std::vector<std::vector<int>> matrix;

    Matrix() : matrix(rows, std::vector<int>(cols, defaultValue)) {}
};