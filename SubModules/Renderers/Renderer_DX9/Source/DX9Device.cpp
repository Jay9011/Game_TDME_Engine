#include "pch.h"
#include "Renderer_DX9/DX9Device.h"

#include <Engine/RHI/SwapChain/SwapChainDesc.h>
#include <Engine/RHI/Vertex/VertexLayoutDesc.h>

#include "Renderer_DX9/Buffer/DX9Buffer.h"
#include "Renderer_DX9/State/DX9RasterizerState.h"
#include "Renderer_DX9/State/DX9BlendState.h"
#include "Renderer_DX9/State/DX9DepthStencilState.h"
#include "Renderer_DX9/Texture/DX9Texture.h"
#include "Renderer_DX9/Vertex/DX9VertexLayout.h"
#include <memory>

namespace TDME
{
    DX9Device::DX9Device() : m_d3d(nullptr), m_device(nullptr)
    {
    }

    DX9Device::~DX9Device()
    {
        Shutdown();
    }

    bool DX9Device::Initialize(IWindow* window, const SwapChainDesc& swapChainDesc)
    {
        // 1. Direct3D9 인스턴스 생성 (열거(Enumeration) 단계)
        m_d3d.Attach(Direct3DCreate9(D3D_SDK_VERSION)); // Attach: 기존 객체를 대체하고 소유권 이전. (런타임 버전 검증용)
        if (!m_d3d)
        {
            return false;
        }

        // 2. Present Parameters 설정 (화면에 그림을 어떻게 표시할 것인가를 설정하는 구조체, Swap Chain 을 어떻게 구성할지 설정하는 구조체)
        D3DPRESENT_PARAMETERS d3dParam  = {};
        d3dParam.Windowed               = true;
        d3dParam.SwapEffect             = D3DSWAPEFFECT_DISCARD;         // D3DSWAPEFFECT_DISCARD: 백 버퍼의 내용을 프론트에 복사 후, 백 버퍼의 내용은 버림. D3DSWAPEFFECT_FLIP: 진짜 포인터 교체
        d3dParam.BackBufferFormat       = D3DFMT_UNKNOWN;                // D3DFMT_UNKNOWN: 윈도우 모드에서 현재 데스크톱과 같은 포멧을 사용하라. (전체화면 모드에서는 명시적으로 포멧을 지정해야 함)
        d3dParam.BackBufferCount        = swapChainDesc.BackBufferCount; // 백 버퍼의 개수.
        d3dParam.EnableAutoDepthStencil = true;                          // 깊이 버퍼를 자동으로 생성할지 여부.
        d3dParam.AutoDepthStencilFormat = D3DFMT_D24S8;                  // D3DFMT_D24S8: 24비트 깊이 + 8비트 스텐실
        d3dParam.hDeviceWindow          = static_cast<HWND>(window->GetNativeHandle());

        // VSync 설정
        d3dParam.PresentationInterval = swapChainDesc.VSync ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;

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
    } // bool DX9Device::Initialize(IWindow* window, const SwapChainDesc& swapChainDesc)

    void DX9Device::Shutdown()
    {
        m_device.Reset();
        m_d3d.Reset();
    }

    void DX9Device::Present()
    {
        if (m_device)
        {
            m_device->Present(nullptr, nullptr, nullptr, nullptr);
        }
    }

    bool DX9Device::ResizeSwapChain(uint32 width, uint32 height)
    {
        // TODO: 구현 필요
        return true;
    }

    std::unique_ptr<IRasterizerState> DX9Device::CreateRasterizerState(const RasterizerStateDesc& desc)
    {
        return std::make_unique<DX9RasterizerState>(desc);
    }

    std::unique_ptr<IBlendState> DX9Device::CreateBlendState(const BlendStateDesc& desc)
    {
        return std::make_unique<DX9BlendState>(desc);
    }

    std::unique_ptr<IDepthStencilState> DX9Device::CreateDepthStencilState(const DepthStencilStateDesc& desc)
    {
        return std::make_unique<DX9DepthStencilState>(desc);
    }

    std::unique_ptr<IVertexLayout> DX9Device::CreateVertexLayout(const VertexLayoutDesc& desc)
    {
        if (!m_device)
        {
            return nullptr;
        }
        return std::make_unique<DX9VertexLayout>(m_device.Get(), desc);
    }

    std::unique_ptr<IBuffer> DX9Device::CreateBuffer(const BufferDesc& desc, const void* initialData)
    {
        if (!m_device)
        {
            return nullptr;
        }

        std::unique_ptr<DX9Buffer> buffer = std::make_unique<DX9Buffer>(m_device.Get(), desc, initialData);
        if (!buffer->IsValid())
        {
            return nullptr;
        }
        return buffer;
    }

    std::unique_ptr<ITexture> DX9Device::CreateTexture(const TextureDesc& desc, const void* initialData)
    {
        if (!m_device)
        {
            return nullptr;
        }

        std::unique_ptr<DX9Texture> texture = std::make_unique<DX9Texture>(m_device.Get(), desc, initialData);
        if (!texture->IsValid())
        {
            return nullptr;
        }

        return texture;
    }
} // namespace TDME