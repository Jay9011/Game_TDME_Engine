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

#include "Renderer_DX9/DX9VertexLayout.h"
#include "Renderer_DX9/DX9TypeConversion.h"

//////////////////////////////////////////////////////////////
// Matrix4 와 D3DMATRIX 호환성 검증
//////////////////////////////////////////////////////////////
static_assert(sizeof(TDME::Matrix4) == sizeof(D3DMATRIX), "Matrix4 and D3DMATRIX must have the same size");
static_assert(sizeof(TDME::Matrix4) == sizeof(float) * 16, "Matrix4 must be 16 bytes (16 floats)");

namespace TDME
{
    // 임시 타입: D3DFVF_XYZRHW | D3DFVF_DIFFUSE 와 매칭
    struct Vertex2DRHW
    {
        float   X = .0f, Y = .0f, Z = .0f, RHW = .0f; // 화면 좌표 (이미 변환됨)
        Color32 Color = Color32();                    // ARGB 포맷
    };

    DX9Renderer::DX9Renderer() : m_d3d(nullptr), m_device(nullptr)
    {
    }

    DX9Renderer::~DX9Renderer()
    {
    }

    bool DX9Renderer::Initialize(IWindow* window)
    {
        // 1. Direct3D9 인스턴스 생성 (열거(Enumeration) 단계)
        m_d3d.Attach(Direct3DCreate9(D3D_SDK_VERSION)); // Attach: 기존 객체를 대체하고 소유권 이전. (런타임 버전 검증용)
        if (!m_d3d)
        {
            return false;
        }

        // 2. Present Parameters 설정 (화면에 그림을 어떻게 표시할 것인가를 설정하는 구조체, Swap Chain 을 어떻게 구성할지 설정하는 구조체)
        D3DPRESENT_PARAMETERS d3dParam = {};

        d3dParam.Windowed               = true;
        d3dParam.SwapEffect             = D3DSWAPEFFECT_DISCARD; // D3DSWAPEFFECT_DISCARD: 백 버퍼의 내용을 프론트에 복사 후, 백 버퍼의 내용은 버림. D3DSWAPEFFECT_FLIP: 진짜 포인터 교체
        d3dParam.BackBufferFormat       = D3DFMT_UNKNOWN;        // D3DFMT_UNKNOWN: 윈도우 모드에서 현재 데스크톱과 같은 포멧을 사용하라. (전체화면 모드에서는 명시적으로 포멧을 지정해야 함)
        d3dParam.BackBufferCount        = 1;                     // 백 버퍼의 개수.
        d3dParam.EnableAutoDepthStencil = true;                  // 깊이 버퍼를 자동으로 생성할지 여부.
        d3dParam.AutoDepthStencilFormat = D3DFMT_D24S8;          // D3DFMT_D24S8: 24비트 깊이 + 8비트 스텐실
        d3dParam.hDeviceWindow          = static_cast<HWND>(window->GetNativeHandle());

        /* ============================================================
        d3dParam.BackBufferWidth  = 1280;   // 렌더링 해상도. 0인 경우 윈도우 크기를 따라가지만, 게임에서는 보통 명시적으로 지정.
        d3dParam.BackBufferHeight = 720;    // 명시적으로 지정하면 윈도우 크기와 렌더링 해상도를 독립적으로 관리할 수 있어서, 저해상도로 렌더링 후 업스케일링하는 등의 최적화가 가능해짐.

        d3dParam.PresentationInterval = D3DPRESENT_INTERVAL_ONE;   // VSync(수직 동기화) 설정. D3DPRESENT_INTERVAL_ONE: 모니터 주사율에 맞춰 화면을 갱신하여 티어링을 방지. D3DPRESENT_INTERVAL_IMMEDIATE: VSync를 끄고 가능한 빨리 화면을 갱신합니다.

        d3dParam.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;    // 멀티 샘플링(안티앨리어싱) 설정. D3DMULTISAMPLE_NONE: 멀티 샘플링 비활성화. D3DMULTISAMPLE_4_SAMPLES: 4x 멀티 샘플링.
        d3dParam.MultiSampleQuality = 0;                         // 멀티 샘플링 품질. 0이면 최고 품질.

        d3dParam.FullScreen_RefreshRateInHz = 60;    // 전체화면 모드에서 사용할 주사율. 0이면 모니터 기본값 사용.
        ============================================================= */

        // 3. Device 생성
        HRESULT hr = m_d3d->CreateDevice(        // HRESULT: 성공 여부와 실패 이유를 담은 32비트 정수. 'SUCCEEDED' 매크로 또는 'FAILED' 매크로로 결과 검증 가능.
            D3DADAPTER_DEFAULT,                  // 어떤 GPU를 사용할지
            D3DDEVTYPE_HAL,                      // 하드웨어 가속 디바이스 사용
            d3dParam.hDeviceWindow,              // 렌더링 대상 윈도우
            D3DCREATE_SOFTWARE_VERTEXPROCESSING, // 버텍스 처리 방식
            &d3dParam,                           // Present Parameters
            m_device.GetAddressOf());            // [출력] 생성된 디바이스 (GetAddressOf(): 내부 포인터 반환)

        if (FAILED(hr))
        {
            return false;
        }

        // NOTE: 2D 렌더링 세팅 임시 테스트용
        m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
        m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

        VertexLayoutDesc layoutDesc;
        layoutDesc
            .Add(EVertexSemantic::Position, EVertexFormat::Float3)
            .Add(EVertexSemantic::Color, EVertexFormat::Color);

        m_layoutPC = std::make_unique<DX9VertexLayout>(m_device.Get(), layoutDesc);

        return true;
    } // bool DX9Renderer::Initialize(IWindow* window)

    void DX9Renderer::Shutdown()
    {
        m_layoutPC.reset(); // 레이아웃 초기화 (임시 테스트용)
        m_device.Reset();
        m_d3d.Reset();
    }

    void DX9Renderer::BeginFrame(const Color& clearColor)
    {
        // Color -> D3DCOLOR 변환
        D3DCOLOR backColor = D3DCOLOR_XRGB(
            static_cast<uint8>(clearColor.R * 255),
            static_cast<uint8>(clearColor.G * 255),
            static_cast<uint8>(clearColor.B * 255));

        m_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
        m_device->BeginScene();
    }

    void DX9Renderer::EndFrame()
    {
        m_device->EndScene();
        m_device->Present(nullptr, nullptr, nullptr, nullptr);
    }

    void DX9Renderer::SetWorldMatrix(const Matrix4& matrix)
    {
        m_device->SetTransform(D3DTS_WORLD, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetViewMatrix(const Matrix4& matrix)
    {
        m_device->SetTransform(D3DTS_VIEW, reinterpret_cast<const D3DMATRIX*>(&matrix));
    }

    void DX9Renderer::SetProjectionMatrix(const Matrix4& matrix)
    {
        m_device->SetTransform(D3DTS_PROJECTION, reinterpret_cast<const D3DMATRIX*>(&matrix));
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
            m_device->SetVertexDeclaration(dx9Layout->GetNativeDeclaration());
        }
        else
        {
            m_device->SetVertexDeclaration(nullptr);
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

        m_device->SetTexture(0, nullptr);
        m_device->DrawPrimitiveUP(ToDX9PrimitiveType(type), primitiveCount, vertices, stride);
    }

    //////////////////////////////////////////////////////////////
    // 2D 렌더링 관련 메서드
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
} // namespace TDME
