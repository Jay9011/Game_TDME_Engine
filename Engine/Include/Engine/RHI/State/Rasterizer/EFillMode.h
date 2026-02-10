#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 채우기 모드
     * @details 프리미티브를 와이어프레임/솔리드로 렌더링할지 결정
     */
    enum class EFillMode : uint8
    {
        Solid,     /** 솔리드 렌더링 - 기본 값 */
        Wireframe, /** 와이어프레임 렌더링 */
    };
} // namespace TDME