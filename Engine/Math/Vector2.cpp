#include "Vector2.hpp"

#include <rttr/registration>

namespace fly
{
const Vector2f Vector2f::Zero = Vector2(0, 0);
const Vector2f Vector2f::One  = Vector2(0, 0);

const Vector2d Vector2d::Zero = Vector2(0, 0);
const Vector2d Vector2d::One  = Vector2(0, 0);

const Vector2i Vector2i::Zero = Vector2(0, 0);
const Vector2i Vector2i::One  = Vector2(0, 0);

const Vector2ui Vector2ui::Zero = Vector2(0, 0);
const Vector2ui Vector2ui::One  = Vector2(0, 0);

const Vector2us Vector2us::Zero = Vector2(0, 0);
const Vector2us Vector2us::One  = Vector2(0, 0);

};  // namespace fly

using namespace rttr;
RTTR_REGISTRATION  //注册反射
{
    registration::class_<fly::Vector2f>("Vector2f").constructor<Float32, Float32>().property("x", &fly::Vector2f::x).property("y", &fly::Vector2f::y);

    registration::class_<fly::Vector2d>("Vector2d").constructor<Double, Double>().property("x", &fly::Vector2d::x).property("y", &fly::Vector2d::y);

    registration::class_<fly::Vector2i>("Vector2i").constructor<Int32, Int32>().property("x", &fly::Vector2i::x).property("y", &fly::Vector2i::y);

    registration::class_<fly::Vector2ui>("Vector2ui")
        .constructor<Uint32, Uint32>()
        .property("x", &fly::Vector2ui::x)
        .property("y", &fly::Vector2ui::y);

    registration::class_<fly::Vector2us>("Vector2us")
        .constructor<Uint16, Uint16>()
        .property("x", &fly::Vector2us::x)
        .property("y", &fly::Vector2us::y);
}