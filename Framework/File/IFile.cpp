#include "IFile.hpp"
namespace FlyEngine::File
{
void IFile::AddSearchPath(std::string searchPath)
{
    for (auto path : fullpathList)
    {
        if (path == searchPath)
            return;
    }

    fullpathList.push_back(searchPath);
}
}  // namespace FlyEngine::Memory