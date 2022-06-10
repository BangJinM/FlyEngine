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
constexpr auto Vector2<T>::Divide(const K &other) const
{
    return Vector2<decltype(x / other)>(x / other, y / other);
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Cross(const Vector2<K> &other) const
{
    return Vector2<decltype(x * other.x - x * other.y)>(x * other.x - x * other.y, y * other.x - y * other.y);
}

template <typename T>
template <typename K>
constexpr auto Vector2<T>::Dot(const Vector2<K> &other) const
{
    return x * other.x + y * other.y;
}

template <typename T>
constexpr auto Vector2<T>::Length() const
{
    return std::sqrt(LengthSquare());
}

template <typename T>
constexpr auto Vector2<T>::LengthSquare() const
{
    return Dot(*this);
}

template <typename T>
auto Vector2<T>::Normalize() const
{
    auto length = this->Length();
    return Vector2<decltype(x / length)>(x / length, y / length);
}

template <typename T>
template <typename K>
constexpr bool Vector2<T>::operator==(const Vector2<K> &other) const
{
    return x == other.x && y == other.y;
}

template <typename T>
template <typename K>
constexpr bool Vector2<T>::operator!=(const Vector2<K> &other) const
{
    return !operator==(other);
}

template <typename T>
template <typename K>
constexpr Vector2<T> &Vector2<T>::operator+=(const Vector2<K> &other)
{
    *this = Add(other);
    return *this;
};

template <typename T>
template <typename K>
constexpr Vector2<T> &Vector2<T>::operator-=(const Vector2<K> &other)
{
    *this = Sub(other);
    return *this;
};

template <typename T>
template <typename K>
constexpr Vector2<T> &Vector2<T>::operator*=(const K &other)
{
    *this = Multiply(other);
    return *this;
};

template <typename T>
template <typename K>
constexpr Vector2<T> &Vector2<T>::operator/=(const K &other)
{
    *this = Divide(other);
    return *this;
};

/*************************************************************************************/

template <typename K, typename J>
constexpr auto operator+(const Vector2<K> &left, const Vector2<J> &right)
{
    return left.Add(right);
}

template <typename K, typename J>
constexpr auto operator-(const Vector2<K> &left, const Vector2<J> &right)
{
    return left.Subtract(right);
}

template <typename K, typename J>
constexpr auto operator*(const J &left, const Vector2<K> &right)
{
    return right.Multiply(left);
}

template <typename K, typename J>
constexpr auto operator/(const Vector2<K> &left, const J &right)
{
    return left.Divide(right);
}

template <typename K>
std::ostream &operator<<(std::ostream &stream, const Vector2<K> &vector)
{
    return stream << vector.x << ", " << vector.y;
}

};  // namespace fly