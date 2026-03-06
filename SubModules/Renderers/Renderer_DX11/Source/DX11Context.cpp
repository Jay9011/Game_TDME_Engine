#include "pch.h"
#include "Renderer_DX11/DX11Context.h"

#include <Engine/RHI/Buffer/IBuffer.h>

#include "Renderer_DX11/DX11Device.h"
#include "Renderer_DX11/Pipeline/DX11PipelineState.h"

namespace TDME
{
    DX11Context::DX11Context(DX11Device* device, ID3D11DeviceContext* nativeContext)
        : m_device(device), m_context(nativeContext)
    {
    }

    void DX11Context::SetPipelineState(IPipelineState* pso)
    {
        if (!pso)
            return;

        DX11PipelineState* dx11Pso = static_cast<DX11PipelineState*>(pso);

        // Rasterizer State
        m_context->RSSetState(dx11Pso->RasterizerState.Get());

        // Blend State
        const float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};                          // TODO: BlendFactor 상수 색상 (Blend Factor: 블렌딩 연산에 사용되는 색상 값. 예를 들어, 0.0f, 0.0f, 0.0f, 0.0f는 검정/투명을 의미.)
        m_context->OMSetBlendState(dx11Pso->BlendState.Get(), blendFactor, 0xFFFFFFFF); // SampleMask: 모든 MSAA 샘플 활성화 (기본값) (MSAA: Multi-Sample Anti-Aliasing)

        // DepthStencil State
        m_context->OMSetDepthStencilState(dx11Pso->DepthStencilState.Get(), 0);

        // Input Layout
        m_context->IASetInputLayout(dx11Pso->InputLayout.Get());

        // Shaders
        m_context->VSSetShader(dx11Pso->VS, nullptr, 0);
        m_context->PSSetShader(dx11Pso->PS, nullptr, 0);

        // Topology
        m_context->IASetPrimitiveTopology(dx11Pso->Topology);
    }

    void DX11Context::SetVertexBuffer(uint32 slot, IBuffer* buffer)
    {
        if (!buffer)
            return;

        ID3D11Buffer* nativeVB = static_cast<ID3D11Buffer*>(buffer->GetNativeHandle());
        UINT          stride   = buffer->GetStride();
        UINT          offset   = 0;
        m_context->IASetVertexBuffers(slot, 1, &nativeVB, &stride, &offset);
    }

    void DX11Context::SetIndexBuffer(IBuffer* buffer)
    {
        if (!buffer)
            return;

        ID3D11Buffer* nativeIB = static_cast<ID3D11Buffer*>(buffer->GetNativeHandle());
        // Stride로 인덱스 포맷 결정: 2byte(uint16) = R16_UINT, 4byte(uint32) = R32_UINT
        DXGI_FORMAT format = (buffer->GetStride() == 2) ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT;
        m_context->IASetIndexBuffer(nativeIB, format, 0);
    }

    void DX11Context::SetViewport(const Viewport& viewport)
    {
        static_assert(sizeof(Viewport) == sizeof(D3D11_VIEWPORT), "Viewport size mismatch");
        m_context->RSSetViewports(1, reinterpret_cast<const D3D11_VIEWPORT*>(&viewport));
    }

    void DX11Context::SetScissorRect(const RectI& rect)
    {
        D3D11_RECT d3dRect = {rect.Left(), rect.Top(), rect.Right(), rect.Bottom()};
        m_context->RSSetScissorRects(1, &d3dRect);
    }

    void DX11Context::SetConstantBuffer(EShaderStage stage, uint32 slot, IBuffer* buffer)
    {
        ID3D11Buffer* nativeCB = buffer ? static_cast<ID3D11Buffer*>(buffer->GetNativeHandle()) : nullptr;

        switch (stage)
        {
        case EShaderStage::Vertex:
            m_context->VSSetConstantBuffers(slot, 1, &nativeCB);
            break;
        case EShaderStage::Pixel:
            m_context->PSSetConstantBuffers(slot, 1, &nativeCB);
            break;
        }
    }

    void DX11Context::SetTexture(EShaderStage stage, uint32 slot, ITexture* texture)
    {
        // TODO: 구현
    }

    void* DX11Context::MapBuffer(IBuffer* buffer)
    {
        if (!buffer)
            return nullptr;

        ID3D11Resource*          resource = static_cast<ID3D11Resource*>(buffer->GetNativeHandle());
        D3D11_MAPPED_SUBRESOURCE mapped   = {};

        HRESULT hr = m_context->Map(resource, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
        // D3D11_MAP_WRITE_DISCARD: 버퍼를 쓰기 전용으로 매핑. 이전 데이터는 버림.
        // GPU가 이전 데이터를 아직 사용 중이면, 드라이버가 자동으로 새 메모리를 할당하여 CPU-GPU 동기화 없이 데이터를 전송할 수 있음. (Dynamic Buffer 전용)
        if (FAILED(hr))
            return nullptr;

        return mapped.pData;
    }

    void DX11Context::UnmapBuffer(IBuffer* buffer)
    {
        if (!buffer)
            return;

        ID3D11Resource* resource = static_cast<ID3D11Resource*>(buffer->GetNativeHandle());
        m_context->Unmap(resource, 0);
    }

    void DX11Context::UpdateBuffer(IBuffer* buffer, const void* data, uint32 size)
    {
        void* mapped = MapBuffer(buffer);
        if (mapped)
        {
            memcpy(mapped, data, size);
            UnmapBuffer(buffer);
        }
    }

    void DX11Context::Draw(uint32 vertexCount, uint32 startVertex)
    {
        m_context->Draw(vertexCount, startVertex);
    }

    void DX11Context::DrawIndexed(uint32 indexCount, uint32 startIndex, int32 baseVertex)
    {
        m_context->DrawIndexed(indexCount, startIndex, baseVertex);
    }

    void DX11Context::ClearRenderTarget(const Color& color)
    {
        ID3D11RenderTargetView* rtv = m_device->GetRenderTargetView();
        if (rtv)
        {
            const float clearColor[4] = {color.R, color.G, color.B, color.A};
            m_context->ClearRenderTargetView(rtv, clearColor);
        }
    }

    void DX11Context::ClearDepthStencil(float depth, uint8 stencil)
    {
        ID3D11DepthStencilView* dsv = m_device->GetDepthStencilView();
        if (dsv)
        {
            UINT flags = D3D11_CLEAR_DEPTH;
            if (stencil != 0)
            {
                flags |= D3D11_CLEAR_STENCIL;
            }
            m_context->ClearDepthStencilView(dsv, flags, depth, stencil);
        }
    }
} // namespace TDME