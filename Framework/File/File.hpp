#pragma once

#include "IFile.hpp"

namespace FlyEngine::File
{
class File : public IFile
{
public:
    virtual FilePtr OpenFile(const std::string fullPath, AssetOpenMode mode) override;

    virtual void CloseFile(FilePtr &fp) override;

    virtual size_t SyncRead(const FilePtr &fp, Memory::Buffer &buf) override;

    virtual void WriteFile(const std::string &file, const std::string fullPath) override;

    virtual size_t GetFileSize(const FilePtr &fp) override;

    virtual bool FileExists(const std::string fullPath) override;

    virtual Memory::Buffer SyncOpenAndReadText(const std::string filePath) override;

    virtual Memory::Buffer SyncOpenAndReadBinary(const std::string filePath) override;
};

}  // namespace FlyEngine::Memory