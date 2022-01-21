#include "Vector2.hpp"

namespace fly
{
template <typename T>
constexpr Vector2<T>::Vector2(const T &a) : x(a), y(a)
{}

template <typename T>
constexpr Vector2<T>::Vector2(const T &x, const T &y) : x(x), y(y)
{}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Add(const Vector2<K> &other) const
{
    return Vector2<decltype(x + other.x)>(x + other.x, y + other.y);
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Sub(const Vector2<K> &other) const
{
    return Vector2<decltype(x - other.x)>(x - other.x, y - other.y);
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Multiply(const K &other) const
{
    return Vector2<decltype(x * other)>(x * other, y * other);
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Cross(const Vector2<K> &other) const
{
    return Vector2<decltype(vec2.Y * vec1.X)>(x * other.x - x * other.y, y * other.x - y * other.y);
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Dot(const Vector2<K> &other) const
{
    return x * other.x + y * other.y;
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Angle(const Vector2<K> &other) const
{}

template <typename T>
template <typename K, typename J>
constexpr auto Vector2<T>::Lerp(const Vector2<K> &other, const J &progression) const
{}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Scale(const K &scalar) const
{}

template <typename T>
template <typename K>
auto Vector2<T>::Rotate(const K &angle) const
{}

};  // namespace fly