#include "Matrix.hpp"

Matrix::Matrix() : rows(0), cols(0) {}
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols), elements(rows, std::vector<float>(cols, 0.0f)) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<float>> values) : rows(values.size()), cols(values.begin()->size()), elements(rows, std::vector<float>(cols))
{
    int i = 0;
    for (const auto &row : values)
    {
        if (row.size() != cols)
            throw std::invalid_argument("All rows must have the same number of columns!");
        std::copy(row.begin(), row.end(), elements[i].begin());
        ++i;
    }
}

Matrix Matrix::identity() const
{
    if (!is_square())
        throw std::invalid_argument("Matrix doesn't have an identity because it's not square!");

    int size = rows;
    Matrix m(size, size);
    for (int i = 0; i < size; ++i)
        m.elements[i][i] = 1;
    return m;
}

Matrix Matrix::transpose() const
{
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.elements[j][i] = elements[i][j];
    return result;
}

bool Matrix::operator==(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        return false;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (std::fabs(elements[i][j] - other.elements[i][j]) >= EPSILON)
                return false;
    return true;
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrices must have the same dimensions for addition!");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] + other.elements[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction!");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] - other.elements[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (cols != other.rows)
        throw std::invalid_argument("Number of columns in first matrix must equal number of rows in second matrix!");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < other.cols; ++j)
            for (int k = 0; k < cols; ++k)
                result.elements[i][j] += elements[i][k] * other.elements[k][j];
    return result;
}

Tuple Matrix::operator*(const Tuple &tuple) const
{
    if (rows != 4 || cols != 4)
        throw std::invalid_argument("Matrix must be 4x4 for Tuple multiplication!");

    float x = elements[0][0] * tuple.x + elements[0][1] * tuple.y + elements[0][2] * tuple.z + elements[0][3] * tuple.w;
    float y = elements[1][0] * tuple.x + elements[1][1] * tuple.y + elements[1][2] * tuple.z + elements[1][3] * tuple.w;
    float z = elements[2][0] * tuple.x + elements[2][1] * tuple.y + elements[2][2] * tuple.z + elements[2][3] * tuple.w;

    return Tuple(x, y, z, tuple.w);
}

Matrix Matrix::operator*(float scalar) const
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] * scalar;
    return result;
}

Matrix Matrix::operator/(float scalar) const
{
    if (std::fabs(scalar) < EPSILON)
        throw std::invalid_argument("Division by zero!");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.elements[i][j] = elements[i][j] / scalar;
    return result;
}

Matrix Matrix::operator-() const
{
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.elements[i][j] = -elements[i][j];
    return result;
}

float &Matrix::at(int row, int col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        throw std::out_of_range("Matrix indices out of range!");
    return elements[row][col];
}

const float &Matrix::at(int row, int col) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        throw std::out_of_range("Matrix indices out of range!");
    return elements[row][col];
}

bool Matrix::is_square() const
{
    return rows == cols;
}

void Matrix::print() const
{
    for (const auto &row : elements)
    {
        for (float val : row)
            std::cout << std::fixed << std::setprecision(2) << val << " ";
        std::cout << std::endl;
    }
}