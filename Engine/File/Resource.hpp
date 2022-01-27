#pragma once

#include <filesystem>
#include <string>
#include <vector>

class Resource
{
    enum ResourceType
    {
        STRING,
        BYTES,
    };

public:
    Resource(std::filesystem::path path, ResourceType type, void* data) : path(path), resourceType(type), data(data) {}
    ~Resource() { delete[] data; }

    void*                 data;
    std::filesystem::path path;
    ResourceType          resourceType;
};
