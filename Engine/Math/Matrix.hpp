#pragma once

#include <Common/BaseDefines.hpp>

namespace fly
{
template <typename T, const size_t crow, const size_t ccolumn>
class Matrix
{
public:
    T values[crow][ccolumn] = {0};

public:
    constexpr Matrix();
    constexpr Matrix(T value);

    constexpr T operator[](int i) const;

    constexpr bool operator==(const Matrix<T, crow, ccolumn> &m2) const;
    constexpr bool operator!=(const Matrix<T, crow, ccolumn> &m2) const;

    constexpr Matrix<T, crow, ccolumn> operator*(const T &other) const;
    constexpr Matrix<T, crow, ccolumn> operator/(const T &other) const;

    int GetRowCount();
    int GetColumnCount();

    constexpr Matrix<T, crow, ccolumn> Multiply(const T &other) const;
    constexpr Matrix<T, crow, ccolumn> Divide(const T &other) const;
    constexpr Matrix<T, crow, ccolumn> Cross(const Matrix<T, crow, ccolumn> &other);
};


using Matrix4f = Matrix<Float32, 4, 4>;
using Matrix4i = Matrix<Int32, 4, 4>;
using Matrix3f = Matrix<Float32, 3, 3>;
using Matrix3i = Matrix<Int32, 3, 3>;

};  // namespace fly

#include "Matrix.inl"