#include "pch.h"
#include "Engine/Renderer/Shape/Shape3DRenderer.h"

#include <Core/CoreTypes.h>
#include <Core/Math/MathConstants.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/TVector3.h>
#include <Core/Math/Transformations.h>
#include <Core/Types/Color32.h>

#include "Engine/RHI/IRHIDevice.h"
#include "Engine/RHI/Buffer/BufferDesc.h"
#include "Engine/RHI/Buffer/EBufferUsage.h"
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
        // 1. Color Vertex 레이아웃
        VertexLayoutDesc colorDesc;
        colorDesc
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::Color, EVertexFormat::Color);

        m_colorLayout = m_device->CreateVertexLayout(colorDesc);

        // 2. TexCoord Vertex 레이아웃
        VertexLayoutDesc textureDesc;
        textureDesc
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::TexCoord, EVertexFormat::Float2);

        m_textureLayout = m_device->CreateVertexLayout(textureDesc);
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

    void Shape3DRenderer::DrawTexturedSphere(const Matrix& worldMatrix, float radius, ITexture* texture, uint32 stacks, uint32 slices)
    {
        BuildSphereBuffers(stacks, slices);

        if (!m_sphereVB || !m_sphereIB)
            return;

        // 단위 구 버퍼 + 스케일 행렬로 반지름 적용
        Matrix scaledWorld = Scale3D(radius, radius, radius) * worldMatrix;

        m_renderer->SetWorldMatrix(scaledWorld);
        m_renderer->SetVertexLayout(m_textureLayout.get());
        m_renderer->SetTexture(0, texture);
        m_renderer->DrawIndexedPrimitives(EPrimitiveType::TriangleList, m_sphereVB.get(), m_sphereIB.get(), m_indexCount);
        m_renderer->SetTexture(0, nullptr);
    }

    //////////////////////////////////////////////////////////////
    // Private Method
    //////////////////////////////////////////////////////////////

    void Shape3DRenderer::BuildSphereBuffers(uint32 stacks, uint32 slices)
    {
        // 캐시 히트: 같은 파라미터면 재생성 불필요 (재사용)
        if (m_sphereVB && m_sphereIB && m_cachedStacks == stacks && m_cachedSlices == slices)
            return;

        // 1. 정점 생성 (단위 구, radius = 1)
        const uint32            vertexCount = (stacks + 1) * (slices + 1);
        std::vector<Vertex2DPT> vertices;
        vertices.reserve(vertexCount);

        for (uint32 i = 0; i <= stacks; i++)
        {
            float phi    = Math::Pi * static_cast<float>(i) / static_cast<float>(stacks);
            float sinPhi = std::sin(phi);
            float cosPhi = std::cos(phi);

            for (uint32 j = 0; j <= slices; j++)
            {
                float theta    = Math::Pi2 * static_cast<float>(j) / static_cast<float>(slices);
                float sinTheta = std::sin(theta);
                float cosTheta = std::cos(theta);

                Vector3 position(sinPhi * cosTheta, cosPhi, sinPhi * sinTheta);
                Vector2 uv(
                    static_cast<float>(j) / static_cast<float>(slices), // U: 0->1 (경도)
                    static_cast<float>(i) / static_cast<float>(stacks)  // V: 0->1 (위도)
                );

                vertices.emplace_back(position, uv);
            }
        }

        // 2. 인덱스 생성
        m_indexCount = stacks * slices * 6;
        std::vector<uint16> indices;
        indices.reserve(m_indexCount);

        for (uint32 i = 0; i < stacks; i++)
        {
            for (uint32 j = 0; j < slices; j++)
            {
                uint16 topLeft     = static_cast<uint16>(i * (slices + 1) + j);
                uint16 topRight    = static_cast<uint16>(i * (slices + 1) + j + 1);
                uint16 bottomLeft  = static_cast<uint16>((i + 1) * (slices + 1) + j);
                uint16 bottomRight = static_cast<uint16>((i + 1) * (slices + 1) + j + 1);

                // 삼각형 1: topLeft -> topRight -> bottomLeft
                indices.push_back(topLeft);
                indices.push_back(topRight);
                indices.push_back(bottomLeft);

                // 삼각형 2: topRight -> bottomRight -> bottomLeft
                indices.push_back(topRight);
                indices.push_back(bottomRight);
                indices.push_back(bottomLeft);
            }
        }

        // 3. GPU 버퍼 생성
        BufferDesc vbDesc;
        vbDesc.Type     = EBufferType::Vertex;
        vbDesc.Usage    = EBufferUsage::Default;
        vbDesc.ByteSize = static_cast<uint32>(vertices.size() * sizeof(Vertex2DPT));
        vbDesc.Stride   = sizeof(Vertex2DPT);

        m_sphereVB = m_device->CreateBuffer(vbDesc, vertices.data());

        BufferDesc ibDesc;
        ibDesc.Type     = EBufferType::Index;
        ibDesc.Usage    = EBufferUsage::Default;
        ibDesc.ByteSize = static_cast<uint32>(indices.size() * sizeof(uint16));
        ibDesc.Stride   = sizeof(uint16);

        m_sphereIB = m_device->CreateBuffer(ibDesc, indices.data());

        m_cachedStacks = stacks;
        m_cachedSlices = slices;
    }
} // namespace TDME