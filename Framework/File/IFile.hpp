#pragma once

#include <string>
#include <vector>

#include "FileDefine.hpp"
#include "Memory/Buffer.hpp"

namespace FlyEngine::File
{
typedef void *FilePtr;

class IFile
{
public:
    virtual FilePtr OpenFile(const std::string fullPath, AssetOpenMode mode) = 0;

    virtual void CloseFile(FilePtr &fp) = 0;

    virtual size_t SyncRead(const FilePtr &fp, Memory::Buffer &buf) = 0;

    virtual void WriteFile(const std::string &file, const std::string fullPath) = 0;

    virtual size_t GetFileSize(const FilePtr &fp) = 0;

    virtual bool FileExists(const std::string fullPath) = 0;

    virtual Memory::Buffer SyncOpenAndReadText(const std::string filePath) = 0;

    virtual Memory::Buffer SyncOpenAndReadBinary(const std::string filePath) = 0;

    void AddSearchPath(std::string searchPath);

protected:
    std::vector<std::string> fullpathList;
};
}  // namespace FlyEngine::File