#include "pch.h"
#include "Renderer_DX11/DX11Device.h"

#include <Engine/ApplicationCore/IWindow.h>

#include "Renderer_DX11/DX11TypeConversion.h"
#include "Renderer_DX11/Pipeline/DX11PipelineState.h"

namespace TDME
{
    DX11Device::DX11Device() = default;
    DX11Device::~DX11Device()
    {
        Shutdown();
    }

    //////////////////////////////////////////////////////////////
    // IRHIDevice
    //////////////////////////////////////////////////////////////

    bool DX11Device::Initialize(IWindow* window, const SwapChainDesc& swapChainDesc)
    {
        m_vsync = swapChainDesc.VSync;

        // 1. SwapChain 설정
        DXGI_SWAP_CHAIN_DESC scDesc = {};
        scDesc.BufferCount          = swapChainDesc.BackBufferCount;
        scDesc.BufferDesc.Width     = window->GetWidth();
        scDesc.BufferDesc.Height    = window->GetHeight();
        scDesc.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM; // UNORM: 0~255 범위의 정수 값을 0.0~1.0 범위의 부동소수점 값으로 변환.
        scDesc.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scDesc.OutputWindow         = static_cast<HWND>(window->GetNativeHandle());
        scDesc.SampleDesc.Count     = 1;
        scDesc.Windowed             = TRUE;
        scDesc.SwapEffect           = ToDX11SwapEffect(swapChainDesc.SwapEffect);

        // 2. Device + SwapChain + Immediate Context 생성
        UINT createFlags = 0;
#ifdef _DEBUG
        createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        D3D_FEATURE_LEVEL featureLevel;

        HRESULT hr = D3D11CreateDeviceAndSwapChain(
            nullptr,                    // 사용할 그래픽 카드 어댑터 (nullptr: 기본 어댑터 사용)
            D3D_DRIVER_TYPE_HARDWARE,   // 사용할 드라이버 타입 (D3D_DRIVER_TYPE_HARDWARE: 하드웨어 가속 드라이버 사용)
            nullptr,                    // 사용할 소프트웨어 레스터라이저 디바이스 (nullptr: 사용하지 않음)
            createFlags,                // 생성 플래그
            nullptr,                    // Feature Level 배열 (nullptr: 기본 Feature Level 사용)
            0,                          // Feature Level 개수
            D3D11_SDK_VERSION,          // SDK 버전
            &scDesc,                    // SwapChain 설정
            m_swapChain.GetAddressOf(), // 생성된 SwapChain 객체의 포인터를 저장할 포인터
            m_device.GetAddressOf(),    // 생성된 Device 객체의 포인터를 저장할 포인터
            &featureLevel,              // 실제 선택된 Feature Level
            m_context.GetAddressOf()    // 생성된 Immediate Context 객체의 포인터를 저장할 포인터
        );

        if (FAILED(hr))
            return false;

        // 3. Render Target View + Depth Stencil View 생성
        if (!CreateRenderTargetAndDepthStencil(window->GetWidth(), window->GetHeight()))
        {
            return false;
        }

        return true;
    } // bool DX11Device::Initialize(IWindow* window, const SwapChainDesc& swapChainDesc)

    void DX11Device::Shutdown()
    {
        if (m_context)
            m_context->ClearState();

        m_depthStencilView.Reset();
        m_depthStencilBuffer.Reset();
        m_renderTargetView.Reset();
        m_swapChain.Reset();
        m_context.Reset();
        m_device.Reset();
    }

    IRHIContext* DX11Device::GetImmediateContext()
    {
        // TODO: 구현 필요
        return nullptr;
    }

    void DX11Device::Present()
    {
        if (m_swapChain)
        {
            m_swapChain->Present(m_vsync ? 1 : 0, 0); // SyncInterval: 0 = 즉시, 1 = 수직 동기화
        }
    }

    bool DX11Device::ResizeSwapChain(uint32 width, uint32 height)
    {
        if (!m_swapChain)
            return false;

        // 1. 기존 View 해제 (SwapChain 크기 변경 전 기존 View 해제 필요)
        m_context->OMSetRenderTargets(0, nullptr, nullptr);
        m_renderTargetView.Reset();
        m_depthStencilView.Reset();
        m_depthStencilBuffer.Reset();

        // 2. 버퍼 크기 변경
        HRESULT hr = m_swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
        if (FAILED(hr))
            return false;

        // 3. Render Target View + Depth Stencil View 생성
        return CreateRenderTargetAndDepthStencil(width, height);
    }

    std::unique_ptr<IPipelineState> DX11Device::CreatePipelineState(const PipelineStateDesc& desc)
    {
        std::unique_ptr<DX11PipelineState> pso = std::make_unique<DX11PipelineState>();

        // 1. Rasterizer State 생성
        D3D11_RASTERIZER_DESC rsDesc = {};
        rsDesc.FillMode              = ToDX11FillMode(desc.RasterizerState.FillMode);
        rsDesc.CullMode              = ToDX11CullMode(desc.RasterizerState.CullMode);
        rsDesc.FrontCounterClockwise = desc.RasterizerState.FrontCounterClockwise;
        rsDesc.DepthClipEnable       = desc.RasterizerState.DepthClipEnable;
        rsDesc.ScissorEnable         = desc.RasterizerState.ScissorEnable;

        HRESULT hr = m_device->CreateRasterizerState(&rsDesc, pso->RasterizerState.GetAddressOf());

        if (FAILED(hr))
            return nullptr;

        // 2. Blend State 생성
        D3D11_BLEND_DESC bsDesc                      = {};
        bsDesc.RenderTarget[0].BlendEnable           = desc.BlendState.BlendEnable;
        bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

        if (desc.BlendState.BlendEnable)
        {
            bsDesc.RenderTarget[0].SrcBlend       = ToDX11BlendFactor(desc.BlendState.SrcBlend);
            bsDesc.RenderTarget[0].DestBlend      = ToDX11BlendFactor(desc.BlendState.DestBlend);
            bsDesc.RenderTarget[0].BlendOp        = ToDX11BlendOp(desc.BlendState.BlendOp);
            bsDesc.RenderTarget[0].SrcBlendAlpha  = ToDX11BlendFactor(desc.BlendState.SrcBlendAlpha);
            bsDesc.RenderTarget[0].DestBlendAlpha = ToDX11BlendFactor(desc.BlendState.DestBlendAlpha);
            bsDesc.RenderTarget[0].BlendOpAlpha   = ToDX11BlendOp(desc.BlendState.BlendOpAlpha);
        }

        hr = m_device->CreateBlendState(&bsDesc, pso->BlendState.GetAddressOf());
        if (FAILED(hr))
            return nullptr;

        // 3. DepthStencil State 생성
        D3D11_DEPTH_STENCIL_DESC dsDesc = {};
        dsDesc.DepthEnable              = desc.DepthStencilState.DepthEnable;
        dsDesc.DepthWriteMask           = desc.DepthStencilState.DepthWriteEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
        dsDesc.DepthFunc                = ToDX11ComparisonFunc(desc.DepthStencilState.DepthFunc);

        hr = m_device->CreateDepthStencilState(&dsDesc, pso->DepthStencilState.GetAddressOf());
        if (FAILED(hr))
            return nullptr;

        // 4. Topology 변환
        pso->Topology = ToDX11Topology(desc.TopologyType);

        // TODO: 5. Input Layout + Shader 구현

        return pso;
    } // std::unique_ptr<IPipelineState> DX11Device::CreatePipelineState(const PipelineStateDesc& desc)

    std::unique_ptr<IRasterizerState> DX11Device::CreateRasterizerState(const RasterizerStateDesc& desc)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<IBlendState> DX11Device::CreateBlendState(const BlendStateDesc& desc)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<IDepthStencilState> DX11Device::CreateDepthStencilState(const DepthStencilStateDesc& desc)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<IVertexShader> DX11Device::CreateVertexShader(const void* byteCode, uint32 byteCodeSize)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<IPixelShader> DX11Device::CreatePixelShader(const void* byteCode, uint32 byteCodeSize)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<IInputLayout> DX11Device::CreateInputLayout(const InputLayoutDesc& desc)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<IBuffer> DX11Device::CreateBuffer(const BufferDesc& desc, const void* initialData)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    std::unique_ptr<ITexture> DX11Device::CreateTexture(const TextureDesc& desc, const void* initialData)
    {
        // TODO: 구현 필요
        return nullptr;
    }

    //////////////////////////////////////////////////////////////
    // Private Methods
    //////////////////////////////////////////////////////////////

    bool DX11Device::CreateRenderTargetAndDepthStencil(uint32 width, uint32 height)
    {
        // 1. Back Buffer -> Render Target View 생성
        ComPtr<ID3D11Texture2D> backBuffer;

        HRESULT hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
        if (FAILED(hr))
            return false;

        hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.GetAddressOf());
        if (FAILED(hr))
            return false;

        // 2. Depth Stencil Texture 생성
        D3D11_TEXTURE2D_DESC depthDesc = {};
        depthDesc.Width                = width;
        depthDesc.Height               = height;
        depthDesc.MipLevels            = 1;
        depthDesc.ArraySize            = 1;
        depthDesc.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT; // 24비트 깊이 + 8비트 스텐실
        depthDesc.SampleDesc.Count     = 1;
        depthDesc.Usage                = D3D11_USAGE_DEFAULT;
        depthDesc.BindFlags            = D3D11_BIND_DEPTH_STENCIL;

        hr = m_device->CreateTexture2D(&depthDesc, nullptr, m_depthStencilBuffer.GetAddressOf());
        if (FAILED(hr))
            return false;

        // 3. Depth Stencil View 생성
        hr = m_device->CreateDepthStencilView(m_depthStencilBuffer.Get(), nullptr, m_depthStencilView.GetAddressOf());
        if (FAILED(hr))
            return false;

        // 4. Output Merger에 바인딩
        m_context->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

        // 5. Viewport 설정
        D3D11_VIEWPORT viewport = {};
        viewport.Width          = static_cast<float>(width);
        viewport.Height         = static_cast<float>(height);
        viewport.MinDepth       = 0.0f;
        viewport.MaxDepth       = 1.0f;
        m_context->RSSetViewports(1, &viewport);

        return true;
    } // bool DX11Device::CreateRenderTargetAndDepthStencil(uint32 width, uint32 height)

} // namespace TDME