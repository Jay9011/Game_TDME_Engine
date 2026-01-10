#pragma once

#include "EVertexFormat.h"
#include "EVertexSemantic.h"

namespace TDME
{
    /**
     * @brief Vertex 구조체 내의 요소 정의
     * @details 각 렌더링 시스템에 전달하기 위해 필요한 정보를 담은 구조체 (상세 정보는 렌더러에 따라 다름)
     * @ref EVertexSemantic "EVertexSemantic"
     * @ref EVertexFormat "EVertexFormat"
     */
    struct VertexElement
    {
        EVertexSemantic Semantic;      // Vertex 속성 의미 (Position, TexCoord 등)
        uint8           SemanticIndex; // 동일 시멘틱의 인덱스 (TEXCOORD0, TEXCOORD1 등)
        EVertexFormat   Format;        // Vertex 데이터 포멧
        uint16          Offset;        // Vertex 구조체 내에서의 바이트 오프셋

        constexpr VertexElement()
            : Semantic(EVertexSemantic::Position), SemanticIndex(0), Format(EVertexFormat::Float3), Offset(0) {}

        constexpr VertexElement(EVertexSemantic semantic, EVertexFormat format, uint16 offset, uint8 semanticIndex = 0)
            : Semantic(semantic), SemanticIndex(semanticIndex), Format(format), Offset(offset) {}
    };
} // namespace TDME