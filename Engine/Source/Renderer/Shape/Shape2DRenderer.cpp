#include "pch.h"
#include "Engine/Renderer/Shape/Shape2DRenderer.h"

#include <Core/CoreTypes.h>
#include <Core/Types/Color32.h>
#include <Core/Math/MathConstants.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/Transformations.h>
#include "Engine/RHI/IRHIDevice.h"
#include "Engine/RHI/Vertex/EVertexFormat.h"
#include "Engine/RHI/Vertex/EVertexSemantic.h"
#include "Engine/RHI/Vertex/VertexLayoutDesc.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Renderer/Vertex2DTypes.h"
#include "Engine/Renderer/EPrimitiveType.h"

#include <vector>

namespace TDME
{
    Shape2DRenderer::Shape2DRenderer(IRenderer* renderer, IRHIDevice* device)
        : m_renderer(renderer), m_device(device)
    {
        VertexLayoutDesc layoutDesc;
        layoutDesc
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::Color, EVertexFormat::Color);

        m_colorLayout = m_device->CreateVertexLayout(layoutDesc);
    }

    void Shape2DRenderer::DrawLine(const Vector2& start, const Vector2& end, const Color& color)
    {
        Color32 color32 = Color32::FromColor(color);

        Vertex2DPC vertices[2] = {
            Vertex2DPC(start.X, start.Y, color32),
            Vertex2DPC(end.X, end.Y, color32),
        };

        m_renderer->SetWorldMatrix(Matrix::IDENTITY);
        m_renderer->SetVertexLayout(m_colorLayout.get());
        m_renderer->DrawPrimitives(EPrimitiveType::LineList, vertices, 2, sizeof(Vertex2DPC));
    }

    void Shape2DRenderer::DrawTriangle(const Vector2& position, float width, float height, float rotation, const Color& color)
    {
        Color32 color32 = Color32::FromColor(color);

        float halfWidth  = width / 2;
        float halfHeight = height / 2;

        Vertex2DPC vertices[3] = {
            Vertex2DPC(0.0f, -halfHeight, color32),      // 상단 중앙
            Vertex2DPC(halfWidth, halfHeight, color32),  // 우하단
            Vertex2DPC(-halfWidth, halfHeight, color32), // 좌하단
        };

        Matrix4 world = Rotation2D(rotation * Math::DegToRad) * Translation2D(position);
        m_renderer->SetWorldMatrix(world);
        m_renderer->SetVertexLayout(m_colorLayout.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleList, vertices, 3, sizeof(Vertex2DPC));
    }

    void Shape2DRenderer::DrawRect(const Vector2& position, float width, float height, float rotation, const Color& color)
    {
        Color32 color32 = Color32::FromColor(color);

        float halfWidth  = width / 2;
        float halfHeight = height / 2;

        Vertex2DPC vertices[6] = {
            Vertex2DPC(-halfWidth, -halfHeight, color32), // 좌상단
            Vertex2DPC(halfWidth, -halfHeight, color32),  // 우상단
            Vertex2DPC(-halfWidth, halfHeight, color32),  // 좌하단

            Vertex2DPC(halfWidth, -halfHeight, color32), // 우상단
            Vertex2DPC(halfWidth, halfHeight, color32),  // 우하단
            Vertex2DPC(-halfWidth, halfHeight, color32), // 좌하단
        };

        Matrix4 world = Rotation2D(rotation * Math::DegToRad) * Translation2D(position);
        m_renderer->SetWorldMatrix(world);
        m_renderer->SetVertexLayout(m_colorLayout.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleList, vertices, 6, sizeof(Vertex2DPC));
    }

    void Shape2DRenderer::DrawCircle(const Vector2& position, float radius, const Color& color, uint32 segments)
    {
        Color32 color32 = Color32::FromColor(color);

        std::vector<Vertex2DPC> vertices;
        vertices.reserve(segments + 2);

        // 중심점
        vertices.emplace_back(0.0f, 0.0f, color32);

        // 원 각 점들
        float angleStep = Math::Pi2 / static_cast<float>(segments);
        for (size_t i = 0; i < segments; i++)
        {
            float angle = angleStep * i;
            float x     = radius * std::cos(angle);
            float y     = radius * std::sin(angle);
            vertices.emplace_back(x, y, color32);
        }

        m_renderer->SetWorldMatrix(Translation2D(position));
        m_renderer->SetVertexLayout(m_colorLayout.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleFan, vertices.data(), static_cast<uint32>(vertices.size()), sizeof(Vertex2DPC));
    }
} // namespace TDME