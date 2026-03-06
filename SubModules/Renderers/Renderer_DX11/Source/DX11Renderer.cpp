#include "pch.h"
#include "Renderer_DX11/DX11Renderer.h"

#include <Engine/RHI/IRHIDevice.h>
#include <Engine/RHI/IRHIContext.h>
#include <Engine/RHI/Buffer/IBuffer.h>
#include <Engine/RHI/Buffer/BufferDesc.h>
#include <Engine/RHI/Shader/EShaderStage.h>

namespace TDME
{
    DX11Renderer::DX11Renderer()  = default;
    DX11Renderer::~DX11Renderer() = default;

    bool DX11Renderer::Initialize(IWindow* window)
    {
        if (!m_device || !m_context)
            return false;

        // Transform Constant Buffer 생성
        BufferDesc cbDesc = {};
        cbDesc.Type       = EBufferType::Constant;
        cbDesc.Usage      = EBufferUsage::Dynamic;
        cbDesc.ByteSize   = sizeof(TransformCB);
        cbDesc.Stride     = sizeof(TransformCB);

        m_transformBuffer = m_device->CreateBuffer(cbDesc, nullptr);

        if (!m_transformBuffer)
            return false;

        m_transformData.World      = Matrix::Identity();
        m_transformData.View       = Matrix::Identity();
        m_transformData.Projection = Matrix::Identity();

        return true;
    }

    void DX11Renderer::Shutdown()
    {
        m_transformBuffer.reset();
        m_context = nullptr;
        m_device  = nullptr;
    }

    void DX11Renderer::BeginFrame(const Color& clearColor)
    {
        m_context->ClearRenderTarget(clearColor);
        m_context->ClearDepthStencil(1.0f, 0);
    }

    void DX11Renderer::EndFrame()
    {
    }

    void DX11Renderer::SetWorldMatrix(const Matrix& matrix)
    {
        m_transformData.World = matrix;
        UpdateTransformCB();
    }

    void DX11Renderer::SetViewMatrix(const Matrix& matrix)
    {
        m_transformData.View = matrix;
        UpdateTransformCB();
    }

    void DX11Renderer::SetProjectionMatrix(const Matrix& matrix)
    {
        m_transformData.Projection = matrix;
        UpdateTransformCB();
    }

    void DX11Renderer::ApplyRenderSettings(const RenderSettings& settings)
    {
        // TODO: 구현
    }

    void DX11Renderer::DrawSprite(const SpriteDesc& sprite)
    {
        // TODO: 구현
    }

    void DX11Renderer::DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride)
    {
        // TODO: 구현
    }

    void DX11Renderer::UpdateTransformCB()
    {
        if (m_transformBuffer && m_context)
        {
            m_context->UpdateBuffer(m_transformBuffer.get(), &m_transformData, sizeof(TransformCB));
            m_context->SetConstantBuffer(EShaderStage::Vertex, 0, m_transformBuffer.get());
        }
    }
} // namespace TDME