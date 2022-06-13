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
Transform::Transform()
{
    position = Vector3f::Zero;
    scale    = Vector3f::Zero;
    rotation = Vector3f::Zero;
}
Transform::~Transform() {}

void Transform::SetPosition(Vector3f position)
{
    this->position = position;
}
Vector3f Transform::GetPosition()
{
    return this->position;
}

void Transform::SetScale(Vector3f scale)
{
    this->scale = scale;
}
Vector3f Transform::GetScale()
{
    return this->scale;
}

void Transform::SetRotation(Vector3f rotation)
{
    this->rotation = rotation;
}
Vector3f Transform::GetRotation()
{
    return this->rotation;
}
};  // namespace fly