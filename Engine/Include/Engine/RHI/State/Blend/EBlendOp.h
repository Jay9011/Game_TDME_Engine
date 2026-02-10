#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 블렌드 연산
     * @details 소스와 대상 색상을 결합하는 연산 방식
     */
    enum class EBlendOp : uint8
    {
        Add,             /** Src + Dest (더하기) */
        Subtract,        /** Src - Dest (빼기) */
        ReverseSubtract, /** Dest - Src (반대로 빼기) */
        Min,             /** Min(Src, Dest) (최소값) */
        Max,             /** Max(Src, Dest) (최대값) */
    };
} // namespace TDME