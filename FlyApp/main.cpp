
#include "App.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
    FlyEngine::App app;
    try {
        app.Init();
        app.Run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    app.Destroy();
    return 0;
}
