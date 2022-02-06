#include "GraphicsCore/Base.hpp"
#include "GraphicsCore/DeviceManager.hpp"
#include "GraphicsCore/Shader.hpp"

#if FLY_USE_VULKAN
#    include <vulkan/vulkan.h> 

#    include "GraphicsVulkan/Device.hpp"
#    include "GraphicsVulkan/DeviceManagerImpl.hpp"
#    include "GraphicsVulkan/GraphicsVulkan.hpp"
#    include "GraphicsVulkan/Instance.hpp"

typedef struct DeviceManagerImpl DeviceManagerImpl;
#endif
