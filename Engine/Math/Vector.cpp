#include "Vector.hpp"

#include <rttr/registration>

namespace fly
{
const Vector2f Vector2f::Zero = Vector2f(0);
const Vector2f Vector2f::One  = Vector2f(1);

const Vector2d Vector2d::Zero = Vector2d(0);
const Vector2d Vector2d::One  = Vector2d(1);

const Vector2i Vector2i::Zero = Vector2i(0);
const Vector2i Vector2i::One  = Vector2i(1);

const Vector2ui Vector2ui::Zero = Vector2ui(0);
const Vector2ui Vector2ui::One  = Vector2ui(1);

const Vector2us Vector2us::Zero = Vector2us(0);
const Vector2us Vector2us::One  = Vector2us(1);

const Vector3f Vector3f::Zero = Vector3f(0);
const Vector3f Vector3f::One  = Vector3f(1);

const Vector3d Vector3d::Zero = Vector3d(0);
const Vector3d Vector3d::One  = Vector3d(1);

const Vector3i Vector3i::Zero = Vector3i(0);
const Vector3i Vector3i::One  = Vector3i(1);

const Vector3ui Vector3ui::Zero = Vector3ui(0);
const Vector3ui Vector3ui::One  = Vector3ui(1);

const Vector3us Vector3us::Zero = Vector3us(0);
const Vector3us Vector3us::One  = Vector3us(1);

};  // namespace fly

using namespace rttr;
RTTR_REGISTRATION  //注册反射
{
    registration::class_<fly::Vector2f>("Vector2f").constructor<Float32>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector2d>("Vector2d").constructor<Double>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector2i>("Vector2i").constructor<Int32>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector2ui>("Vector2ui").constructor<Uint32>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector2us>("Vector2us").constructor<Uint16>().property("values", &fly::Vector2ui::values);

    registration::class_<fly::Vector3f>("Vector3f").constructor<Float32>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector3d>("Vector3d").constructor<Double>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector3i>("Vector3i").constructor<Int32>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector3ui>("Vector3ui").constructor<Uint32>().property("values", &fly::Vector2ui::values);
    registration::class_<fly::Vector3ui>("Vector3us").constructor<Uint16>().property("values", &fly::Vector2ui::values);
}