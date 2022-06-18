#pragma once

namespace FlyEngine::DAG
{
    enum NodeType : int
    {
        UNDEFINE = -1,
        PASS = 0,
        RESOURCE,
    };
}