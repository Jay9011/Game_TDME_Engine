#pragma once

#include <Engine/Renderer/IRenderer.h>
#include <d3d9.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr; // ComPtr은 스마트 포인터와 비슷하게 사용하도록 별칭 선언 (namespace 충돌 염려 없을 것 같음)

    class DX9Renderer : public IRenderer
    {
    public:
        DX9Renderer();
        ~DX9Renderer() override;

        /**
         * @brief 렌더러를 초기화합니다.
         * @param window 창 객체
         * @return true 성공, false 실패
         * @see TDME::IWindow
         */
        bool Initialize(IWindow* window) override;

        /**
         * @brief 렌더러를 종료합니다.
         */
        void Shutdown() override;

        /**
         * @brief 프레임을 시작합니다.
         */
        void BeginFrame(const Color& clearColor) override;

        /**
         * @brief 프레임을 종료합니다.
         */
        void EndFrame() override;

    private:
        /**
         * @brief Direct3D 인터페이스 (Factory) COM 객체
         * @note Direct3D9 API를 사용하기 위해 필요한 첫 번째 객체.
         * @li 어댑터 열거(Adapter Enumeration): 시스템에 설치된 그래픽 어댑터(GPU)가 몇 개인지, 각각의 이름과 드라이버 정보가 무엇인지 조회 가능.
         * @li 디스플레이 모드 열거: 지원하는 해상도, 주사율, 픽셀 포멧 조합을 조회.
         * @li 기능 검사(Capability Check): 특정 기능(멀티 샘플링, 특정 텍스처 포멧, 등)을 하드웨어가 지원하는지 확인.
         * @li 디바이스 생성: 위 정보를 바탕으로 결정한 설정으로 실제 렌더링 디바이스 생성.
         *
         * @see Direct3D9::GetAdapterCount()
         * @see Direct3D9::GetAdapterIdentifier()
         * @see Direct3D9::GetAdapterDisplayMode()
         * @see Direct3D9::CheckDeviceType()
         * @see Direct3D9::CheckDeviceFormat()
         * @see Direct3D9::CheckDeviceFormatConversion()
         * @see Direct3D9::CheckDeviceMultiSampleType()
         * @see Direct3D9::CheckDeviceFormatConversion()
         * @see Direct3D9::CheckDeviceFormatConversion()
         */
        ComPtr<IDirect3D9> m_d3d;

        /**
         * @brief 렌더링 디바이스 (리소스 생성 + 렌더링) COM 객체
         * @note 실제 렌더링을 담당하는 IDirect3DDevice9 인터페이스를 구현한 COM 객체.
         * @li 리소스 생성 (텍스처, 버텍스 버퍼, 인덱스 버퍼, 셰이더)
         * @li 렌더링 상태 설정 (블렌딩, 깊이 테스트, 컬링, 등)
         * @li 드로우 콜 실행 (DrawPrimitive, DrawIndexedPrimitive, DrawTriangles, 등)
         * @li 화면 표시 (Present)
         *
         * @see Direct3DDevice9::CreateTexture()
         * @see Direct3DDevice9::CreateVertexBuffer()
         * @see Direct3DDevice9::CreateIndexBuffer()
         * @see Direct3DDevice9::CreateShader()
         * @see Direct3DDevice9::SetRenderState()
         * @see Direct3DDevice9::DrawPrimitive()
         * @see Direct3DDevice9::DrawIndexedPrimitive()
         * @see Direct3DDevice9::DrawTriangles()
         * @see Direct3DDevice9::Present()
         */
        ComPtr<IDirect3DDevice9> m_device;
    };
} // namespace TDME