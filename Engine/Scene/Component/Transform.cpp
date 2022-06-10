#include <Scene/Component/Transform.hpp>

#include <rttr/registration>

using namespace rttr;
RTTR_REGISTRATION  //注册反射
{
    registration::class_<fly::Transform>("Transform")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr)
        .property("position", &fly::Transform::GetPosition, &fly::Transform::SetPosition)
        .property("rotation", &fly::Transform::GetRotation, &fly::Transform::SetRotation)
        .property("scale", &fly::Transform::GetScale, &fly::Transform::SetScale);
}

namespace fly
{
void Transform::SetPosition(Vector3F position)
{
    this->position = position;
}
Vector3F Transform::GetPosition()
{
    return this->position;
}

void Transform::SetScale(Vector3F scale)
{
    this->scale = scale;
}
Vector3F Transform::GetScale()
{
    return this->scale;
}

void Transform::SetRotation(Vector3F rotation)
{
    this->rotation = rotation;
}
Vector3F Transform::GetRotation()
{
    return this->rotation;
}
};  // namespace fly