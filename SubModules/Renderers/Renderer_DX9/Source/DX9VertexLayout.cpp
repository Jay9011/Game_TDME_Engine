#include "pch.h"
#include "Renderer_DX9/DX9VertexLayout.h"

#include <Engine/RHI/Vertex/VertexLayoutDesc.h>

#include "Renderer_DX9/DX9TypeConversion.h"
#include <d3d9.h>
#include <vector>

namespace TDME
{
    DX9VertexLayout::DX9VertexLayout(IDirect3DDevice9* device, const VertexLayoutDesc& desc)
        : m_stride(desc.Stride), m_elementCount(desc.GetElementCount())
    {
        std::vector<D3DVERTEXELEMENT9> elements; // D3DVERTEXELEMENT9 배열 구성
        elements.reserve(desc.Elements.size() + 1);

        for (const auto& elem : desc.Elements)
        {
            D3DVERTEXELEMENT9 dx9Element = {
                0,                                            // Stream (단일 스트림)
                static_cast<WORD>(elem.Offset),               // Offset (바이트 오프셋)
                static_cast<BYTE>(ToDX9Type(elem.Format)),    // Type (데이터 타입)
                D3DDECLMETHOD_DEFAULT,                        // Method (데이터 접근 방법)
                static_cast<BYTE>(ToDX9Usage(elem.Semantic)), // Usage (데이터 의미)
                elem.SemanticIndex                            // SemanticIndex (동일 시멘틱의 인덱스)
            };
            elements.push_back(dx9Element);
        }

        // 종료 마커 추가
        D3DVERTEXELEMENT9 endMarker = D3DDECL_END();
        elements.push_back(endMarker);

        // VertexDeclaration 생성
        device->CreateVertexDeclaration(elements.data(), m_declaration.GetAddressOf());
    }

    uint32 DX9VertexLayout::GetStride() const
    {
        return m_stride;
    }

    size_t DX9VertexLayout::GetElementCount() const
    {
        return m_elementCount;
    }

    IDirect3DVertexDeclaration9* DX9VertexLayout::GetNativeDeclaration() const
    {
        return m_declaration.Get();
    }
} // namespace TDME