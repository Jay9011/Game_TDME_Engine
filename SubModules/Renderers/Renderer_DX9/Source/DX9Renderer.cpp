#include "pch.h"
#include "Renderer_DX9/DX9Renderer.h"

#include <Core/Math/TVector2.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Transformations.h>
#include <Core/Types/Color32.h>
#include <Engine/RHI/State/DepthStencil/DepthStencilStateDesc.h>
#include <Engine/RHI/State/Rasterizer/RasterizerStateDesc.h>
#include <Engine/RHI/Vertex/IVertexLayout.h>
#include <Engine/RHI/State/IRasterizerState.h>
#include <Engine/RHI/State/IBlendState.h>
#include <Engine/RHI/State/IDepthStencilState.h>
#include <Engine/RHI/Texture/ITexture.h>

#include "Renderer_DX9/DX9Device.h"
#include "Renderer_DX9/Vertex/DX9VertexLayout.h"
#include "Renderer_DX9/DX9TypeConversion.h"

//////////////////////////////////////////////////////////////
// Matrix 와 D3DMATRIX 호환성 검증
//////////////////////////////////////////////////////////////
static_assert(sizeof(TDME::Matrix) == sizeof(D3DMATRIX), "Matrix and D3DMATRIX must have the same size");
static_assert(sizeof(TDME::Matrix) == sizeof(float) * 16, "Matrix must be 16 bytes (16 floats)");

namespace TDME
{
    DX9Renderer::DX9Renderer() : m_device(nullptr), m_nativeDevice(nullptr)
    {
    }

    DX9Renderer::~DX9Renderer()
    {
    }

    bool DX9Renderer::Initialize(IWindow* window)
    {
        if (!m_device || !m_nativeDevice)
        {
            return false;
        }

        m_nativeDevice->SetRenderState(D3DRS_LIGHTING, FALSE); // DX9 전용: 고정 기능 라이팅 비활성화 (셰이더에서 처리 예정)

        return true;
    } // bool DX9Renderer::Initialize(IWindow* window)

    void DX9Renderer::Shutdown()
    {
        m_currentLayout = nullptr;
        m_nativeDevice  = nullptr;
        m_device        = nullptr;
    }

    void DX9Renderer::BeginFrame(const Color& clearColor)
    {
        // Color -> D3DCOLOR 변환
        D3DCOLOR backColor = D3DCOLOR_XRGB(
            static_cast<uint8>(clearColor.R * 255),
            static_cast<uint8>(clearColor.G * 255),
            static_cast<uint8>(clearColor.B * 255));

        m_nativeDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
        m_nativeDevice->BeginScene();
    }

    void DX9Renderer::EndFrame()
    {
        m_nativeDevice->EndScene();
    }

    void DX9Renderer::SetWorldMatrix(const Matrix& matrix)
    {
        m_nativeDevice->SetTransform(D3DTS_WORLD, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetViewMatrix(const Matrix& matrix)
    {
        m_nativeDevice->SetTransform(D3DTS_VIEW, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetProjectionMatrix(const Matrix& matrix)
    {
        m_nativeDevice->SetTransform(D3DTS_PROJECTION, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetRasterizerState(IRasterizerState* state)
    {
        if (!state)
            return;

        const RasterizerStateDesc& desc = state->GetDesc();
        m_nativeDevice->SetRenderState(D3DRS_CULLMODE, ToDX9CullMode(desc.CullMode));
        m_nativeDevice->SetRenderState(D3DRS_FILLMODE, ToDX9FillMode(desc.FillMode));
    }

    void DX9Renderer::SetBlendState(IBlendState* state)
    {
        if (!state)
            return;

        const BlendStateDesc& desc = state->GetDesc();
        m_nativeDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, desc.BlendEnable ? TRUE : FALSE);

        if (desc.BlendEnable)
        {
            m_nativeDevice->SetRenderState(D3DRS_SRCBLEND, ToDX9BlendFactor(desc.SrcBlend));
            m_nativeDevice->SetRenderState(D3DRS_DESTBLEND, ToDX9BlendFactor(desc.DestBlend));
            m_nativeDevice->SetRenderState(D3DRS_BLENDOP, ToDX9BlendOp(desc.BlendOp));
        }
    }

    void DX9Renderer::SetDepthStencilState(IDepthStencilState* state)
    {
        if (!state)
            return;

        const DepthStencilStateDesc& desc = state->GetDesc();
        m_nativeDevice->SetRenderState(D3DRS_ZENABLE, desc.DepthEnable ? TRUE : FALSE);
        m_nativeDevice->SetRenderState(D3DRS_ZWRITEENABLE, desc.DepthWriteEnable ? TRUE : FALSE);
        m_nativeDevice->SetRenderState(D3DRS_ZFUNC, ToDX9ComparisonFunc(desc.DepthFunc));
    }

    void DX9Renderer::SetTexture(uint32 slot, ITexture* texture)
    {
        if (!m_nativeDevice)
        {
            return;
        }

        if (texture)
        {
            IDirect3DTexture9* nativeTexture = static_cast<IDirect3DTexture9*>(texture->GetNativeHandle());
            m_nativeDevice->SetTexture(slot, nativeTexture);
        }
        else
        {
            m_nativeDevice->SetTexture(slot, nullptr);
        }
    }

    void DX9Renderer::ApplyRenderSettings(const RenderSettings& settings)
    {
        // TODO: 구현
    }

    void DX9Renderer::SetVertexLayout(IVertexLayout* layout)
    {
        if (m_currentLayout == layout)
            return;

        m_currentLayout = layout;

        if (layout)
        {
            DX9VertexLayout* dx9Layout = static_cast<DX9VertexLayout*>(layout);
            m_nativeDevice->SetVertexDeclaration(dx9Layout->GetNativeDeclaration());
        }
        else
        {
            m_nativeDevice->SetVertexDeclaration(nullptr);
        }
    }

    void DX9Renderer::DrawSprite(const SpriteDesc& sprite)
    {
        // TODO: 구현
        // 1. 텍스처 설정
        // 2. 쿼드 정점 생성 (position, size, pivot, rotation)
        // 3. UV 설정 (sourceRect)
        // 4. 색상/알파 적용
        // 5. DrawPrimitiveUp
    }

    void DX9Renderer::DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride)
    {
        if (!vertices || vertexCount == 0)
        {
            return;
        }

        uint32 primitiveCount = CalcPrimitiveCount(type, vertexCount);
        if (primitiveCount == 0)
        {
            return;
        }

        m_nativeDevice->DrawPrimitiveUP(ToDX9PrimitiveType(type), primitiveCount, vertices, stride);
    }

    //////////////////////////////////////////////////////////////
    // Getter / Setter
    //////////////////////////////////////////////////////////////

    void DX9Renderer::SetDevice(DX9Device* device)
    {
        m_device       = device;
        m_nativeDevice = device ? device->GetNativeDevice() : nullptr;
    }

} // namespace TDME
