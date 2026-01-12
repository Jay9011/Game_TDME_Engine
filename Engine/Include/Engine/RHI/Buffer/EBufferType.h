#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 버퍼 타입
     * @details 버퍼가 어떤 목적으로 사용되는지 나타내는 열거형
     */
    enum class EBufferType : uint8
    {
        Vertex, // 정점 버퍼
        Index,  // 인덱스 버퍼
    };
} // namespace TDME