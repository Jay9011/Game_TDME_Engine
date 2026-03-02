#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 셰이더 스테이지
     * @details 리소스를 바인딩할 파이프라인 스테이지 지정용
     */
    enum class EShaderStage : uint8
    {
        Vertex,
        Pixel,
    };
} // namespace TDME