#pragma once

#include "Common/BaseDefines.hpp"

namespace fly
{
template <typename T, const size_t count>
class Vector
{
public:
    T values[count];

public:
    static const Vector Zero;
    static const Vector One;

public:
    constexpr Vector(T);
    constexpr Vector(const Vector<T, count> &other);
    /**
     * @brief 加法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    constexpr Vector<T, count> Add(const Vector<T, count> &other) const;

    /**
     * @brief 减法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    constexpr Vector<T, count> Sub(const Vector<T, count> &other) const;

    /**
     * @brief 乘法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    constexpr Vector<T, count> Multiply(const T &other) const;

    /**
     * @brief 除法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    constexpr Vector<T, count> Divide(const T &other) const;

    // /**
    //  * @brief 叉乘
    //  *
    //  * @tparam K
    //  * @param other
    //  * @return constexpr auto
    //  */
    // constexpr auto Cross(const Vector<T, count> &other) const;

    // /**
    //  * @brief 点乘
    //  *
    //  * @tparam K
    //  * @param other
    //  * @return constexpr auto
    //  */
    // constexpr auto Dot(const Vector<T, count> &other) const;

    /**
     * @brief 长度
     *
     * @return auto
     */
    constexpr auto Length() const;

    /**
     * @brief 长度的平方
     *
     * @return auto
     */
    constexpr auto LengthSquare() const;

    /**
     * @brief 归一
     *
     * @return auto
     */
    auto Normalize() const;

    /**
     * @brief ==
     *
     * @tparam K
     * @param other
     * @return true
     * @return false
     */
    constexpr bool operator==(const Vector<T, count> &other) const;
    constexpr bool operator!=(const Vector<T, count> &other) const;

    constexpr Vector<T, count> &operator+=(const Vector<T, count> &other);
    constexpr Vector<T, count> &operator-=(const Vector<T, count> &other);

    constexpr Vector<T, count> &operator*=(const T &other);
    constexpr Vector<T, count> &operator/=(const T &other);

    constexpr Vector<T, count> operator+(const Vector<T, count> &other);
    constexpr Vector<T, count> operator-(const Vector<T, count> &other);

    constexpr Vector<T, count> operator/(const T &other);
    constexpr Vector<T, count> operator*(const T &other);
};

using Vector2f  = Vector<Float32, 2>;
using Vector2d  = Vector<Double, 2>;
using Vector2i  = Vector<Int32, 2>;
using Vector2ui = Vector<Uint32, 2>;
using Vector2us = Vector<Uint16, 2>;

using Vector3f  = Vector<Float32, 3>;
using Vector3d  = Vector<Double, 3>;
using Vector3i  = Vector<Int32, 3>;
using Vector3ui = Vector<Uint32, 3>;
using Vector3us = Vector<Uint16, 3>;

};  // namespace fly

#include "Vector.inl"