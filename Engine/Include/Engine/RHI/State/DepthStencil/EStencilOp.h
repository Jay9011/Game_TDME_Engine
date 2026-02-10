#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 스텐실 연산
     * @details 스텐실 테스트 결과에 따라 스텐실 버퍼에 수행할 연산
     */
    enum class EStencilOp : uint8
    {
        Keep,              /** 현재 스텐실 값 유지 */
        Zero,              /** 0으로 대체 */
        Replace,           /** 참조 값으로 대체 */
        Increment,         /** 순환 증가 (오버플로우시 0) */
        Decrement,         /** 순환 감소 (언더플로우시 최대값) */
        IncrementSaturate, /** 포화 증가 (최대값 제한, 클램프) */
        DecrementSaturate, /** 포화 감소 (최소값 제한, 0 클램프) */
        Invert,            /** 비트 반전 (0 -> 1, 1 -> 0) */
    };
} // namespace TDME