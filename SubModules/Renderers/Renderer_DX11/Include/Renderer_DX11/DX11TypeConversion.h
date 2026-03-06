#pragma once

#include <Core/CoreMacros.h>
#include <Engine/RHI/Buffer/EBufferType.h>
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
#include <d3d11.h>

namespace TDME
{
    constexpr FORCE_INLINE const char* ToDX11SemanticName(EVertexSemantic semantic)
    {
        switch (semantic)
        {
        case EVertexSemantic::Position:      return "POSITION";
        case EVertexSemantic::Color:         return "COLOR";
        case EVertexSemantic::TexCoord:      return "TEXCOORD";
        case EVertexSemantic::Normal:        return "NORMAL";
        case EVertexSemantic::Tangent:       return "TANGENT";
        case EVertexSemantic::Binormal:      return "BINORMAL";
        case EVertexSemantic::BlendWeight:   return "BLENDWEIGHT";
        case EVertexSemantic::BlendIndices:  return "BLENDINDICES";
        case EVertexSemantic::SV_Position:   return "SV_POSITION";
        case EVertexSemantic::SV_VertexID:   return "SV_VertexID";
        case EVertexSemantic::SV_InstanceID: return "SV_InstanceID";
        }

        assert(false && "Unknown vertex semantic");
        return "POSITION";
    }

    //////////////////////////////////////////////////////////////
    // Vertex 관련 변환 함수
    //////////////////////////////////////////////////////////////
    constexpr FORCE_INLINE const char* ToInputLayoutSemanticName(EVertexSemantic semantic)
    {
        switch (semantic)
        {
        case EVertexSemantic::Position:     return "POSITION";
        case EVertexSemantic::Color:        return "COLOR";
        case EVertexSemantic::TexCoord:     return "TEXCOORD";
        case EVertexSemantic::Normal:       return "NORMAL";
        case EVertexSemantic::Tangent:      return "TANGENT";
        case EVertexSemantic::Binormal:     return "BINORMAL";
        case EVertexSemantic::BlendWeight:  return "BLENDWEIGHT";
        case EVertexSemantic::BlendIndices: return "BLENDINDICES";
        //////////////////////////////////////////////////////////////
        // 미사용
        //////////////////////////////////////////////////////////////
        case EVertexSemantic::SV_Position:
        case EVertexSemantic::SV_VertexID:
        case EVertexSemantic::SV_InstanceID:
            assert(false && "SV_ semantics cannot be used in Input Layout");
            return "POSITION";
        }

        assert(false && "Unknown vertex semantic");
        return "POSITION";
    }

    constexpr FORCE_INLINE DXGI_FORMAT ToDX11Format(EVertexFormat format)
    {
        switch (format)
        {
        case EVertexFormat::Float1:  return DXGI_FORMAT_R32_FLOAT;
        case EVertexFormat::Float2:  return DXGI_FORMAT_R32G32_FLOAT;
        case EVertexFormat::Float3:  return DXGI_FORMAT_R32G32B32_FLOAT;
        case EVertexFormat::Float4:  return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case EVertexFormat::Color:   return DXGI_FORMAT_B8G8R8A8_UNORM;
        case EVertexFormat::UByte4:  return DXGI_FORMAT_R8G8B8A8_UINT;
        case EVertexFormat::UByte4N: return DXGI_FORMAT_R8G8B8A8_UNORM;
        default:                     return DXGI_FORMAT_R32G32B32A32_FLOAT;
        }
    }

    //////////////////////////////////////////////////////////////
    // Texture 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE DXGI_FORMAT ToDX11TextureFormat(ETextureFormat format)
    {
        switch (format)
        {
        case ETextureFormat::R8G8B8A8:          return DXGI_FORMAT_R8G8B8A8_UNORM;
        case ETextureFormat::R8:                return DXGI_FORMAT_R8_UNORM;
        case ETextureFormat::BC1:               return DXGI_FORMAT_BC1_UNORM;
        case ETextureFormat::BC3:               return DXGI_FORMAT_BC3_UNORM;
        case ETextureFormat::D24S8:             return DXGI_FORMAT_D24_UNORM_S8_UINT;
        case ETextureFormat::R16:               return DXGI_FORMAT_R16_UNORM;
        case ETextureFormat::R16G16B16A16:      return DXGI_FORMAT_R16G16B16A16_UNORM;
        case ETextureFormat::R32Float:          return DXGI_FORMAT_R32_FLOAT;
        case ETextureFormat::R32G32B32A32Float: return DXGI_FORMAT_R32G32B32A32_FLOAT;
        case ETextureFormat::D32Float:          return DXGI_FORMAT_D32_FLOAT;
        default:                                return DXGI_FORMAT_R8G8B8A8_UNORM;
        }
    }

    //////////////////////////////////////////////////////////////
    // Primitive Type 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3D11_PRIMITIVE_TOPOLOGY ToDX11Topology(EPrimitiveType type)
    {
        switch (type)
        {
        case EPrimitiveType::PointList:     return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
        case EPrimitiveType::LineList:      return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
        case EPrimitiveType::LineStrip:     return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
        case EPrimitiveType::TriangleList:  return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        case EPrimitiveType::TriangleStrip: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
        //////////////////////////////////////////////////////////////
        // 미지원
        //////////////////////////////////////////////////////////////
        case EPrimitiveType::TriangleFan:
            assert(false && "TriangleFan is not supported in DX11");
            return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
        }

        assert(false && "Unknown primitive type");
        return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    }

    //////////////////////////////////////////////////////////////
    // SwapChain 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE DXGI_SWAP_EFFECT ToDX11SwapEffect(ESwapEffect effect)
    {
        switch (effect)
        {
        case ESwapEffect::Discard:        return DXGI_SWAP_EFFECT_DISCARD;
        case ESwapEffect::Sequential:     return DXGI_SWAP_EFFECT_SEQUENTIAL;
        case ESwapEffect::FlipDiscard:    return DXGI_SWAP_EFFECT_FLIP_DISCARD;
        case ESwapEffect::FlipSequential: return DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        default:                          return DXGI_SWAP_EFFECT_DISCARD;
        }
    }

    //////////////////////////////////////////////////////////////
    // State 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3D11_CULL_MODE ToDX11CullMode(ECullMode mode)
    {
        switch (mode)
        {
        case ECullMode::None:  return D3D11_CULL_NONE;
        case ECullMode::Front: return D3D11_CULL_FRONT;
        case ECullMode::Back:  return D3D11_CULL_BACK;
        default:               return D3D11_CULL_NONE;
        }
    }

    constexpr FORCE_INLINE D3D11_FILL_MODE ToDX11FillMode(EFillMode mode)
    {
        switch (mode)
        {
        case EFillMode::Solid:     return D3D11_FILL_SOLID;
        case EFillMode::Wireframe: return D3D11_FILL_WIREFRAME;
        default:                   return D3D11_FILL_SOLID;
        }
    }

    constexpr FORCE_INLINE D3D11_BLEND ToDX11BlendFactor(EBlendFactor factor)
    {
        switch (factor)
        {
        case EBlendFactor::Zero:         return D3D11_BLEND_ZERO;
        case EBlendFactor::One:          return D3D11_BLEND_ONE;
        case EBlendFactor::SrcAlpha:     return D3D11_BLEND_SRC_ALPHA;
        case EBlendFactor::InvSrcAlpha:  return D3D11_BLEND_INV_SRC_ALPHA;
        case EBlendFactor::DestAlpha:    return D3D11_BLEND_DEST_ALPHA;
        case EBlendFactor::InvDestAlpha: return D3D11_BLEND_INV_DEST_ALPHA;
        case EBlendFactor::SrcColor:     return D3D11_BLEND_SRC_COLOR;
        case EBlendFactor::InvSrcColor:  return D3D11_BLEND_INV_SRC_COLOR;
        case EBlendFactor::DestColor:    return D3D11_BLEND_DEST_COLOR;
        case EBlendFactor::InvDestColor: return D3D11_BLEND_INV_DEST_COLOR;
        default:                         return D3D11_BLEND_ONE;
        }
    }

    constexpr FORCE_INLINE D3D11_BLEND_OP ToDX11BlendOp(EBlendOp op)
    {
        switch (op)
        {
        case EBlendOp::Add:             return D3D11_BLEND_OP_ADD;
        case EBlendOp::Subtract:        return D3D11_BLEND_OP_SUBTRACT;
        case EBlendOp::ReverseSubtract: return D3D11_BLEND_OP_REV_SUBTRACT;
        case EBlendOp::Min:             return D3D11_BLEND_OP_MIN;
        case EBlendOp::Max:             return D3D11_BLEND_OP_MAX;
        default:                        return D3D11_BLEND_OP_ADD;
        }
    }

    constexpr FORCE_INLINE D3D11_COMPARISON_FUNC ToDX11ComparisonFunc(EComparisonFunc func)
    {
        switch (func)
        {
        case EComparisonFunc::Never:        return D3D11_COMPARISON_NEVER;
        case EComparisonFunc::Less:         return D3D11_COMPARISON_LESS;
        case EComparisonFunc::Equal:        return D3D11_COMPARISON_EQUAL;
        case EComparisonFunc::LessEqual:    return D3D11_COMPARISON_LESS_EQUAL;
        case EComparisonFunc::Greater:      return D3D11_COMPARISON_GREATER;
        case EComparisonFunc::NotEqual:     return D3D11_COMPARISON_NOT_EQUAL;
        case EComparisonFunc::GreaterEqual: return D3D11_COMPARISON_GREATER_EQUAL;
        case EComparisonFunc::Always:       return D3D11_COMPARISON_ALWAYS;
        default:                            return D3D11_COMPARISON_LESS;
        }
    }

    //////////////////////////////////////////////////////////////
    // Buffer 관련 변환 함수
    //////////////////////////////////////////////////////////////

    constexpr FORCE_INLINE D3D11_BIND_FLAG ToDX11BindFlags(EBufferType type)
    {
        switch (type)
        {
        case EBufferType::Vertex:   return D3D11_BIND_VERTEX_BUFFER;
        case EBufferType::Index:    return D3D11_BIND_INDEX_BUFFER;
        case EBufferType::Constant: return D3D11_BIND_CONSTANT_BUFFER;
        }

        assert(false && "Unknown buffer type");
        return D3D11_BIND_VERTEX_BUFFER;
    }
} // namespace TDME