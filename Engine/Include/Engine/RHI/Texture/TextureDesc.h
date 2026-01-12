#pragma once

#include "ETextureFormat.h"
#include "ETextureUsage.h"

namespace TDME
{
    struct TextureDesc
    {
        uint32         Width     = 0;
        uint32         Height    = 0;
        uint32         MipLevels = 0; // 밉맵 레벨 수 (1: 밉맵 없음)
        ETextureFormat Format    = ETextureFormat::R8G8B8A8;
        ETextureUsage  Usage     = ETextureUsage::Default;
    };
} // namespace TDME