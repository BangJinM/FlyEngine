#include <chrono>
#include <iostream>
#include <list>
#include <stdexcept>

#include "Log/Log.hpp"

#include "Math/Vector2.hpp"

using namespace fly;

int main(int argc, char const *argv[])
{
    Log::OpenLog("Logs/VectorTest.txt");
    Vector2 vec2 = fly::Vector2<float>(2.0, 20);
    Log::Info(vec2);
    Vector2 vec3 = fly::Vector2<float>(20, 2);
    Log::Info(vec3);
    Vector2 vec4 = vec2 + vec3;
    Log::Info(vec4);
    Vector2 vec5 = vec3 / 2;
    Log::Info(vec5);
    Vector2 vec6 = 2 * vec3;
    Log::Info(vec6);
    Vector2 vec7 = 2 * vec3;
    Log::Info(vec7);
    vec3 += Vector2<float>(1, 1);
    Log::Info(vec3);
    vec3 -= Vector2<float>(-2, -2);
    Log::Info(vec3);

    auto isTrue = vec3 == vec2;
    Log::Info(isTrue);

    Log::CloseLog();
    return 0;
}
