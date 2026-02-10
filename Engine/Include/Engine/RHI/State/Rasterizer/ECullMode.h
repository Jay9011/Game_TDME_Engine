#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 컬링 모드
     * @details 렌더링 시 제거할 면을 지정
     */
    enum class ECullMode : uint8
    {
        None,  /** 컬링 없음 (양면 렌더링) */
        Front, /** 앞면 컬링 (뒷면 렌더링) */
        Back,  /** 뒷면 컬링 (앞면 렌더링) - 기본 값 */
    };
} // namespace TDME