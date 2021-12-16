#pragma once
#include "GraphicsCore/Image.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class ImageVk : public Image
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE