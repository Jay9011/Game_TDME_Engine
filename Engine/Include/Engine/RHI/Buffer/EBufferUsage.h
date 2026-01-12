#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 버퍼 사용 목적
     */
    enum class EBufferUsage : uint8
    {
        Default, // GPU 전용
        Dynamic, // CPU에서 자주 갱신
    };
} // namespace TDME