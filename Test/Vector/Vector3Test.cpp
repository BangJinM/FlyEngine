#include <chrono>
#include <iostream>
#include <list>
#include <stdexcept>

// #include "Log/Log.hpp"

#include "Math/Vector.hpp"

using namespace fly;

int main(int argc, char const *argv[])
{
    // Log::OpenLog("Logs/VectorTest.txt");
    Vector3f vec2 = Vector3f(1);
    // Log::Info(vec2);
    Vector3f vec3 = Vector3f(1);
    // Log::Info(vec3);
    Vector3f vec4 = vec2 + vec3;
    // Log::Info(vec4);
    Vector3f vec5 = vec3 / 2;
    // Log::Info(vec5);
    Vector3f vec6 = vec3 * 2;
    // Log::Info(vec6);
    Vector3f vec7 = vec3;
    // Log::Info(vec7);
    vec3 += Vector3f(1);
    // Log::Info(vec3);
    vec3 -= Vector3f(1);
    // Log::Info(vec3);

    bool isTrue = vec3 == vec2;
    // Log::Info("==", isTrue);
    isTrue = vec3 != vec2;
    // Log::Info(isTrue);

    vec3 += vec3;
    // Log::Info(vec3);
    vec3 -= vec3;
    // Log::Info(vec3);
    vec3 *= 3;
    // Log::Info(vec3);
    vec3 /= 3;
    // Log::Info(vec3);

    return 0;
}
