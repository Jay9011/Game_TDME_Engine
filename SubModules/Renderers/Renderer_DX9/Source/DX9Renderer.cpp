#include "pch.h"
#include "Renderer_DX9/DX9Renderer.h"

#include <Core/CoreTypes.h>
#include <Core/Math/TVector2.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Transformations.h>
#include <Core/Types/Color32.h>
#include <Engine/RHI/Buffer/IBuffer.h>
#include <Engine/RHI/IRHIDevice.h>
#include <Engine/RHI/Texture/ITexture.h>
#include <Engine/RHI/Viewport.h>

#include "Renderer_DX9/DX9Device.h"
#include "Renderer_DX9/Vertex/DX9VertexLayout.h"
#include "Renderer_DX9/Pipeline/DX9PipelineState.h"
#include "Renderer_DX9/DX9TypeConversion.h"

//////////////////////////////////////////////////////////////
// Matrix 와 D3DMATRIX 호환성 검증
//////////////////////////////////////////////////////////////
static_assert(sizeof(TDME::Matrix) == sizeof(D3DMATRIX), "Matrix and D3DMATRIX must have the same size");

namespace TDME
{
    DX9Renderer::DX9Renderer() : m_device(nullptr), m_nativeDevice(nullptr)
    {
    }

    DX9Renderer::~DX9Renderer()
    {
    }

    //////////////////////////////////////////////////////////////
    // IRenderer
    //////////////////////////////////////////////////////////////

    bool DX9Renderer::Initialize(IWindow* window)
    {
        if (!m_device || !m_nativeDevice)
            return false;

        m_nativeDevice->SetRenderState(D3DRS_LIGHTING, FALSE); // DX9 전용: 고정 기능 라이팅 비활성화 (셰이더에서 처리 예정)

        return true;
    } // bool DX9Renderer::Initialize(IWindow* window)

    void DX9Renderer::Shutdown()
    {
        m_currentVertexBuffer = nullptr;
        m_currentLayout       = nullptr;

        m_nativeDevice = nullptr;
        m_device       = nullptr;
    }

    void DX9Renderer::BeginFrame(const Color& clearColor)
    {
        ClearRenderTarget(clearColor);
        ClearDepthStencil(1.0f, 0);
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

    void DX9Renderer::ApplyRenderSettings(const RenderSettings& settings)
    {
        // TODO: 구현
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
            return;

        uint32 primitiveCount = CalcPrimitiveCount(type, vertexCount);
        if (primitiveCount == 0)
            return;

        m_nativeDevice->DrawPrimitiveUP(ToDX9PrimitiveType(type), primitiveCount, vertices, stride);
    }

    //////////////////////////////////////////////////////////////
    // IRHIContext
    //////////////////////////////////////////////////////////////

    void DX9Renderer::SetPipelineState(IPipelineState* pso)
    {
        // DX9에는 PSO가 없으므로, Desc 를 분해하여 각 상태 객체를 설정
        if (!pso)
            return;

        DX9PipelineState* dx9Pso = static_cast<DX9PipelineState*>(pso);

        // Rasterizer State
        const RasterizerStateDesc& rs = dx9Pso->RasterizerState;
        m_nativeDevice->SetRenderState(D3DRS_CULLMODE, ToDX9CullMode(rs.CullMode, rs.FrontCounterClockwise));
        m_nativeDevice->SetRenderState(D3DRS_FILLMODE, ToDX9FillMode(rs.FillMode));
        m_nativeDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, rs.ScissorEnable ? TRUE : FALSE);

        // Blend State
        const BlendStateDesc& bs = dx9Pso->BlendState;
        m_nativeDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, bs.BlendEnable ? TRUE : FALSE);
        if (bs.BlendEnable)
        {
            m_nativeDevice->SetRenderState(D3DRS_SRCBLEND, ToDX9BlendFactor(bs.SrcBlend));
            m_nativeDevice->SetRenderState(D3DRS_DESTBLEND, ToDX9BlendFactor(bs.DestBlend));
            m_nativeDevice->SetRenderState(D3DRS_BLENDOP, ToDX9BlendOp(bs.BlendOp));
        }

        // DepthStencil State
        const DepthStencilStateDesc& ds = dx9Pso->DepthStencilState;
        m_nativeDevice->SetRenderState(D3DRS_ZENABLE, ds.DepthEnable ? TRUE : FALSE);
        m_nativeDevice->SetRenderState(D3DRS_ZWRITEENABLE, ds.DepthWriteEnable ? TRUE : FALSE);
        m_nativeDevice->SetRenderState(D3DRS_ZFUNC, ToDX9ComparisonFunc(ds.DepthFunc));

        // InputLayout
        if (dx9Pso->InputLayout && m_currentLayout != dx9Pso->InputLayout)
        {
            m_currentLayout            = dx9Pso->InputLayout;
            DX9VertexLayout* dx9Layout = static_cast<DX9VertexLayout*>(m_currentLayout);
            m_nativeDevice->SetVertexDeclaration(dx9Layout->GetNativeDeclaration());
        }

        // Topology 저장
        m_currentTopology = dx9Pso->TopologyType;
    }

    void DX9Renderer::SetVertexBuffer(uint32 slot, IBuffer* buffer)
    {
        if (!buffer)
            return;

        if (slot == 0)
        {
            m_currentVertexBuffer = buffer;
        }

        IDirect3DVertexBuffer9* nativeVB = static_cast<IDirect3DVertexBuffer9*>(buffer->GetNativeHandle());
        m_nativeDevice->SetStreamSource(slot, nativeVB, 0, buffer->GetStride());
    }

    void DX9Renderer::SetIndexBuffer(IBuffer* buffer)
    {
        if (!buffer)
            return;

        IDirect3DIndexBuffer9* nativeIB = static_cast<IDirect3DIndexBuffer9*>(buffer->GetNativeHandle());
        m_nativeDevice->SetIndices(nativeIB);
    }

    void DX9Renderer::SetViewport(const Viewport& viewport)
    {
        D3DVIEWPORT9 vp;
        vp.X      = static_cast<DWORD>(viewport.X);
        vp.Y      = static_cast<DWORD>(viewport.Y);
        vp.Width  = static_cast<DWORD>(viewport.Width);
        vp.Height = static_cast<DWORD>(viewport.Height);
        vp.MinZ   = viewport.MinDepth;
        vp.MaxZ   = viewport.MaxDepth;

        m_nativeDevice->SetViewport(&vp);
    }

    void DX9Renderer::SetScissorRect(const RectI& rect)
    {
        RECT d3dRect = {rect.Left(), rect.Top(), rect.Right(), rect.Bottom()};
        m_nativeDevice->SetScissorRect(&d3dRect);
    }

    void DX9Renderer::SetConstantBuffer(EShaderStage stage, uint32 slot, IBuffer* buffer)
    {
        // TODO: 구현
    }

    void DX9Renderer::SetTexture(EShaderStage stage, uint32 slot, ITexture* texture)
    {
        if (texture)
        {
            IDirect3DTexture9* nativeTex = static_cast<IDirect3DTexture9*>(texture->GetNativeHandle());
            m_nativeDevice->SetTexture(slot, nativeTex);
        }
        else
        {
            m_nativeDevice->SetTexture(slot, nullptr);
        }
    }

    void* DX9Renderer::MapBuffer(IBuffer* buffer)
    {
        if (!buffer)
            return nullptr;

        void* data         = nullptr;
        auto* nativeHandle = buffer->GetNativeHandle();

        // TODO: 버퍼 타입별 분기 (DX9는 버퍼 타입에 따라 Lock 호출이 다름)
        return data;
    }

    void DX9Renderer::UnmapBuffer(IBuffer* buffer)
    {
        if (!buffer)
            return;

        // TODO: 버퍼 타입별 Unlock 분기
    }

    void DX9Renderer::UpdateBuffer(IBuffer* buffer, const void* data, uint32 size)
    {
        void* mapped = MapBuffer(buffer);
        if (mapped)
        {
            memcpy(mapped, data, size);
            UnmapBuffer(buffer);
        }
    }

    void DX9Renderer::Draw(uint32 vertexCount, uint32 startVertex)
    {
        uint32 primitiveCount = CalcPrimitiveCount(m_currentTopology, vertexCount);
        if (primitiveCount == 0)
            return;

        m_nativeDevice->DrawPrimitive(ToDX9PrimitiveType(m_currentTopology), startVertex, primitiveCount);
    }

    void DX9Renderer::DrawIndexed(uint32 indexCount, uint32 startIndex, int32 baseVertex)
    {
        uint32 primitiveCount = CalcPrimitiveCount(m_currentTopology, indexCount);
        if (primitiveCount == 0)
            return;

        uint32 numVertices = 0xFFFF;
        if (m_currentVertexBuffer)
        {
            numVertices = m_currentVertexBuffer->GetByteSize() / m_currentVertexBuffer->GetStride();
        }

        m_nativeDevice->DrawIndexedPrimitive(
            ToDX9PrimitiveType(m_currentTopology),
            baseVertex,    // BaseVertexIndex: 인덱스에 더할 오프셋. 여러 메시를 하나의 정점 버퍼에 합칠 때 사용. (0 = 없음)
            0,             // MinVertexIndex: 참조되는 최소 정점 인덱스.
            numVertices,   // NumVertices: 참조되는 정점 범위.
            startIndex,    // StartIndex: 인덱스 버퍼에서 읽기 시작하는 위치. 하나의 인덱스 버퍼에 여러 메시의 인덱스를 합칠 때 사용.
            primitiveCount // PrimitiveCount - 그릴 프리미티브 수
        );
    }

    void DX9Renderer::ClearRenderTarget(const Color& color)
    {
        // Color -> D3DCOLOR 변환
        D3DCOLOR backColor = D3DCOLOR_XRGB(
            static_cast<uint8>(color.R * 255),
            static_cast<uint8>(color.G * 255),
            static_cast<uint8>(color.B * 255));

        m_nativeDevice->Clear(0, nullptr, D3DCLEAR_TARGET, backColor, 1.0f, 0);
    }

    void DX9Renderer::ClearDepthStencil(float depth, uint8 stencil)
    {
        DWORD flags = D3DCLEAR_ZBUFFER;
        if (stencil != 0)
        {
            flags |= D3DCLEAR_STENCIL;
        }

        m_nativeDevice->Clear(0, nullptr, flags, 0, depth, stencil);
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
