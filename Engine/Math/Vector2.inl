#include "Vector2.hpp"

namespace fly
{
template <typename T>
constexpr Vector2<T>::Vector2(const T &a) : x(a), y(a)
{}

template <typename T>
constexpr Vector2<T>::Vector2(const T &x, const T &y) : x(x), y(y)
{}

};  // namespace fly