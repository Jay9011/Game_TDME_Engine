#include "pch.h"
#include "Renderer_DX9/DX9Renderer.h"

#include <Core/Math/TVector2.h>
#include <Core/Types/Color32.h>
#include <Core/Render/Vertex2DTypes.h>

#include <algorithm>
#include <cmath>
#include <d3d9types.h>

namespace TDME
{
    // 임시 타입: D3DFVF_XYZRHW | D3DFVF_DIFFUSE 와 매칭
    struct Vertex2DRHW
    {
        float   X, Y, Z, RHW; // 화면 좌표 (이미 변환됨)
        Color32 Color;        // ARGB 포맷
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

        return SUCCEEDED(hr);
    } // bool DX9Renderer::Initialize(IWindow* window)

    void DX9Renderer::Shutdown()
    {
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

        Vector2 local[3] = {
            Vector2(0.0f, -halfHeight),      // 상단 중앙
            Vector2(halfWidth, halfHeight),  // 우하단
            Vector2(-halfWidth, halfHeight), // 좌하단
        };

        // 3. 회전 변환 + RHW 정점 생성
        float rad  = rotation * Math::DegToRad;
        float cosR = std::cos(rad);
        float sinR = std::sin(rad);

        Vertex2DRHW vertices[3];
        for (int i = 0; i < 3; i++)
        {
            // 회전 변환
            float rx = local[i].X * cosR - local[i].Y * sinR;
            float ry = local[i].X * sinR + local[i].Y * cosR;

            // 화면 좌표 (Pre-transformed)
            vertices[i].X     = position.X + rx;
            vertices[i].Y     = position.Y + ry;
            vertices[i].Z     = 0.0f;
            vertices[i].RHW   = 1.0f;
            vertices[i].Color = color32;
        }

        // 4. 렌더링 상태 설정
        m_device->SetFVF(FVF_VERTEX2D);
        m_device->SetTexture(0, nullptr);

        // 5. 렌더링
        m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, vertices, sizeof(Vertex2DRHW));
    }

} // namespace TDME
