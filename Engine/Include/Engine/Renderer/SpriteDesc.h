#pragma once

#include <Core/Math/TVector2.h>
#include <Core/Types/Color.h>

#include "EPivot.h"

namespace TDME
{
    class ITexture;

    /**
     * @brief 스프라이트 렌더링 구조체
     */
    struct SpriteDesc
    {
        ITexture* Texture  = nullptr;         // 텍스처
        Vector2   Position = Vector2::Zero(); // 위치
        Vector2   Size     = Vector2::Zero(); // 크기 (0 이면 텍스처 원본 크기 사용)
        Vector2   Scale    = Vector2::One();  // 스케일
        float     Rotation = 0.0f;            // 회전 (도)
        Color     Tint     = Colors::WHITE;   // 색상 (텍스처 색상 틴트)
        EPivot    Pivot    = EPivot::Center;  // 피벗
        float     Depth    = 0.0f;            // Z 깊이 (정렬용)
    };
} // namespace TDME