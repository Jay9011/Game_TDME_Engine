#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    enum class EPrimitiveType : uint8
    {
        PointList,     // 점 리스트
        LineList,      // 선 리스트 (2개씩 연결)
        LineStrip,     // 연결된 선
        TriangleList,  // 삼각형 리스트 (3개씩 연결)
        TriangleStrip, // 연결된 삼각형
        TriangleFan,   // 삼각형 팬 (중심점과 주변 점들을 삼각형으로 연결)
    };
} // namespace TDME