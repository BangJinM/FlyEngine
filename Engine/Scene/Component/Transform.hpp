#pragma once

#include <Common/BaseDefines.hpp>
#include <Math/Vector3.hpp>
#include <Scene/Component.hpp>

namespace fly
{
class Transform : Component
{
public:
    Vector3F position;
    Vector3F scale;
    Vector3F rotation;

public:
    void     SetPosition(Vector3F position);
    Vector3F GetPosition();

    void     SetScale(Vector3F scale);
    Vector3F GetScale();

    void     SetRotation(Vector3F rotation);
    Vector3F GetRotation();
};
};  // namespace fly