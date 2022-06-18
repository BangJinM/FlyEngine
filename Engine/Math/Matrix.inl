#include "Matrix.hpp"
namespace fly
{
template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn>::Matrix()
{
    for (size_t row = 0; row < crow; row++)
        for (size_t column = 0; column < ccolumn; column++)
            values[row][column] = 0;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn>::Matrix(T value)
{
    for (size_t row = 0; row < crow; row++)
        for (size_t column = 0; column < ccolumn; column++)
            values[row][column] = value;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr T Matrix<T, crow, ccolumn>::operator[](int i) const
{
    unsigned int line = i / crow;
    unsigned int row  = i % ccolumn;
    if (line < crow, row < ccolumn)
        return values[line][row];
    return -1;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr bool Matrix<T, crow, ccolumn>::operator==(const Matrix<T, crow, ccolumn> &m2) const
{
    for (int i = 0; i < crow; ++i)
        for (int j = 0; j < ccolumn; ++j)
            if (m[i][j] != m2.m[i][j])
                return false;
    return true;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr bool Matrix<T, crow, ccolumn>::operator!=(const Matrix<T, crow, ccolumn> &m2) const
{
    for (int i = 0; i < crow; ++i)
        for (int j = 0; j < ccolumn; ++j)
            if (m[i][j] != m2.m[i][j])
                return true;
    return false;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn> Matrix<T, crow, ccolumn>::operator*(const T &other) const
{
    return this->Multiply(other);
}
template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn> Matrix<T, crow, ccolumn>::operator/(const T &other) const
{
    return this->Divide(other);
}

template <typename T, const size_t crow, const size_t ccolumn>
int Matrix<T, crow, ccolumn>::GetRowCount()
{
    return crow;
}

template <typename T, const size_t crow, const size_t ccolumn>
int Matrix<T, crow, ccolumn>::GetColumnCount()
{
    return ccolumn;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn> Matrix<T, crow, ccolumn>::Multiply(const T &other) const
{
    Matrix<T, crow, ccolumn> mat = *this;
    for (int i = 0; i < crow; ++i)
        for (int j = 0; j < ccolumn; ++j)
            mat.values[i][j] *= other;
    return mat;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn> Matrix<T, crow, ccolumn>::Divide(const T &other) const
{
    Matrix<T, crow, ccolumn> mat = *this;
    for (int i = 0; i < crow; ++i)
        for (int j = 0; j < ccolumn; ++j)
            mat.values[i][j] /= other;
    return mat;
}

template <typename T, const size_t crow, const size_t ccolumn>
constexpr Matrix<T, crow, ccolumn> Matrix<T, crow, ccolumn>::Cross(const Matrix<T, crow, ccolumn> &other)
{
    Matrix<T, crow, ccolumn> mat;
    return mat;
}

};  // namespace fly