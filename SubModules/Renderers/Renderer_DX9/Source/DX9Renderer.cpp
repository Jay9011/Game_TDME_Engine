#include "pch.h"
#include "Renderer_DX9/DX9Renderer.h"

#include <Core/Math/MathConstants.h>
#include <Core/Math/TVector2.h>
#include <Core/Math/TMatrix4x4.h>
#include <Core/Types/Color32.h>
#include <Core/Math/Detail/TMatrix4x4.Transform2D.h>
#include <Engine/RHI/Vertex/IVertexLayout.h>
#include <Engine/RHI/Vertex/VertexLayoutDesc.h>
#include <Engine/Renderer/Vertex2DTypes.h>

#include "Renderer_DX9/DX9Device.h"
#include "Renderer_DX9/DX9VertexLayout.h"
#include "Renderer_DX9/DX9TypeConversion.h"

//////////////////////////////////////////////////////////////
// Matrix4 와 D3DMATRIX 호환성 검증
//////////////////////////////////////////////////////////////
static_assert(sizeof(TDME::Matrix4) == sizeof(D3DMATRIX), "Matrix4 and D3DMATRIX must have the same size");
static_assert(sizeof(TDME::Matrix4) == sizeof(float) * 16, "Matrix4 must be 16 bytes (16 floats)");

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

        // NOTE: 2D 렌더링 세팅 임시 테스트용
        m_nativeDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
        m_nativeDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

        VertexLayoutDesc layoutDesc;
        layoutDesc
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::Color, EVertexFormat::Color);

        m_layoutPC = m_device->CreateVertexLayout(layoutDesc);

        return m_layoutPC != nullptr;
    } // bool DX9Renderer::Initialize(IWindow* window)

    void DX9Renderer::Shutdown()
    {
        m_layoutPC.reset(); // 레이아웃 초기화 (임시 테스트용)
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

    void DX9Renderer::SetWorldMatrix(const Matrix4& matrix)
    {
        m_nativeDevice->SetTransform(D3DTS_WORLD, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetViewMatrix(const Matrix4& matrix)
    {
        m_nativeDevice->SetTransform(D3DTS_VIEW, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetProjectionMatrix(const Matrix4& matrix)
    {
        m_nativeDevice->SetTransform(D3DTS_PROJECTION, reinterpret_cast<const D3DMATRIX*>(&matrix));
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

    void DX9Renderer::ApplyRenderSettings(const RenderSettings& settings)
    {
        // TODO: 구현
    }

    void DX9Renderer::SetVertexLayout(IVertexLayout* layout)
    {
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

        m_nativeDevice->SetTexture(0, nullptr);
        m_nativeDevice->DrawPrimitiveUP(ToDX9PrimitiveType(type), primitiveCount, vertices, stride);
    }

    //////////////////////////////////////////////////////////////
    // 저수준 프리미티브 렌더링
    //////////////////////////////////////////////////////////////

    void DX9Renderer::DrawTriangle(const Vector2& position, float width, float height, float rotation, const Color& color)
    {
        // 1. Color -> Color32 변환
        Color32 color32 = Color32::FromColor(color);

        // 2. 삼각형 로컬 좌표 생성 (중심 기준, 시계방향)
        float halfWidth  = width / 2;
        float halfHeight = height / 2;

        Vertex2DPC vertices[3] = {
            Vertex2DPC(0.0f, -halfHeight, color32),      // 상단 중앙
            Vertex2DPC(halfWidth, halfHeight, color32),  // 우하단
            Vertex2DPC(-halfWidth, halfHeight, color32), // 좌하단
        };

        // 3. World 행렬로 위치/회전 설정
        Matrix4 world = Rotation2D(rotation * Math::DegToRad) * Translation2D(position);
        SetWorldMatrix(world);

        // 4. 레이아웃 설정
        SetVertexLayout(m_layoutPC.get());

        // 5. 렌더링
        DrawPrimitives(EPrimitiveType::TriangleList, vertices, 3, sizeof(Vertex2DPC));
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
