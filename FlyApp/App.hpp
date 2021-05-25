#pragma once

#include <string>

namespace FlyEngine
{
namespace Backend
{
class FlyDevice;
}
class Window;

class App
{
private:
    void mainLoop();

public:
    void Init();
    void Destroy();
    void Run();

private:
    Backend::FlyDevice *p_FlyDevice;
    Window *            p_Window;
};

}  // namespace FlyEngine