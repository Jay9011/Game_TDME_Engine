#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief SwapChain 버퍼 교환 방식
     */
    enum class ESwapEffect : uint8
    {
        Discard,        // 이전 프레임 버리기
        Sequential,     // 이전 프레임 유지, 순차적 교환
        FlipDiscard,    // Flip 교환 방식, 이전 프레임 버리기
        FlipSequential, // Flip 교환 방식, 이전 프레임 유지, 순차적 교환
    };
} // namespace TDME