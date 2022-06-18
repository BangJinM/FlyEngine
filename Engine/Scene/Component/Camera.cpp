#include <Scene/Component/Camera.hpp>

#include <rttr/registration>
using namespace rttr;
RTTR_REGISTRATION  //注册反射
{
    registration::class_<fly::Camera>("Camera")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr)
        .property("near", &fly::Camera::GetNear, &fly::Camera::SetNear)
        .property("far", &fly::Camera::GetFar, &fly::Camera::SetFar)
        .property("fieldOfView", &fly::Camera::GetFieldofView, &fly::Camera::SetFieldofView)
        .property("width", &fly::Camera::GetWidth, &fly::Camera::SetWidth)
        .property("height", &fly::Camera::GetHeigth, &fly::Camera::SetHeigth);
}

namespace fly
{};  // namespace fly