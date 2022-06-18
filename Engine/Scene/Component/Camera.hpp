#pragma once

#include <vector>

#include <Common/BaseDefines.hpp>
#include <Scene/Component.hpp>

namespace fly
{
/// 相机投影类型
enum Projection
{
    Perspective  = 0,  //透视投影
    Orthographic = 1   //正交投影
};

class Camera : Component
{
public:
    Float32 near;         //近摄像机平面距离
    Float32 far;          //远摄像机平面距离
    Float32 fieldOfView;  //摄像机夹角
    Float32 width;        //宽度
    Float32 height;       //高度

    // glm::mat4 view_mat4_;        //指定相机坐标和朝向
    // glm::mat4 projection_mat4_;  //指定相机范围

    static std::vector<Camera *> allCameras;  //所有Camera，每一帧都遍历Camera，设置current_camera_。
    static Camera *currentCamera;  //当前用于渲染的Camera，就是MeshRenderer在计算MVP的时候，用这个Camera的View Projection矩阵计算MVP。
public:
    Camera();
    ~Camera();

    Float32 GetNear() { return near; }
    void SetNear(Float32 near) { this->near = near; }

    Float32 GetFar() { return far; }
    void SetFar(Float32 far) { this->far = far; }

    Float32 GetFieldofView() { return fieldOfView; }
    void SetFieldofView(Float32 fieldOfView) { this->fieldOfView = fieldOfView; }

    Float32 GetWidth() { return width; }
    void SetWidth(Float32 width) { this->width = width; }

    Float32 GetHeigth() { return height; }
    void SetHeigth(Float32 height) { this->height = height; }
};
};  // namespace fly