#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief Viewport 설정
     * @details 렌더링 영역의 위치, 크기, 깊이 범위 정의
     */
    struct Viewport
    {
        float X        = 0.f;
        float Y        = 0.f;
        float Width    = 0.f;
        float Height   = 0.f;
        float MinDepth = 0.f;
        float MaxDepth = 1.f;
    };
} // namespace TDME