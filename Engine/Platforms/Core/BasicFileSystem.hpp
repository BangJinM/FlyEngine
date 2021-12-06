#pragma once

#include "PlatformDefine.h"

FLYENGINE_PLATFORM_BEGIN_NAMESPACE

class BasicFileSystem
{
public:
    static BasicFile *OpenFile(FileOpenAttribs &OpenAttribs);
    static void       ReleaseFile(BasicFile *);

    static std::string GetFullPath(const Diligent::Char *strFilePath);

    static bool FileExists(const Diligent::Char *strFilePath);

    static void SetWorkingDirectory(const Diligent::Char *strWorkingDir) { m_strWorkingDirectory = strWorkingDir; }

    static const Diligent::String &GetWorkingDirectory() { return m_strWorkingDirectory; }

    static Diligent::Char GetSlashSymbol();

    static void CorrectSlashes(Diligent::String &Path, Diligent::Char SlashSymbol);

    static void SplitFilePath(const Diligent::String &FullName, Diligent::String *Path, Diligent::String *Name);

    static bool IsPathAbsolute(const Diligent::Char *strPath);

    static std::string SimplifyPath(const Diligent::Char *Path, Diligent::Char SlashSymbol);

    template <typename CallbackType>
    static void SplitPathList(const Diligent::Char *PathList, CallbackType Callback, const char Separator = ';')
    {
        const auto *Pos = PathList;
        while (*Pos != '\0')
        {
            while (*Pos != '\0' && *Pos == Separator)
                ++Pos;
            if (*Pos == '\0')
                break;

            const auto *End = Pos + 1;
            while (*End != '\0' && *End != Separator)
                ++End;

            if (!Callback(Pos, static_cast<size_t>(End - Pos)))
                break;

            Pos = End;
        }
    }

protected:
    static Diligent::String m_strWorkingDirectory;
};

FLYENGINE_END_NAMESPACE