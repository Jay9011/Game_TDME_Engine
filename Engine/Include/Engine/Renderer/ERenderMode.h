#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 렌더링 모드 프리셋
     * @details 2D, 3D 렌더링 모드 세팅을 미리 정의한 열거형
     */
    enum class ERenderMode : uint8
    {
        /**
         * @brief 2D 렌더링 모드 (UI/오버레이 등)
         * @details Lighting OFF, Culling NONE, Z OFF
         */
        Mode2D,
        /**
         * @brief 2D 렌더링 모드 (2D 게임)
         * @details Lighting OFF, Culling NONE, Z ON
         */
        Mode2D_Z,
        /**
         * @brief 3D 렌더링 모드
         * @details Lighting ON, Culling CCW, Z ON
         */
        Mode3D,
    };
} // namespace TDME