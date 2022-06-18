#include <chrono>
#include <iostream>
#include <list>
#include <stdexcept>

#include "Math/Matrix.hpp"

using namespace fly;

int main(int argc, char const *argv[])
{
    fly::Matrix4f mat4 = fly::Matrix4f(1);
    fly::Matrix3f mat3;
    auto          i = mat4[4];

    fly::Matrix4f m  = mat4.Multiply(3);
    fly::Matrix4f m2 = mat4.Divide(3);

    auto m3  = mat4 * 4;
    auto m1 = mat4 / 4;
    return 0;
}
