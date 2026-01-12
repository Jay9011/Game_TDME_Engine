#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 텍스처 사용 목적
     * @details 텍스처가 어떤 목적으로 사용되는지 나타내는 열거형
     */
    enum class ETextureUsage : uint8
    {
        Default,      // 일반 텍스처
        Dynamic,      // CPU에서 자주 갱신
        RenderTarget, // 렌더 타겟으로 사용
        DepthStencil, // 깊이/스텐실 버퍼로 사용
    };
} // namespace TDME