#include <chrono>
#include <iostream>
#include <list>
#include <stdexcept>

#include "Log/Log.hpp"

#include "Math/Vector3.hpp"

using namespace fly;

int main(int argc, char const *argv[])
{
    Log::OpenLog("Logs/VectorTest.txt");
    Vector3 vec2 = Vector3<float>(0, 0, 0);
    Log::Info(vec2);
    Vector3 vec3 = Vector3<float>(1, 1, 1);
    Log::Info(vec3);
    Vector3 vec4 = vec2 + vec3;
    Log::Info(vec4);
    Vector3 vec5 = vec3 / 2;
    Log::Info(vec5);
    Vector3 vec6 = 2 * vec3;
    Log::Info(vec6);
    Vector3 vec7 = 2 * vec3;
    Log::Info(vec7);
    vec3 += Vector3<float>(1, 1, 1);
    Log::Info(vec3);
    vec3 -= Vector3<float>(1, 1, 1);
    Log::Info(vec3);

    bool isTrue = vec3 == vec2;
    Log::Info("==", isTrue);
    isTrue = vec3 != vec2;
    Log::Info(isTrue);

    vec3 += vec3;
    Log::Info(vec3);
    vec3 -= vec3;
    Log::Info(vec3);
    vec3 *= 3;
    Log::Info(vec3);
    vec3 /= 3;
    Log::Info(vec3);

    return 0;
}
