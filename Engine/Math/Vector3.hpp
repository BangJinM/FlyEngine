#pragma once

namespace fly
{
template <typename T>
class Vector3
{
public:
    constexpr explicit Vector3(const T &a);
    constexpr Vector3(const T &x, const T &y);

    /**
     * 加法
     */
    template <typename K>
    constexpr auto Add(const Vector3<K> &other) const;

    /**
     * 减法
     */
    template <typename K>
    constexpr auto Sub(const Vector3<K> &other) const;

    /**
     * 乘法
     */
    template <typename K>
    constexpr auto Multiply(const K &other) const;

    /**
     * 叉乘
     */
    template <typename K>
    constexpr auto Cross(const Vector3<K> &other) const;

    /**
     * 点乘
     */
    template <typename K>
    constexpr auto Dot(const Vector3<K> &other) const;

    /**
     * 归一
     */
    auto Normalize() const;

public:
    T x = 0;
    T y = 0;
    T z = 0;
};
};  // namespace fly