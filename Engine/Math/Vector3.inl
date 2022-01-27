#include "Vector3.hpp"

namespace fly
{
template <typename T>
constexpr Vector3<T>::Vector3(const T &a) : x(x), y(y), z(z)
{}

template <typename T>
constexpr Vector3<T>::Vector3(const T &x, const T &y, const T &z) : x(x), y(y), z(z)
{}

template <typename T>
template <typename K>
constexpr auto Vector3<T>::Add(const Vector3<K> &other) const
{
    return Vector3<decltype(x + other.x)>(x + other.x, y + other.y, z + other.z);
}

template <typename T>
template <typename K>
constexpr auto Vector3<T>::Sub(const Vector3<K> &other) const
{
    return Vector3<decltype(x - other.x)>(x - other.x, y - other.y, z - other.z);
}

template <typename T>
template <typename K>
constexpr auto Vector3<T>::Multiply(const K &other) const
{
    return Vector3<decltype(x * other)>(x * other, y * other, z * other);
}

template <typename T>
template <typename K>
constexpr auto Vector3<T>::Divide(const K &other) const
{
    return Vector3<decltype(x / other)>(x / other, y / other, z / other);
}

template <typename T>
template <typename K>
constexpr auto Vector3<T>::Cross(const Vector3<K> &other) const
{
    return Vector3<decltype(y * other.z - other.y * z)>(y * other.z - other.y * z, other.x * z - x * other.z, x * other.y - other.x * y);
}

template <typename T>
template <typename K>
constexpr auto Vector3<T>::Dot(const Vector3<K> &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

template <typename T>
constexpr auto Vector3<T>::Length() const
{
    return std::sqrt(LengthSquare());
}

template <typename T>
constexpr auto Vector3<T>::LengthSquare() const
{
    return Dot(*this);
}

template <typename T>
auto Vector3<T>::Normalize() const
{
    auto length = this->Length();
    return Vector3<decltype(x / length)>(x / length, y / length, z / length);
}

template <typename T>
template <typename K>
constexpr bool Vector3<T>::operator==(const Vector3<K> &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

template <typename T>
template <typename K>
constexpr bool Vector3<T>::operator!=(const Vector3<K> &other) const
{
    return !operator==(other);
}

template <typename T>
template <typename K>
constexpr Vector3<T> &Vector3<T>::operator+=(const Vector3<K> &other)
{
    *this = Add(other);
    return *this;
}

template <typename T>
template <typename K>
constexpr Vector3<T> &Vector3<T>::operator-=(const Vector3<K> &other)
{
    *this = Sub(other);
    return *this;
}

template <typename T>
template <typename K>
constexpr Vector3<T> &Vector3<T>::operator*=(const K &other)
{
    *this = Multiply(other);
    return *this;
};

template <typename T>
template <typename K>
constexpr Vector3<T> &Vector3<T>::operator/=(const K &other)
{
    *this = Divide(other);
    return *this;
};

template <typename K, typename J>
constexpr auto operator+(const Vector3<K> &left, const Vector3<J> &right)
{
    return left.Add(right);
}

template <typename K, typename J>
constexpr auto operator-(const Vector3<K> &left, const Vector3<J> &right)
{
    return left.Subtract(right);
}

template <typename K, typename J>
constexpr auto operator*(const J &left, const Vector3<K> &right)
{
    return right.Multiply(left);
}

template <typename K, typename J>
constexpr auto operator/(const Vector3<K> &left, const J &right)
{
    return left.Divide(right);
}

template <typename K>
std::ostream &operator<<(std::ostream &stream, const Vector3<K> &vector)
{
    return stream << vector.x << ", " << vector.y << ", " << vector.z;
}

};  // namespace fly