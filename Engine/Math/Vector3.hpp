#pragma once

#include "Common/BaseDefines.hpp"

#include <cstdint>
#include <ostream>

namespace fly
{
template <typename T>
class Vector3
{
public:
    constexpr explicit Vector3(const T &a);
    constexpr Vector3(const T &x, const T &y, const T &z);

    /**
     * @brief 加法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    template <typename K>
    constexpr auto Add(const Vector3<K> &other) const;

    /**
     * @brief 减法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    template <typename K>
    constexpr auto Sub(const Vector3<K> &other) const;

    /**
     * @brief 乘法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    template <typename K>
    constexpr auto Multiply(const K &other) const;

    /**
     * @brief 除法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    template <typename K>
    constexpr auto Divide(const K &other) const;

    /**
     * @brief 叉乘
     *
     * @tparam K
     * @param other
     * @return constexpr auto
     */
    template <typename K>
    constexpr auto Cross(const Vector3<K> &other) const;

    /**
     * @brief 点乘
     *
     * @tparam K
     * @param other
     * @return constexpr auto
     */
    template <typename K>
    constexpr auto Dot(const Vector3<K> &other) const;

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
    template <typename K>
    constexpr bool operator==(const Vector3<K> &other) const;

    /**
     * @brief !=
     *
     * @tparam K
     * @param other
     * @return true
     * @return false
     */
    template <typename K>
    constexpr bool operator!=(const Vector3<K> &other) const;

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector3&
     */
    template <typename K>
    constexpr Vector3 &operator+=(const Vector3<K> &other);

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector3&
     */
    template <typename K>
    constexpr Vector3 &operator-=(const Vector3<K> &other);

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector3&
     */
    template <typename K>
    constexpr Vector3 &operator*=(const K &other);

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector3&
     */
    template <typename K>
    constexpr Vector3 &operator/=(const K &other);

public:
    T x = 0;
    T y = 0;
    T z = 0;

public:
    static const Vector3 Zero;
    static const Vector3 One;
};

/**
 * @brief 加法
 *
 * @tparam K
 * @tparam J
 * @param vector
 * @return Vector3
 */
template <typename K, typename J>
constexpr auto operator+(const Vector3<K> &left, const Vector3<J> &right);

/**
 * @brief 减法
 *
 * @tparam K
 * @tparam J
 * @param vector
 * @return Vector3
 */
template <typename K, typename J>
constexpr auto operator-(const Vector3<K> &left, const Vector3<J> &right);

/**
 * @brief 乘法
 *
 * @tparam K
 * @tparam J
 * @param vector
 * @return Vector3
 */
template <typename K, typename J>
constexpr auto operator*(const J &left, const Vector3<K> &right);

/**
 * @brief 除法
 *
 * @tparam K
 * @tparam J
 * @param vector
 * @return Vector3
 */
template <typename K, typename J>
constexpr auto operator/(const Vector3<K> &left, const J &right);

template <typename K>
std::ostream &operator<<(std::ostream &stream, const Vector3<K> &vector);

using Vector3f  = Vector3<Float32>;
using Vector3d  = Vector3<Double>;
using Vector3i  = Vector3<Int32>;
using Vector3ui = Vector3<Uint32>;
using Vector3us = Vector3<Uint16>;
};  // namespace fly

#include "Vector3.inl"