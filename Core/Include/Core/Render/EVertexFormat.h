#pragma once

#include "Core/CoreTypes.h"

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // VERTEX FORMAT
    //////////////////////////////////////////////////////////////
    // 데이터 포멧 (메모리 저장 방식)을 나타내는 열거형

    enum class EVertexFormat : uint8
    {
        Float1,  // float * 1
        Float2,  // float * 2 (Vector2)
        Float3,  // float * 3 (Vector3)
        Float4,  // float * 4 (Vector4)
        UByte4,  // uint8 * 4
        UByte4N, // uint8 * 4 (normalized, 0-255 -> 0.0-1.0)
    };
} // namespace TDME