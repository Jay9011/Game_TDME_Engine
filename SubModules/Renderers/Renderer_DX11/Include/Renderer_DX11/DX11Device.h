#pragma once

#include <Engine/RHI/IRHIDevice.h>

#include <wrl/client.h>
#include <d3d11.h>
#include <memory>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    class DX11Context;

    /**
     * @brief DX11 Device 클래스
     * @details ID3D11Device + IDXGISwapChain 래핑. 리소스 생성 및 SwapChain 관리.
     */
    class DX11Device : public IRHIDevice
    {
    public:
        DX11Device();
        ~DX11Device() override;

        //////////////////////////////////////////////////////////////
        // IRHIDevice
        //////////////////////////////////////////////////////////////

        /**
         * @brief RHI 디바이스 초기화
         * @param window 렌더링 대상 Window
         * @param swapChainDesc SwapChain 설정
         * @return true/false 성공 여부
         */
        bool Initialize(IWindow* window, const SwapChainDesc& swapChainDesc) override;

        /**
         * @brief RHI 디바이스 종료
         */
        void Shutdown() override;

        /**
         * @brief 즉시 실행 컨텍스트 반환
         * @return IRHIContext* 관찰용 포인터
         */
        [[nodiscard]] IRHIContext* GetImmediateContext() override;

        /**
         * @brief 화면에 렌더링 결과 표현
         */
        void Present() override;

        /**
         * @brief SwapChain 크기 변경 (윈도우 크기 변경 시 호출)
         * @param width 새로운 너비
         * @param height 새로운 높이
         * @return true/false 성공 여부
         */
        bool ResizeSwapChain(uint32 width, uint32 height) override;

        /**
         * @brief 파이프라인 상태 객체 생성
         * @param desc PSO 설정 구조체 (셰이더, InputLayout, 상태 객체, 토폴로지)
         * @return std::unique_ptr<IPipelineState> 생성된 PSO (소유권은 호출자)
         * @see TDME::IPipelineState
         * @see TDME::PipelineStateDesc
         */
        [[nodiscard]] std::unique_ptr<IPipelineState> CreatePipelineState(const PipelineStateDesc& desc) override;

        /**
         * @brief 래스터라이저 상태 객체 생성
         * @param desc 래스터라이저 상태 설정 구조체
         * @return std::unique_ptr<IRasterizerState> 생성된 래스터라이저 상태 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IRasterizerState
         * @see TDME::RasterizerStateDesc
         */
        [[nodiscard]] std::unique_ptr<IRasterizerState> CreateRasterizerState(const RasterizerStateDesc& desc) override;

        /**
         * @brief 블렌딩 상태 객체 생성
         * @param desc 블렌딩 상태 설정 구조체
         * @return std::unique_ptr<IBlendState> 생성된 블렌딩 상태 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IBlendState
         * @see TDME::BlendStateDesc
         */
        [[nodiscard]] std::unique_ptr<IBlendState> CreateBlendState(const BlendStateDesc& desc) override;

        /**
         * @brief 깊이/스텐실 상태 객체 생성
         * @param desc 깊이/스텐실 상태 설정 구조체
         * @return std::unique_ptr<IDepthStencilState> 생성된 깊이/스텐실 상태 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IDepthStencilState
         * @see TDME::DepthStencilStateDesc
         */
        [[nodiscard]] std::unique_ptr<IDepthStencilState> CreateDepthStencilState(const DepthStencilStateDesc& desc) override;

        /**
         * @brief Vertex 셰이더 생성
         * @param byteCode 컴파일된 셰이더 바이트코드
         * @param byteCodeSize 바이트코드 크기
         * @return std::unique_ptr<IVertexShader> 생성된 Vertex 셰이더 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IVertexShader
         */
        [[nodiscard]] std::unique_ptr<IVertexShader> CreateVertexShader(const void* byteCode, uint32 byteCodeSize) override;

        /**
         * @brief Pixel 셰이더 생성
         * @param byteCode 컴파일된 셰이더 바이트코드
         * @param byteCodeSize 바이트코드 크기
         * @return std::unique_ptr<IPixelShader> 생성된 Pixel 셰이더 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IPixelShader
         */
        [[nodiscard]] std::unique_ptr<IPixelShader> CreatePixelShader(const void* byteCode, uint32 byteCodeSize) override;

        /**
         * @brief Input Layout 생성
         * @param desc 정점 레이아웃 정보 구조체
         * @return std::unique_ptr<IInputLayout> 생성된 정점 레이아웃 포인터 (소유권은 호출자가 가져가야함)
         * @see TDME::IInputLayout
         * @see TDME::InputLayoutDesc
         */
        [[nodiscard]] std::unique_ptr<IInputLayout> CreateInputLayout(const InputLayoutDesc& desc) override;

        /**
         * @brief GPU 버퍼 객체 생성 (Vertex/Index)
         * @param desc 버퍼 설정 구조체 (타입, 용도, 크기 등)
         * @param initialData 초기 데이터 포인터 (nullptr이면 빈 버퍼 생성)
         * @return std::unique_ptr<IBuffer> 생성된 버퍼 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IBuffer
         * @see TDME::BufferDesc
         */
        [[nodiscard]] std::unique_ptr<IBuffer> CreateBuffer(const BufferDesc& desc, const void* initialData = nullptr) override;

        /**
         * @brief GPU 텍스처 객체 생성
         * @param desc 텍스처 설정 구조체 (크기, 포맷, 밉맵 등)
         * @param initialData 초기 픽셀 데이터 포인터 (nullptr이면 빈 텍스처 생성)
         * @return std::unique_ptr<ITexture> 생성된 텍스처 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::ITexture
         * @see TDME::TextureDesc
         */
        [[nodiscard]] std::unique_ptr<ITexture> CreateTexture(const TextureDesc& desc, const void* initialData = nullptr) override;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 네이티브 DX11 디바이스 반환
         * @return ID3D11Device* Native DX11 Device
         */
        ID3D11Device* GetNativeDevice() const { return m_device.Get(); }

        /**
         * @brief 네이티브 DX11 컨텍스트 반환
         * @return ID3D11DeviceContext* Native DX11 DeviceContext
         */
        ID3D11DeviceContext* GetNativeContext() const { return m_context.Get(); }

        /**
         * @brief Render Target View 반환
         * @return ID3D11RenderTargetView* Render Target View
         */
        ID3D11RenderTargetView* GetRenderTargetView() const { return m_renderTargetView.Get(); }

        /**
         * @brief Depth Stencil View 반환
         * @return ID3D11DepthStencilView* Depth Stencil View
         */
        ID3D11DepthStencilView* GetDepthStencilView() const { return m_depthStencilView.Get(); }

    private:
        /**
         * @brief Render Target + Depth Stencil 생성 헬퍼
         * @param width 너비
         * @param height 높이
         * @return true/false 성공 여부
         */
        bool CreateRenderTargetAndDepthStencil(uint32 width, uint32 height);

    private:
        ComPtr<ID3D11Device>        m_device;
        ComPtr<ID3D11DeviceContext> m_context;
        ComPtr<IDXGISwapChain>      m_swapChain;

        // Immediate Context (즉시 실행용)
        std::unique_ptr<DX11Context> m_dx11Context;

        // Render Target
        ComPtr<ID3D11RenderTargetView> m_renderTargetView;
        ComPtr<ID3D11DepthStencilView> m_depthStencilView;
        ComPtr<ID3D11Texture2D>        m_depthStencilBuffer;

        // VSync 설정
        bool m_vsync = false;
    };
} // namespace TDME