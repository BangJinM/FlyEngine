#include <chrono>
#include <iostream>
#include <list>
#include <stdexcept>

#include "Common/BaseDefines.hpp"
#include "Common/IApplication.h"
// #include "File/Files.hpp"
#include "Log/Log.hpp"

FLYENGINE_BEGIN_NAMESPACE
extern IApplication *g_pApplication;
FLYENGINE_END_NAMESPACE

USING_FLYENGINE_NAMESPACE

int main(int argc, char const *argv[])
{
    Log::OpenLog("Logs/error.txt");
    if (argc <= 0) return -1;
    // Files *files = new Files(argv[0]);
    if (g_pApplication)
    {
        std::chrono::high_resolution_clock::time_point m_LastUpdate = std::chrono::high_resolution_clock::now();
        try
        {
            Log::Info("dafasdfa", "fjalsfjlasd");
            if (!g_pApplication->CreateEngineWindow("Vulkan", 1280, 640)) return -1;
            if (!g_pApplication->Initialize()) return -1;
            if (!g_pApplication->InitEngine(1)) return -1;

            while (!g_pApplication->IsQuit())
            {
                const auto time = std::chrono::high_resolution_clock::now();
                const auto dt   = std::chrono::duration_cast<std::chrono::duration<float>>(time - m_LastUpdate).count();
                m_LastUpdate    = time;
                g_pApplication->Tick(dt);
            }
            g_pApplication->Finalize();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }
    Log::CloseLog();
    return 0;
}

