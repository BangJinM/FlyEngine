#include <chrono>
#include <iostream>
#include <list>
#include <stdexcept>

#include "Common/BaseDefines.hpp"
#include "Interface/IApplication.h"

FLYENGINE_CORE_BEGIN_NAMESPACE

extern IApplication *g_pApplication;

FLYENGINE_END_NAMESPACE

USING_FLYENGINE_NAMESPACE(Core)

int main()
{
    if (g_pApplication)
    {
        std::chrono::high_resolution_clock::time_point m_LastUpdate = std::chrono::high_resolution_clock::now();
        try
        {
            if (!g_pApplication->CreateEngineWindow("Vulkan", 1280, 640))
                return -1;
            if (!g_pApplication->Initialize())
                return -1;
            if (!g_pApplication->InitEngine(1))
                return -1;

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
    return 0;
}
