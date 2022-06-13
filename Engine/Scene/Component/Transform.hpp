#pragma once

#include <Common/BaseDefines.hpp>
#include <Math/Vector3.hpp>
#include <Scene/Component.hpp>

namespace fly
{
class Transform : Component
{
public:
    Vector3f position = Vector3f::Zero;
    Vector3f scale    = Vector3f::Zero;
    Vector3f rotation = Vector3f::Zero;

public:
    Transform();
    ~Transform();

    void     SetPosition(Vector3f position);
    Vector3f GetPosition();

    void     SetScale(Vector3f scale);
    Vector3f GetScale();

    void     SetRotation(Vector3f rotation);
    Vector3f GetRotation();
};
};  // namespace fly