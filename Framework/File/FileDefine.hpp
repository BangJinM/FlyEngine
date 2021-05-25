#pragma once

namespace FlyEngine::File
{
typedef void *FilePtr;

enum class AssetOpenMode : int
{
    ASSET_OPEN_TEXT   = 0,  /// Open In Text Mode
    ASSET_OPEN_BINARY = 1,  /// Open In Binary Mode
};

}  // namespace FlyEngine::Memory