#include "pch.h"
#include "Engine/Renderer/Shape/Shape3DRenderer.h"

#include <Core/CoreTypes.h>
#include <Core/Math/MathConstants.h>
#include <Core/Math/TVector3.h>
#include <Core/Types/Color32.h>

#include "Engine/RHI/IRHIDevice.h"
#include "Engine/RHI/Vertex/EVertexFormat.h"
#include "Engine/RHI/Vertex/EVertexSemantic.h"
#include "Engine/RHI/Vertex/VertexLayoutDesc.h"
#include "Engine/Renderer/IRenderer.h"
#include "Engine/Renderer/EPrimitiveType.h"
#include "Engine/Renderer/Vertex2DTypes.h"

#include <cmath>
#include <vector>

namespace TDME
{
    Shape3DRenderer::Shape3DRenderer(IRenderer* renderer, IRHIDevice* device)
        : m_renderer(renderer), m_device(device)
    {
        VertexLayoutDesc layoutDesc;
        layoutDesc
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::Color, EVertexFormat::Color);

        m_colorLayout = m_device->CreateVertexLayout(layoutDesc);
    }

    void Shape3DRenderer::DrawSphere(const Matrix& worldMatrix, float radius, const Color& color, uint32 stacks, uint32 slices)
    {
        Color32 color32 = Color32::FromColor(color);

        std::vector<Vertex2DPC> vertices;
        vertices.reserve(stacks * slices * 6);

        for (uint32 i = 0; i < stacks; i++)
        {
            // 현재 stack과 다음 stack의 각도
            float phi0 = Math::Pi * static_cast<float>(i) / static_cast<float>(stacks);
            float phi1 = Math::Pi * static_cast<float>(i + 1) / static_cast<float>(stacks);

            float sinPhi0 = std::sin(phi0), sinPhi1 = std::sin(phi1);
            float cosPhi0 = std::cos(phi0), cosPhi1 = std::cos(phi1);

            for (uint32 j = 0; j < slices; j++)
            {
                // 현재 slice와 다음 slice의 각도
                float theta0 = Math::Pi2 * static_cast<float>(j) / static_cast<float>(slices);
                float theta1 = Math::Pi2 * static_cast<float>(j + 1) / static_cast<float>(slices);

                float sinTheta0 = std::sin(theta0), sinTheta1 = std::sin(theta1);
                float cosTheta0 = std::cos(theta0), cosTheta1 = std::cos(theta1);

                // 4개의 정점 (Quad)
                Vector3 v00(radius * sinPhi0 * cosTheta0, radius * cosPhi0, radius * sinPhi0 * sinTheta0); // 좌상 (i, j)
                Vector3 v01(radius * sinPhi0 * cosTheta1, radius * cosPhi0, radius * sinPhi0 * sinTheta1); // 우상 (i, j+1)
                Vector3 v10(radius * sinPhi1 * cosTheta0, radius * cosPhi1, radius * sinPhi1 * sinTheta0); // 좌하 (i+1, j)
                Vector3 v11(radius * sinPhi1 * cosTheta1, radius * cosPhi1, radius * sinPhi1 * sinTheta1); // 우하 (i+1, j+1)

                // Triangle 1: v00 -> v01 -> v10
                vertices.emplace_back(v00, color32);
                vertices.emplace_back(v01, color32);
                vertices.emplace_back(v10, color32);

                // Triangle 2: v01 -> v11 -> v10
                vertices.emplace_back(v01, color32);
                vertices.emplace_back(v11, color32);
                vertices.emplace_back(v10, color32);
            }
        }

        m_renderer->SetWorldMatrix(worldMatrix);
        m_renderer->SetVertexLayout(m_colorLayout.get());
        m_renderer->DrawPrimitives(EPrimitiveType::TriangleList, vertices.data(), static_cast<uint32>(vertices.size()), sizeof(Vertex2DPC));
    }
} // namespace TDME