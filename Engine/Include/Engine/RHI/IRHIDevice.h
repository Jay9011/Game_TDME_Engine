#pragma once

#include <Core/CoreTypes.h>

#include <memory>

namespace TDME
{
    class IWindow;
    class IRHIContext;
    class IBuffer;
    class IBlendState;
    class IDepthStencilState;
    class ITexture;
    class IInputLayout;
    class IPixelShader;
    class IPipelineState;
    class IRasterizerState;
    class IVertexShader;
    struct BufferDesc;
    struct BlendStateDesc;
    struct DepthStencilStateDesc;
    struct SwapChainDesc;
    struct TextureDesc;
    struct InputLayoutDesc;
    struct PipelineStateDesc;
    struct RasterizerStateDesc;

    /**
     * @brief RHI 디바이스 인터페이스
     * @details GPU 리소스 생성 및 SwapChain 관리
     */
    class IRHIDevice
    {
    public:
        virtual ~IRHIDevice() = default;

        /**
         * @brief RHI 디바이스 초기화
         * @param window 렌더링 대상 Window
         * @param swapChainDesc SwapChain 설정
         * @return true/false 성공 여부
         */
        virtual bool Initialize(IWindow* window, const SwapChainDesc& swapChainDesc) = 0;

        /**
         * @brief RHI 디바이스 종료
         */
        virtual void Shutdown() = 0;

        /**
         * @brief 즉시 실행 컨텍스트 반환
         * @return IRHIContext* 관찰용 포인터
         */
        [[nodiscard]] virtual IRHIContext* GetImmediateContext() = 0;

        //////////////////////////////////////////////////////////////
        // SwapChain
        //////////////////////////////////////////////////////////////

        /**
         * @brief 화면에 렌더링 결과 표현
         */
        virtual void Present() = 0;

        /**
         * @brief SwapChain 크기 변경 (윈도우 크기 변경 시 호출)
         * @param width 새로운 너비
         * @param height 새로운 높이
         * @return true/false 성공 여부
         */
        virtual bool ResizeSwapChain(uint32 width, uint32 height) = 0;

        //////////////////////////////////////////////////////////////
        // State Object 생성
        //////////////////////////////////////////////////////////////

        /**
         * @brief 파이프라인 상태 객체 생성
         * @param desc PSO 설정 구조체 (셰이더, InputLayout, 상태 객체, 토폴로지)
         * @return std::unique_ptr<IPipelineState> 생성된 PSO (소유권은 호출자)
         * @see TDME::IPipelineState
         * @see TDME::PipelineStateDesc
         */
        [[nodiscard]] virtual std::unique_ptr<IPipelineState> CreatePipelineState(const PipelineStateDesc& desc) = 0;

        /**
         * @brief 래스터라이저 상태 객체 생성
         * @param desc 래스터라이저 상태 설정 구조체
         * @return std::unique_ptr<IRasterizerState> 생성된 래스터라이저 상태 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IRasterizerState
         * @see TDME::RasterizerStateDesc
         */
        [[nodiscard]] virtual std::unique_ptr<IRasterizerState> CreateRasterizerState(const RasterizerStateDesc& desc) = 0;

        /**
         * @brief 블렌딩 상태 객체 생성
         * @param desc 블렌딩 상태 설정 구조체
         * @return std::unique_ptr<IBlendState> 생성된 블렌딩 상태 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IBlendState
         * @see TDME::BlendStateDesc
         */
        [[nodiscard]] virtual std::unique_ptr<IBlendState> CreateBlendState(const BlendStateDesc& desc) = 0;

        /**
         * @brief 깊이/스텐실 상태 객체 생성
         * @param desc 깊이/스텐실 상태 설정 구조체
         * @return std::unique_ptr<IDepthStencilState> 생성된 깊이/스텐실 상태 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IDepthStencilState
         * @see TDME::DepthStencilStateDesc
         */
        [[nodiscard]] virtual std::unique_ptr<IDepthStencilState> CreateDepthStencilState(const DepthStencilStateDesc& desc) = 0;

        //////////////////////////////////////////////////////////////
        // Shader 생성
        //////////////////////////////////////////////////////////////

        /**
         * @brief Vertex 셰이더 생성
         * @param byteCode 컴파일된 셰이더 바이트코드
         * @param byteCodeSize 바이트코드 크기
         * @return std::unique_ptr<IVertexShader> 생성된 Vertex 셰이더 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IVertexShader
         */
        [[nodiscard]] virtual std::unique_ptr<IVertexShader> CreateVertexShader(const void* byteCode, uint32 byteCodeSize) = 0;

        /**
         * @brief Pixel 셰이더 생성
         * @param byteCode 컴파일된 셰이더 바이트코드
         * @param byteCodeSize 바이트코드 크기
         * @return std::unique_ptr<IPixelShader> 생성된 Pixel 셰이더 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IPixelShader
         */
        [[nodiscard]] virtual std::unique_ptr<IPixelShader> CreatePixelShader(const void* byteCode, uint32 byteCodeSize) = 0;

        //////////////////////////////////////////////////////////////
        // Resource 생성
        //////////////////////////////////////////////////////////////

        /**
         * @brief Input Layout 생성
         * @param desc 정점 레이아웃 정보 구조체
         * @return std::unique_ptr<IInputLayout> 생성된 정점 레이아웃 포인터 (소유권은 호출자가 가져가야함)
         * @see TDME::IInputLayout
         * @see TDME::InputLayoutDesc
         */
        [[nodiscard]] virtual std::unique_ptr<IInputLayout> CreateInputLayout(const InputLayoutDesc& desc) = 0;

        /**
         * @brief GPU 버퍼 객체 생성 (Vertex/Index)
         * @param desc 버퍼 설정 구조체 (타입, 용도, 크기 등)
         * @param initialData 초기 데이터 포인터 (nullptr이면 빈 버퍼 생성)
         * @return std::unique_ptr<IBuffer> 생성된 버퍼 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::IBuffer
         * @see TDME::BufferDesc
         */
        [[nodiscard]] virtual std::unique_ptr<IBuffer> CreateBuffer(const BufferDesc& desc, const void* initialData = nullptr) = 0;

        /**
         * @brief GPU 텍스처 객체 생성
         * @param desc 텍스처 설정 구조체 (크기, 포맷, 밉맵 등)
         * @param initialData 초기 픽셀 데이터 포인터 (nullptr이면 빈 텍스처 생성)
         * @return std::unique_ptr<ITexture> 생성된 텍스처 객체 (소유권은 호출자가 가져가야함)
         * @see TDME::ITexture
         * @see TDME::TextureDesc
         */
        [[nodiscard]] virtual std::unique_ptr<ITexture> CreateTexture(const TextureDesc& desc, const void* initialData = nullptr) = 0;
    };
} // namespace TDME