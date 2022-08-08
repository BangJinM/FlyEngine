#pragma once

namespace fly
{
template <typename T>
inline T Abs(T x)
{
    return x > 0 ? x : -x;
}

template <typename T>
inline T Sgn(T x)
{
    return (x < T(0) ? T(-1) : (x > T(0) ? T(1) : T(0)));
}

template <typename T>
inline T Sqr(T x)
{
    return x * x;
}

template <typename T>
inline bool IsPowerOfTwo(T n)
{
    return (n & (n - 1)) == 0;
}

inline bool IsEqualF(float lhs, float rhs, float precision = 0.000001f)
{
    return (Abs<float>(lhs - rhs) < precision);
}

inline bool IsNotEqualF(float lhs, float rhs, float precision = 0.000001f)
{
    return (Abs<float>(lhs - rhs) > precision);
}

}  // namespace fly