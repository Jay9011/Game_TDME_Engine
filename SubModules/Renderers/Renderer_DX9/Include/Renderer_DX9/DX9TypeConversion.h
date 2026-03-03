#pragma once

#include <Core/CoreMacros.h>
#include <Engine/RHI/SwapChain/ESwapEffect.h>
#include <Engine/RHI/State/Blend/EBlendFactor.h>
#include <Engine/RHI/State/Blend/EBlendOp.h>
#include <Engine/RHI/State/DepthStencil/EComparisonFunc.h>
#include <Engine/RHI/State/Rasterizer/ECullMode.h>
#include <Engine/RHI/State/Rasterizer/EFillMode.h>
#include <Engine/RHI/Texture/ETextureFormat.h>
#include <Engine/RHI/Vertex/EVertexSemantic.h>
#include <Engine/RHI/Vertex/EVertexFormat.h>
#include <Engine/Renderer/EPrimitiveType.h>

#include <cassert>
#include <d3d9.h>
#include <d3d9types.h>

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
        //////////////////////////////////////////////////////////////
        // 미지원
        //////////////////////////////////////////////////////////////
        case EVertexSemantic::SV_Position:
        case EVertexSemantic::SV_VertexID:
        case EVertexSemantic::SV_InstanceID:
            assert(false && "SV_ semantics are not supported in DX9");
            return D3DDECLUSAGE_POSITION;
        }

        assert(false && "Unknown vertex semantic");
        return D3DDECLUSAGE_POSITION;
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
    // Texture 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3DFORMAT ToDX9TextureFormat(ETextureFormat format)
    {
        switch (format)
        {
        case ETextureFormat::R8G8B8A8: return D3DFMT_A8R8G8B8;
        case ETextureFormat::R8:       return D3DFMT_L8;
        case ETextureFormat::BC1:      return D3DFMT_DXT1;
        case ETextureFormat::BC3:      return D3DFMT_DXT5;
        case ETextureFormat::D24S8:    return D3DFMT_D24S8;
        default:                       return D3DFMT_A8R8G8B8;
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

    //////////////////////////////////////////////////////////////
    // SwapChain 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3DSWAPEFFECT ToDX9SwapEffect(ESwapEffect effect)
    {
        switch (effect)
        {
        case ESwapEffect::Discard:        return D3DSWAPEFFECT_DISCARD;
        case ESwapEffect::Sequential:     return D3DSWAPEFFECT_FLIP;
        case ESwapEffect::FlipDiscard:    return D3DSWAPEFFECT_DISCARD;
        case ESwapEffect::FlipSequential: return D3DSWAPEFFECT_FLIP;
        default:                          return D3DSWAPEFFECT_DISCARD;
        }
    }

    //////////////////////////////////////////////////////////////
    // State 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE DWORD ToDX9CullMode(ECullMode mode, bool frontCounterClockwise = false)
    {
        switch (mode)
        {
        case ECullMode::None: return D3DCULL_NONE;
        case ECullMode::Front:
            // Front face 컬링: FrontCCW이면 CCW를 컬링, 아니면 CW를 컬링
            return frontCounterClockwise ? D3DCULL_CCW : D3DCULL_CW;
        case ECullMode::Back:
            // Back face 컬링: FrontCCW이면 CW를 컬링, 아니면 CCW를 컬링
            return frontCounterClockwise ? D3DCULL_CW : D3DCULL_CCW;
        }

        assert(false && "Unknown cull mode");
        return D3DCULL_NONE;
    }

    constexpr FORCE_INLINE DWORD ToDX9FillMode(EFillMode mode)
    {
        switch (mode)
        {
        case EFillMode::Wireframe: return D3DFILL_WIREFRAME;
        case EFillMode::Solid:     return D3DFILL_SOLID;
        default:                   return D3DFILL_SOLID;
        }
    }

    constexpr FORCE_INLINE DWORD ToDX9BlendFactor(EBlendFactor factor)
    {
        switch (factor)
        {
        case EBlendFactor::Zero:         return D3DBLEND_ZERO;
        case EBlendFactor::One:          return D3DBLEND_ONE;
        case EBlendFactor::SrcAlpha:     return D3DBLEND_SRCALPHA;
        case EBlendFactor::InvSrcAlpha:  return D3DBLEND_INVSRCALPHA;
        case EBlendFactor::DestAlpha:    return D3DBLEND_DESTALPHA;
        case EBlendFactor::InvDestAlpha: return D3DBLEND_INVDESTALPHA;
        case EBlendFactor::SrcColor:     return D3DBLEND_SRCCOLOR;
        case EBlendFactor::InvSrcColor:  return D3DBLEND_INVSRCCOLOR;
        case EBlendFactor::DestColor:    return D3DBLEND_DESTCOLOR;
        case EBlendFactor::InvDestColor: return D3DBLEND_INVDESTCOLOR;
        default:                         return D3DBLEND_ONE;
        }
    }

    constexpr FORCE_INLINE DWORD ToDX9BlendOp(EBlendOp op)
    {
        switch (op)
        {
        case EBlendOp::Add:             return D3DBLENDOP_ADD;
        case EBlendOp::Subtract:        return D3DBLENDOP_SUBTRACT;
        case EBlendOp::ReverseSubtract: return D3DBLENDOP_REVSUBTRACT;
        case EBlendOp::Min:             return D3DBLENDOP_MIN;
        case EBlendOp::Max:             return D3DBLENDOP_MAX;
        default:                        return D3DBLENDOP_ADD;
        }
    }

    constexpr FORCE_INLINE DWORD ToDX9ComparisonFunc(EComparisonFunc func)
    {
        switch (func)
        {
        case EComparisonFunc::Never:        return D3DCMP_NEVER;
        case EComparisonFunc::Less:         return D3DCMP_LESS;
        case EComparisonFunc::Equal:        return D3DCMP_EQUAL;
        case EComparisonFunc::LessEqual:    return D3DCMP_LESSEQUAL;
        case EComparisonFunc::Greater:      return D3DCMP_GREATER;
        case EComparisonFunc::NotEqual:     return D3DCMP_NOTEQUAL;
        case EComparisonFunc::GreaterEqual: return D3DCMP_GREATEREQUAL;
        case EComparisonFunc::Always:       return D3DCMP_ALWAYS;
        default:                            return D3DCMP_LESS;
        }
    }
} // namespace TDME