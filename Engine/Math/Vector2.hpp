#pragma once

namespace fly
{
template <typename T>
class Vector2
{
public:
    constexpr explicit Vector2(const T &a);
    constexpr Vector2(const T &x, const T &y);

    /**
     * 加法
     */
    template <typename K>
    constexpr auto Add(const Vector2<K> &other) const;

    /**
     * 减法
     */
    template <typename K>
    constexpr auto Sub(const Vector2<K> &other) const;

    /**
     * 乘法
     */
    template <typename K>
    constexpr auto Multiply(const K &other) const;

    /**
     * 叉乘
     */
    template <typename K>
    constexpr auto Cross(const Vector2<K> &other) const;

    /**
     * 叉乘
     */
    template <typename K>
    constexpr auto Dot(const Vector2<K> &other) const;

    template <typename K>
    constexpr auto Angle(const Vector2<K> &other) const;

    template <typename K, typename J = float>
    constexpr auto Lerp(const Vector2<K> &other, const J &progression) const;

    template <typename K = float>
    constexpr auto Scale(const K &scalar) const;

    template <typename K = float>
    auto Rotate(const K &angle) const;

public:
    T x = 0;
    T y = 0;
};
};  // namespace fly