
#include "App.hpp"

#include <iostream>
#include <stdexcept>

#include "Logger/Logger.hpp"
INITIALIZE_EASYLOGGINGPP

int main()
{
    LOG(INFO) << "App Start~~~~~~~~~~~~~~~~~";
    FlyEngine::App app;
    try
    {
        app.Init();
        app.Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    app.Destroy();
    return 0;
}
