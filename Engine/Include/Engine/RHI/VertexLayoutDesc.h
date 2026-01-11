#pragma once

#include <Core/CoreMacros.h>
#include <Core/CoreTypes.h>

#include "VertexElement.h"

#include <vector>

namespace TDME
{
    /**
     * @brief Vertex 데이터 포멧의 바이트 크기를 반환
     * @param format 데이터 포멧
     * @return 바이트 크기
     */
    FORCE_INLINE constexpr uint16 GetFormatSize(EVertexFormat format)
    {
        switch (format)
        {
        case EVertexFormat::Float1:  return sizeof(float) * 1;
        case EVertexFormat::Float2:  return sizeof(float) * 2;
        case EVertexFormat::Float3:  return sizeof(float) * 3;
        case EVertexFormat::Float4:  return sizeof(float) * 4;
        case EVertexFormat::UByte4:  return sizeof(uint8) * 4;
        case EVertexFormat::UByte4N: return sizeof(uint8) * 4;
        case EVertexFormat::Color:   return sizeof(uint32);
        default:                     return 0;
        }
    }

    /**
     * @brief Vertex 레이아웃 (구조체 집합) 정의
     * @details VertexElement들의 집합으로 Vertext 구조를 정의
     * @ref VertexElement "VertexElement"
     */
    struct VertexLayoutDesc
    {
        std::vector<VertexElement> Elements;
        uint32                     Stride = 0; // Vertex 하나의 바이트 크기

        /**
         * @brief Vertex 레이아웃에 새로운 요소를 추가
         * @param semantic 속성 의미 (Position, TexCoord 등)
         * @param format 데이터 포멧
         * @param semanticIndex 동일 시멘틱의 인덱스 (TEXCOORD0, TEXCOORD1 등)
         * @return VertexLayoutDesc& 자기 자신의 참조(메서드 체이닝 가능)
         */
        VertexLayoutDesc& Add(EVertexSemantic semantic, EVertexFormat format, uint8 semanticIndex = 0)
        {
            uint16 offset = static_cast<uint16>(Stride);
            Elements.emplace_back(semantic, format, offset, semanticIndex);
            Stride += GetFormatSize(format);
            return *this;
        }

        /**
         * @brief Vertex 레이아웃의 요소 개수를 반환
         * @return 요소 개수
         */
        FORCE_INLINE size_t GetElementCount() const { return Elements.size(); }

        /**
         * @brief Vertex 레이아웃의 초기화
         */
        FORCE_INLINE void Clear()
        {
            Elements.clear();
            Stride = 0;
        }
    };
} // namespace TDME