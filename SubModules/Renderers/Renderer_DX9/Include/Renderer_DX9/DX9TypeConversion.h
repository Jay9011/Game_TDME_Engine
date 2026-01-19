#pragma once

#include <Core/CoreMacros.h>
#include <Engine/RHI/Vertex/EVertexSemantic.h>
#include <Engine/RHI/Vertex/EVertexFormat.h>
#include <Engine/Renderer/EPrimitiveType.h>

#include <d3d9.h>

namespace TDME
{
    //////////////////////////////////////////////////////////////
    // Vertex 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3DDECLUSAGE ToDX9Usage(EVertexSemantic semantic)
    {
        switch (semantic)
        {
        case EVertexSemantic::Position:     return D3DDECLUSAGE_POSITION;
        case EVertexSemantic::Color:        return D3DDECLUSAGE_COLOR;
        case EVertexSemantic::TexCoord:     return D3DDECLUSAGE_TEXCOORD;
        case EVertexSemantic::Normal:       return D3DDECLUSAGE_NORMAL;
        case EVertexSemantic::Tangent:      return D3DDECLUSAGE_TANGENT;
        case EVertexSemantic::Binormal:     return D3DDECLUSAGE_BINORMAL;
        case EVertexSemantic::BlendWeight:  return D3DDECLUSAGE_BLENDWEIGHT;
        case EVertexSemantic::BlendIndices: return D3DDECLUSAGE_BLENDINDICES;
        default:                            return D3DDECLUSAGE_POSITION;
        }
    }

    constexpr FORCE_INLINE D3DDECLTYPE ToDX9Type(EVertexFormat format)
    {
        switch (format)
        {
        case EVertexFormat::Float1:  return D3DDECLTYPE_FLOAT1;
        case EVertexFormat::Float2:  return D3DDECLTYPE_FLOAT2;
        case EVertexFormat::Float3:  return D3DDECLTYPE_FLOAT3;
        case EVertexFormat::Float4:  return D3DDECLTYPE_FLOAT4;
        case EVertexFormat::Color:   return D3DDECLTYPE_D3DCOLOR;
        case EVertexFormat::UByte4:  return D3DDECLTYPE_UBYTE4;
        case EVertexFormat::UByte4N: return D3DDECLTYPE_UBYTE4N;
        default:                     return D3DDECLTYPE_FLOAT3;
        }
    }

    //////////////////////////////////////////////////////////////
    // Primitive Type 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3DPRIMITIVETYPE ToDX9PrimitiveType(EPrimitiveType type)
    {
        switch (type)
        {
        case EPrimitiveType::PointList:     return D3DPT_POINTLIST;
        case EPrimitiveType::LineList:      return D3DPT_LINELIST;
        case EPrimitiveType::LineStrip:     return D3DPT_LINESTRIP;
        case EPrimitiveType::TriangleList:  return D3DPT_TRIANGLELIST;
        case EPrimitiveType::TriangleStrip: return D3DPT_TRIANGLESTRIP;
        case EPrimitiveType::TriangleFan:   return D3DPT_TRIANGLEFAN;
        default:                            return D3DPT_TRIANGLELIST;
        }
    }

    constexpr FORCE_INLINE uint32 CalcPrimitiveCount(EPrimitiveType type, uint32 vertexCount)
    {
        switch (type)
        {
        case EPrimitiveType::PointList:     return vertexCount;
        case EPrimitiveType::LineList:      return vertexCount / 2;
        case EPrimitiveType::LineStrip:     return (vertexCount > 1) ? (vertexCount - 1) : 0;
        case EPrimitiveType::TriangleList:  return vertexCount / 3;
        case EPrimitiveType::TriangleStrip: return (vertexCount > 2) ? (vertexCount - 2) : 0;
        case EPrimitiveType::TriangleFan:   return (vertexCount > 2) ? (vertexCount - 2) : 0;
        default:                            return 0;
        }
    }
} // namespace TDME