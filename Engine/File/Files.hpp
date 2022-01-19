// https://github.com/EQMG/Acid.git
#pragma once

#include "Common/BaseDefines.hpp"

#include <filesystem>
#include <istream>
#include <optional>

struct PHYSFS_File;

FLYENGINE_BEGIN_NAMESPACE

enum class FileMode
{
    Read,
    Write,
    Append
};

class BaseFStream
{
public:
    explicit BaseFStream(PHYSFS_File *file);
    virtual ~BaseFStream();

    size_t length();

protected:
    PHYSFS_File *file;
};

class IFStream : public BaseFStream, public std::istream
{
public:
    explicit IFStream(const std::filesystem::path &filename);
    virtual ~IFStream();
};

class OFStream : public BaseFStream, public std::ostream
{
public:
    explicit OFStream(const std::filesystem::path &filename, FileMode writeMode = FileMode::Write);
    virtual ~OFStream();
};

class FStream : public BaseFStream, public std::iostream
{
public:
    explicit FStream(const std::filesystem::path &filename, FileMode openMode = FileMode::Read);
    virtual ~FStream();
};

/**
 * @brief Module used for managing files on engine updates.
 */
class Files
{
public:
    Files(std::string arg);
    ~Files();

    /**
     * Adds an file search path.
     * @param path The path to add.
     */
    void AddSearchPath(const std::string &path);

    /**
     * Removes a file search path.
     * @param path The path to remove.
     */
    void RemoveSearchPath(const std::string &path);

    /**
     * Clears all file search paths.
     */
    void ClearSearchPath();

    /**
     * Gets if the path is found in one of the search paths.
     * @param path The path to look for.
     * @return If the path is found in one of the searches.
     */
    static bool ExistsInPath(const std::filesystem::path &path);

    /**
     * Reads a file found by real or partial path.
     * @param path The path to read.
     * @return The data read from the file.
     */
    static std::optional<std::string> Read(const std::filesystem::path &path);

    /**
     * Reads all bytes from file found by real or partial path.
     * @param path The path to read.
     * @return The data read from the file.
     */
    static std::vector<unsigned char> ReadBytes(const std::filesystem::path &path);

    /**
     * Finds all the files in a path.
     * @param path The path to search.
     * @param recursive If paths will be recursively searched.
     * @return The files found.
     */
    static std::vector<std::string> FilesInPath(const std::filesystem::path &path, bool recursive = true);

    /**
     * Gets the next line from a stream.
     * @param is The input stream.
     * @param t The next string.
     * @return The input stream.
     */
    static std::istream &SafeGetLine(std::istream &is, std::string &t);

private:
    std::vector<std::string> searchPaths;
};
FLYENGINE_END_NAMESPACE
