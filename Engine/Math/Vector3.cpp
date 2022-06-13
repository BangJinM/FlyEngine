#include "Vector3.hpp"
#include <rttr/registration>

namespace fly
{
const Vector3f Vector3f::Zero = Vector3(0, 0, 0);
const Vector3f Vector3f::One  = Vector3(0, 0, 0);

const Vector3d Vector3d::Zero = Vector3(0, 0, 0);
const Vector3d Vector3d::One  = Vector3(0, 0, 0);

const Vector3i Vector3i::Zero = Vector3(0, 0, 0);
const Vector3i Vector3i::One  = Vector3(0, 0, 0);

const Vector3ui Vector3ui::Zero = Vector3(0, 0, 0);
const Vector3ui Vector3ui::One  = Vector3(0, 0, 0);

const Vector3us Vector3us::Zero = Vector3(0, 0, 0);
const Vector3us Vector3us::One  = Vector3(0, 0, 0);

};  // namespace fly

using namespace rttr;
RTTR_REGISTRATION  //注册反射
{
    registration::class_<fly::Vector3f>("Vector3f")
        .constructor<Float32, Float32, Float32>()
        .property("x", &fly::Vector3f::x)
        .property("y", &fly::Vector3f::y)
        .property("z", &fly::Vector3f::z);

    registration::class_<fly::Vector3d>("Vector3d")
        .constructor<Double, Double, Double>()
        .property("x", &fly::Vector3d::x)
        .property("y", &fly::Vector3d::y)
        .property("z", &fly::Vector3d::z);

    registration::class_<fly::Vector3i>("Vector3i")
        .constructor<Int32, Int32, Int32>()
        .property("x", &fly::Vector3i::x)
        .property("y", &fly::Vector3i::y)
        .property("z", &fly::Vector3i::z);

    registration::class_<fly::Vector3ui>("Vector3ui")
        .constructor<Uint32, Uint32, Uint32>()
        .property("x", &fly::Vector3ui::x)
        .property("y", &fly::Vector3ui::y)
        .property("z", &fly::Vector3ui::z);

    registration::class_<fly::Vector3us>("Vector3us")
        .constructor<Uint16, Uint16, Uint16>()
        .property("x", &fly::Vector3us::x)
        .property("y", &fly::Vector3us::y)
        .property("z", &fly::Vector3us::z);
}