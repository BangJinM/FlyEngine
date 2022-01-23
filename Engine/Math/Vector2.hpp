#pragma once

#include <cstdint>

namespace fly
{

template <typename T>
class Vector2
{
public:
    constexpr explicit Vector2(const T &a);
    constexpr Vector2(const T &x, const T &y);

    /**
     * @brief 加法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    template <typename K>
    constexpr auto Add(const Vector2<K> &other) const;

    /**
     * @brief 减法
     *
     * @param other
     * @return template <typename K> constexpr
     */
    template <typename K>
    constexpr auto Sub(const Vector2<K> &other) const;

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
    constexpr auto Cross(const Vector2<K> &other) const;

    /**
     * @brief 点乘
     *
     * @tparam K
     * @param other
     * @return constexpr auto
     */
    template <typename K>
    constexpr auto Dot(const Vector2<K> &other) const;

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
    constexpr bool operator==(const Vector2<K> &other) const;

    /**
     * @brief !=
     *
     * @tparam K
     * @param other
     * @return true
     * @return false
     */
    template <typename K>
    constexpr bool operator!=(const Vector2<K> &other) const;

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector2&
     */
    template <typename K>
    constexpr Vector2 &operator+=(const Vector2<K> &other);

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector2&
     */
    template <typename K>
    constexpr Vector2 &operator-=(const Vector2<K> &other);

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector2&
     */
    template <typename K>
    constexpr Vector2 &operator*=(const K &other);

    /**
     * @brief
     *
     * @tparam K
     * @param other
     * @return constexpr Vector2&
     */
    template <typename K>
    constexpr Vector2 &operator/=(const K &other);

public:
    T x = 0;
    T y = 0;

public:
    static const Vector2 Zero;
    static const Vector2 One;
};

using Vector2f  = Vector2<float>;
using Vector2d  = Vector2<double>;
using Vector2i  = Vector2<int32_t>;
using Vector2ui = Vector2<uint32_t>;
using Vector2us = Vector2<uint16_t>;
};  // namespace fly