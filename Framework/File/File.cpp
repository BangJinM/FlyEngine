#include "File.hpp"

namespace FlyEngine::File
{
IFile *IFile::pIFile = nullptr;

IFile *IFile::GetFileInstance()
{
    if (pIFile)
        return pIFile;
    pIFile = new File;
    return pIFile;
}

FilePtr File::OpenFile(const std::string fullPath, AssetOpenMode mode)
{
    FILE *fp = nullptr;
    for (auto src : fullpathList)
    {
        std::string absolutePath;

        absolutePath.append(src);
        absolutePath.append(fullPath);
#ifdef DEBUG
        fprintf(stderr, "Trying to open %s\n", absolutePath.c_str());
#endif
        switch (mode)
        {
#ifdef _WINDOWS
            case AssetOpenMode::ASSET_OPEN_TEXT: fopen_s(&fp, absolutePath.c_str(), "r"); break;
            case AssetOpenMode::ASSET_OPEN_BINARY: fopen_s(&fp, absolutePath.c_str(), "rb"); break;
#else
            case AssetOpenMode::ASSET_OPEN_TEXT: fp = fopen(absolutePath.c_str(), "r"); break;
            case AssetOpenMode::ASSET_OPEN_BINARY: fp = fopen(absolutePath.c_str(), "rb"); break;
#endif
        }

        if (fp)
            return (FilePtr)fp;
    }

    return nullptr;
}

void File::CloseFile(FilePtr &fp)
{
    fclose((FILE *)fp);
    fp = nullptr;
}

size_t File::SyncRead(const FilePtr &fp, Memory::Buffer &buf)
{
    size_t sz;

    if (!fp)
    {
        fprintf(stderr, "null file discriptor\n");
        return 0;
    }

    sz = fread(buf.m_pData, buf.GetDataSize(), 1, static_cast<FILE *>(fp));

    return sz;
}

void File::WriteFile(const std::string &file, const std::string fullPath)
{
    bool  exist = FileExists(fullPath.c_str());
    FILE *fp;
#ifdef _WINDOWS
    fopen_s(&fp, fullPath.c_str(), "w");
#else
    fp = fopen(fullPath.c_str(), "w");
#endif

    fwrite(file.c_str(), file.size(), 1, fp);
}

size_t File::GetFileSize(const FilePtr &fp)
{
    FILE *_fp = static_cast<FILE *>(fp);

    long pos = ftell(_fp);
    fseek(_fp, 0, SEEK_END);
    size_t length = ftell(_fp);
    fseek(_fp, pos, SEEK_SET);

    return length;
}

bool File::FileExists(const std::string fullPath)
{
    FilePtr fp = OpenFile(fullPath.c_str(), AssetOpenMode::ASSET_OPEN_BINARY);
    if (fp != nullptr)
    {
        CloseFile(fp);
        return true;
    }
    return false;
}

Memory::Buffer File::SyncOpenAndReadText(const std::string filePath)
{
    FilePtr         fp    = OpenFile(filePath, AssetOpenMode::ASSET_OPEN_TEXT);
    Memory::Buffer *pBuff = nullptr;

    if (fp)
    {
        size_t length = GetFileSize(fp);

        pBuff                    = new Memory::Buffer(length + 1);
        length                   = fread(pBuff->GetData(), 1, length, static_cast<FILE *>(fp));
        pBuff->GetData()[length] = '\0';
        CloseFile(fp);
    }
    else
    {
        // el::Loggers::getLogger("logger")->info("Error opening file '%s'\n", filePath);
        pBuff = new Memory::Buffer();
    }

#ifdef DEBUG
    fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

    return *pBuff;
}

Memory::Buffer File::SyncOpenAndReadBinary(const std::string filePath)
{
    FilePtr         fp    = OpenFile(filePath, AssetOpenMode::ASSET_OPEN_BINARY);
    Memory::Buffer *pBuff = nullptr;

    if (fp)
    {
        size_t length = GetFileSize(fp);

        pBuff = new Memory::Buffer(length);
        fread(pBuff->GetData(), length, 1, static_cast<FILE *>(fp));

        CloseFile(fp);
    }
    else
    {
        pBuff = new Memory::Buffer();
    }

#ifdef DEBUG
    fprintf(stderr, "Read file '%s', %d bytes\n", filePath, length);
#endif

    return *pBuff;
}
}  // namespace FlyEngine::File