#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    class IWindow;
    class ITexture;
    class IBuffer;
    class IVertexLayout;
    struct SwapChainDesc;
    struct TextureDesc;
    struct BufferDesc;
    struct VertexLayoutDesc;

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
    };
} // namespace TDME