#pragma once

#include <Engine/RHI/IRHIDevice.h>

#include <d3d9.h>
#include <wrl/client.h>
#include <memory>

namespace TDME
{
    using Microsoft::WRL::ComPtr; // ComPtr은 스마트 포인터와 비슷하게 사용하도록 별칭 선언 (namespace 충돌 염려 없을 것 같음)

    class DX9Device : public IRHIDevice
    {
    public:
        DX9Device();
        ~DX9Device() override;

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

        //////////////////////////////////////////////////////////////
        // SwapChain
        //////////////////////////////////////////////////////////////
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

        //////////////////////////////////////////////////////////////
        // 리소스 생성
        //////////////////////////////////////////////////////////////

        /**
         * @brief Vertex 레이아웃 생성
         * @param desc 정점 레이아웃 정보 구조체
         * @return 생성된 정점 레이아웃 포인터 (소유권은 호출자가 가져가야함)
         * @see TDME::IVertexLayout
         * @see TDME::VertexLayoutDesc
         */
        [[nodiscard]] std::unique_ptr<IVertexLayout> CreateVertexLayout(const VertexLayoutDesc& desc) override;

        //////////////////////////////////////////////////////////////
        // Getter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 네이티브 DX9 디바이스 반환
         * @return IDirect3DDevice9 포인터
         * @see IDirect3DDevice9
         */
        IDirect3DDevice9* GetNativeDevice() const { return m_device.Get(); }

    private:
        ComPtr<IDirect3D9>       m_d3d;
        ComPtr<IDirect3DDevice9> m_device;
    };
} // namespace TDME