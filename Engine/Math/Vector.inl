#include "Vector.hpp"

namespace fly
{
template <typename T, const size_t count>
constexpr Vector<T, count>::Vector(T value)
{
    for (size_t i = 0; i < count; i++)
    {
        values[i] = value;
    }
}

template <typename T, const size_t count>
constexpr Vector<T, count>::Vector(const Vector<T, count> &other)
{
    for (size_t i = 0; i < count; i++)
    {
        values[i] = other.values[i];
    }
}

template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::Add(const Vector<T, count> &other) const
{
    Vector<T, count> result = *this;
    for (size_t i = 0; i < count; i++)
    {
        result.values[i] += other.values[i];
    }
    return result;
}

template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::Sub(const Vector<T, count> &other) const
{
    Vector<T, count> result = *this;
    for (size_t i = 0; i < count; i++)
    {
        result.values[i] -= other.values[i];
    }
    return result;
}

template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::Multiply(const T &other) const
{
    Vector<T, count> result = *this;
    for (size_t i = 0; i < count; i++)
    {
        result.values[i] *= other;
    }
    return result;
}

template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::Divide(const T &other) const
{
    Vector<T, count> result = *this;
    for (size_t i = 0; i < count; i++)
    {
        result.values[i] /= other;
    }
    return result;
}

// template <typename T, const size_t count>
// constexpr auto Vector<T, count>::Cross(const Vector<T, count> &other) const
// {
//     return Vector<(x * other.x - x * other.y)>(x * other.x - x * other.y, y * other.x - y * other.y);
// }

// template <typename T, const size_t count>
// constexpr auto Vector<T, count>::Dot(const Vector<T, count> &other) const
// {

//     return x * other.x + y * other.y;
// }

template <typename T, const size_t count>
constexpr auto Vector<T, count>::Length() const
{
    return std::sqrt(LengthSquare());
}

template <typename T, const size_t count>
constexpr auto Vector<T, count>::LengthSquare() const
{
    return Dot(*this);
}

template <typename T, const size_t count>
auto Vector<T, count>::Normalize() const
{
    auto length = this->Length();
    return Vector<decltype(x / length)>(x / length, y / length);
}

template <typename T, const size_t count>
constexpr bool Vector<T, count>::operator==(const Vector<T, count> &other) const
{
    for (size_t i = 0; i < count; i++)
    {
        if (values[i] != other.values[i])
            return false;
    }

    return true;
}

template <typename T, const size_t count>
constexpr bool Vector<T, count>::operator!=(const Vector<T, count> &other) const
{
    for (size_t i = 0; i < count; i++)
    {
        if (values[i] == other.values[i])
            return false;
    }

    return true;
}

template <typename T, const size_t count>
constexpr Vector<T, count> &Vector<T, count>::operator+=(const Vector<T, count> &other)
{
    *this = Add(other);
    return *this;
};

template <typename T, const size_t count>
constexpr Vector<T, count> &Vector<T, count>::operator-=(const Vector<T, count> &other)
{
    *this = Sub(other);
    return *this;
};

template <typename T, const size_t count>
constexpr Vector<T, count> &Vector<T, count>::operator*=(const T &other)
{
    *this = Multiply(other);
    return *this;
};

template <typename T, const size_t count>
constexpr Vector<T, count> &Vector<T, count>::operator/=(const T &other)
{
    *this = Divide(other);
    return *this;
};

template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::operator+(const Vector<T, count> &other)
{
    return this->Add(other);
}
template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::operator-(const Vector<T, count> &other)
{
    return this->Sub(other);
}

template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::operator/(const T &other)
{
    return this->Divide(other);
}
template <typename T, const size_t count>
constexpr Vector<T, count> Vector<T, count>::operator*(const T &other)
{
    return this->Multiply(other);
}

};  // namespace fly