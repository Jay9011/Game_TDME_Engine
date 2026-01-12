#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 피벗 위치 (기준점)
     */
    enum class EPivot : uint8
    {
        Center,       // 중앙
        TopLeft,      // 좌상단
        TopCenter,    // 상단 중앙
        TopRight,     // 우상단
        MiddleLeft,   // 좌측 중앙
        MiddleRight,  // 우측 중앙
        BottomLeft,   // 좌하단
        BottomCenter, // 하단 중앙
        BottomRight,  // 우하단
    };
} // namespace TDME