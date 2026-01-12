#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 렌더링 품질 설정
     */
    struct RenderSettings
    {
        uint32 VirtualWidth  = 1280;  // 가상 너비 (게임 내 렌더링 해상도)
        uint32 VirtualHeight = 720;   // 가상 높이 (게임 내 렌더링 해상도)
        bool   PixelPerfect  = false; // 픽셀 퍼펙트 렌더링 여부 (픽셀 단위로 렌더링)
    };
} // namespace TDME