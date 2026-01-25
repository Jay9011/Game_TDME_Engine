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
         * @see TDME::Matrix4x4
         */
        void SetWorldMatrix(const Matrix4& matrix) override;

        /**
         * @brief 뷰 행렬 설정
         * @param matrix 뷰 행렬
         * @see TDME::Matrix4x4
         */
        void SetViewMatrix(const Matrix4& matrix) override;

        /**
         * @brief 투영 행렬 설정
         * @param matrix 투영 행렬
         * @see TDME::Matrix4x4
         */
        void SetProjectionMatrix(const Matrix4& matrix) override;

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
        // 렌더링 설정
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        void ApplyRenderSettings(const RenderSettings& settings) override;

        /**
         * @brief 렌더링 모드 설정
         * @param mode 렌더링 모드
         * @see TDME::ERenderMode
         */
        void SetRenderMode(ERenderMode mode) override;

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