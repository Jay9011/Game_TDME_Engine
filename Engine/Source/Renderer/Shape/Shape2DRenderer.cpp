#include "pch.h"
#include "Engine/Renderer/Shape/Shape2DRenderer.h"

#include <Core/Types/Color32.h>
#include <Core/Math/TVector2.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Transformations.h>

#include "Engine/RHI/IRHIDevice.h"
#include "Engine/RHI/IRHIContext.h"
#include "Engine/RHI/Pipeline/PipelineStateDesc.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Renderer/VertexTypes.h"

namespace TDME
{
    Shape2DRenderer::Shape2DRenderer(IRenderer* renderer, IRHIContext* context, IRHIDevice* device)
        : m_renderer(renderer), m_context(context), m_device(device)
    {
        PipelineStateDesc psoDesc;
        psoDesc.InputLayout
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::Color, EVertexFormat::Color);

        m_colorPSO = m_device->CreatePipelineState(psoDesc);
    }

    void Shape2DRenderer::DrawLine(const Vector2& start, const Vector2& end, const Color& color)
    {
        DrawLine(Matrix::Identity(), start, end, color);
    }

    void Shape2DRenderer::DrawLine(const Matrix& worldMatrix, const Vector2& start, const Vector2& end, const Color& color)
    {
        Color32 color32 = Color32::FromColor(color);

        VertexPC vertices[2] = {
            VertexPC(start.X, start.Y, color32),
            VertexPC(end.X, end.Y, color32),
        };

        m_renderer->SetWorldMatrix(worldMatrix);
        m_context->SetPipelineState(m_colorPSO.get());
        m_renderer->DrawPrimitives(EPrimitiveType::LineList, vertices, 2, sizeof(VertexPC));
    }

    void Shape2DRenderer::DrawTriangle(const Vector2& position, float width, float height, float rotation, const Color& color)
    {
        Matrix world = RotationMatrix2D(rotation * Math::DegToRad) * TranslationMatrix2D(position);
        DrawTriangle(world, width, height, color);
    }

    void Shape2DRenderer::DrawTriangle(const Matrix& worldMatrix, float width, float height, const Color& color)
    {
        Color32 color32 = Color32::FromColor(color);

        float halfWidth  = width / 2;
        float halfHeight = height / 2;

        VertexPC vertices[3] = {
            VertexPC(0.0f, -halfHeight, color32),      // 상단 중앙
            VertexPC(halfWidth, halfHeight, color32),  // 우하단
            VertexPC(-halfWidth, halfHeight, color32), // 좌하단
        };

        m_renderer->SetWorldMatrix(worldMatrix);
        m_context->SetPipelineState(m_colorPSO.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleList, vertices, 3, sizeof(VertexPC));
    }

    void Shape2DRenderer::DrawRect(const Vector2& position, float width, float height, float rotation, const Color& color)
    {
        Matrix world = RotationMatrix2D(rotation * Math::DegToRad) * TranslationMatrix2D(position);
        DrawRect(world, width, height, color);
    }

    void Shape2DRenderer::DrawRect(const Matrix& worldMatrix, float width, float height, const Color& color)
    {
        Color32 color32 = Color32::FromColor(color);

        float halfWidth  = width / 2;
        float halfHeight = height / 2;

        VertexPC vertices[6] = {
            VertexPC(-halfWidth, -halfHeight, color32), // 좌상단
            VertexPC(halfWidth, -halfHeight, color32),  // 우상단
            VertexPC(-halfWidth, halfHeight, color32),  // 좌하단

            VertexPC(halfWidth, -halfHeight, color32), // 우상단
            VertexPC(halfWidth, halfHeight, color32),  // 우하단
            VertexPC(-halfWidth, halfHeight, color32), // 좌하단
        };

        m_renderer->SetWorldMatrix(worldMatrix);
        m_context->SetPipelineState(m_colorPSO.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleList, vertices, 6, sizeof(VertexPC));
    }

    void Shape2DRenderer::DrawCircle(const Vector2& position, float radius, const Color& color, uint32 segments)
    {
        DrawCircle(TranslationMatrix2D(position), radius, color, segments);
    }

    void Shape2DRenderer::DrawCircle(const Matrix& worldMatrix, float radius, const Color& color, uint32 segments)
    {
        Color32 color32 = Color32::FromColor(color);

        std::vector<VertexPC> vertices;
        vertices.reserve(segments + 2);

        // 중심점
        vertices.emplace_back(0.0f, 0.0f, color32);

        // 원 각 점들 (로컬 좌표)
        float angleStep = Math::Pi2 / static_cast<float>(segments);
        for (size_t i = 0; i <= segments; i++)
        {
            float angle = angleStep * i;
            float x     = radius * std::cos(angle);
            float y     = radius * std::sin(angle);
            vertices.emplace_back(x, y, color32);
        }

        m_renderer->SetWorldMatrix(worldMatrix);
        m_context->SetPipelineState(m_colorPSO.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleFan, vertices.data(), static_cast<uint32>(vertices.size()), sizeof(VertexPC));
    }
} // namespace TDME