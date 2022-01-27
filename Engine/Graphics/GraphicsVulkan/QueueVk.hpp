#pragma once
#include "GraphicsCore/Queue.hpp"

FLYENGINE_GRAPHICS_BEGIN_NAMESPACE

class QueueVk : public Queue
{
public:
    virtual void Initialize();
    virtual void Finalize();
};

FLYENGINE_END_NAMESPACE