#pragma once

#include <Core/CoreTypes.h>

#include "EBufferType.h"
#include "EBufferUsage.h"

namespace TDME
{
    /**
     * @brief 버퍼 설정 구조체
     * @details 버퍼의 타입, 사용 목적, 크기 등을 설정하는 구조체
     * @ref EBufferType "EBufferType"
     * @ref EBufferUsage "EBufferUsage"
     */
    struct BufferDesc
    {
        EBufferType  Type     = EBufferType::Vertex;
        EBufferUsage Usage    = EBufferUsage::Default;
        uint32       ByteSize = 0; // 버퍼 전체 크기 (바이트)
        uint32       Stride   = 0; // 요소 하나의 크기 (정점 버퍼용)
    };
} // namespace TDME