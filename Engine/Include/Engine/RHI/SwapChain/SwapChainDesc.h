#pragma once

#include <Core/CoreTypes.h>

#include "ESwapEffect.h"

namespace TDME
{
    /**
     * @brief SwapChain 설정 구조체
     */
    struct SwapChainDesc
    {
        uint32      Width           = 0;                    // 백 버퍼 너비
        uint32      Height          = 0;                    // 백 버퍼 높이
        uint32      BackBufferCount = 2;                    // 백 버퍼 개수
        bool        VSync           = true;                 // 수직 동기화(VSync) 여부
        ESwapEffect SwapEffect      = ESwapEffect::Discard; // 버퍼 교환 방식
    };
} // namespace TDME