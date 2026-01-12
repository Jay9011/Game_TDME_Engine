#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // VERTEX ATTRIBUTE SEMANTICS
    //////////////////////////////////////////////////////////////
    // 각 속성이 무엇을 의미하는지 나타내는 열거형
    // 셰이더에서 올바른 입력에 연결하기 위해 필요

    enum class EVertexSemantic : uint8
    {
        Position,     // 정점 위치
        Color,        // 정점 색상
        TexCoord,     // 텍스처 좌표 (UV)
        Normal,       // 법선 벡터
        Tangent,      // 접선 벡터 (탄젠트)
        Binormal,     // 바이노멀 벡터 (Bitangent)
        BlendWeight,  // Bone 가중치
        BlendIndices, // Bone 인덱스
        //////////////////////////////////////////////////////////////
        // 시스템 값 시멘틱
        //////////////////////////////////////////////////////////////
        SV_Position,   // 변환된 정점 위치 (정점 쉐이더에서 사용)
        SV_VertexID,   // 정점 인덱스
        SV_InstanceID, // 인스턴스 인덱스
    };
} // namespace TDME