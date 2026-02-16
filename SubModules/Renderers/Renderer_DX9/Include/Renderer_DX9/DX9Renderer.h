#pragma once

#include <Core/Math/TMatrix4x4.h>
#include <Engine/RHI/IRHIDevice.h>
#include <Engine/RHI/Vertex/IVertexLayout.h>
#include <Engine/Renderer/IRenderer.h>

#include <d3d9.h>
#include <Windows.h>
#include <memory>

namespace TDME
{
    class DX9Device;

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

        //////////////////////////////////////////////////////////////
        // 행렬 설정 (World, View, Projection)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 월드 행렬 설정
         * @param matrix 월드 행렬
         * @see TDME::Matrix
         */
        void SetWorldMatrix(const Matrix& matrix) override;

        /**
         * @brief 뷰 행렬 설정
         * @param matrix 뷰 행렬
         * @see TDME::Matrix
         */
        void SetViewMatrix(const Matrix& matrix) override;

        /**
         * @brief 투영 행렬 설정
         * @param matrix 투영 행렬
         * @see TDME::Matrix
         */
        void SetProjectionMatrix(const Matrix& matrix) override;

        //////////////////////////////////////////////////////////////
        // 상태 객체 바인딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 래스터라이저 상태 바인딩
         * @param state 래스터라이저 상태 객체 (nullptr이면 무시)
         * @see TDME::IRasterizerState
         */
        void SetRasterizerState(IRasterizerState* state) override;

        /**
         * @brief 블렌딩 상태 바인딩
         * @param state 블렌딩 상태 객체 (nullptr이면 무시)
         * @see TDME::IBlendState
         */
        void SetBlendState(IBlendState* state) override;

        /**
         * @brief 깊이/스텐실 상태 바인딩
         * @param state 깊이/스텐실 상태 객체 (nullptr이면 무시)
         * @see TDME::IDepthStencilState
         */
        void SetDepthStencilState(IDepthStencilState* state) override;

        //////////////////////////////////////////////////////////////
        // 리소스 바인딩
        //////////////////////////////////////////////////////////////

        /**
         * @brief 텍스처를 지정 슬롯에 바인딩
         * @param slot 텍스처 슬롯 번호 (0부터 시작)
         * @param texture 바인딩할 텍스처 (nullptr이면 해당 슬롯 해제)
         * @see TDME::ITexture
         */
        void SetTexture(uint32 slot, ITexture* texture) override;

        //////////////////////////////////////////////////////////////
        // 렌더링 설정
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        void ApplyRenderSettings(const RenderSettings& settings) override;

        //////////////////////////////////////////////////////////////
        // 스프라이트 랜더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 스프라이트 랜더링
         * @param sprite 스프라이트 파라미터
         * @see TDME::SpriteDesc
         */
        void DrawSprite(const SpriteDesc& sprite) override;

        //////////////////////////////////////////////////////////////
        // 저수준 프리미티브 렌더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 레이아웃 설정
         * @param layout 정점 레이아웃 (nullptr 면 해제)
         * @see TDME::IVertexLayout
         */
        void SetVertexLayout(IVertexLayout* layout) override;

        /**
         * @brief 프리미티브 타입 렌더링 (점, 선, 면)
         * @param type 프리미티브 타입
         * @param vertices 정점 데이터 포인터
         * @param vertexCount 정점 개수
         * @param stride 정점 하나의 바이트 크기
         * @see TDME::EPrimitiveType
         * @see TDME::void*
         * @see TDME::uint32
         */
        void DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride) override;

        /**
         * @brief 인덱스 기반 프리미티브 렌더링
         * @note GPU 버퍼를 사용하므로 stride는 vertexBuffer에서 직접 가져옴.
         * @note indexCount는 버퍼의 전체가 아닌 일부만 렌더링 할 수 있도록 할 수 있도록 함.
         * @param type 프리미티브 타입
         * @param vertexBuffer 정점 버퍼
         * @param indexBuffer 인덱스 버퍼
         * @param indexCount 인덱스 개수
         * @see TDME::EPrimitiveType
         * @see TDME::IBuffer
         */
        void DrawIndexedPrimitives(EPrimitiveType type, IBuffer* vertexBuffer, IBuffer* indexBuffer, uint32 indexCount) override;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 디바이스 설정
         * @param device 디바이스
         * @see TDME::DX9Device
         */
        void SetDevice(DX9Device* device);

    private:
        DX9Device*        m_device       = nullptr; // Engine 디바이스 객체
        IDirect3DDevice9* m_nativeDevice = nullptr; // Direct3D 9 디바이스 객체

        IVertexLayout* m_currentLayout = nullptr;
    };
} // namespace TDME