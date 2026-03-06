#pragma once

#include <Core/Math/TMatrix4x4.h>
#include <Engine/RHI/IRHIContext.h>
#include <Engine/RHI/IRHIDevice.h>
#include <Engine/Renderer/IRenderer.h>

#include <memory>

namespace TDME
{
    class IBuffer;

    /**
     * @brief DX11 고수준 렌더러
     * @details Constant Buffer 기반 행렬 관리. IRHIContext를 내부적으로 사용.
     */
    class DX11Renderer : public IRenderer
    {
    public:
        DX11Renderer();
        ~DX11Renderer() override;

        //////////////////////////////////////////////////////////////
        // IRenderer
        //////////////////////////////////////////////////////////////

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
         * @note 백버퍼를 클리어하고 프레임을 시작.
         * @param clearColor 클리어 색상
         * @see TDME::Color
         */
        void BeginFrame(const Color& clearColor) override;

        /**
         * @brief 프레임을 종료합니다.
         * @note 백버퍼를 화면에 출력.
         */
        void EndFrame() override;

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

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        void ApplyRenderSettings(const RenderSettings& settings) override;

        /**
         * @brief 스프라이트 랜더링
         * @param sprite 스프라이트 파라미터
         * @see TDME::SpriteDesc
         */
        void DrawSprite(const SpriteDesc& sprite) override;

        /**
         * @brief CPU 메모리 기반 즉시 프리미티브 타입 렌더링 (점, 선, 면)
         * @param type 프리미티브 타입
         * @param vertices CPU 정점 데이터 포인터
         * @param vertexCount 정점 개수
         * @param stride 정점 하나의 바이트 크기
         * @see TDME::EPrimitiveType
         */
        void DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride) override;

        //////////////////////////////////////////////////////////////
        // Getter / Setter
        //////////////////////////////////////////////////////////////

        void SetDevice(IRHIDevice* device) { m_device = device; }
        void SetContext(IRHIContext* context) { m_context = context; }

    private:
        /**
         * @brief Transform CB 데이터를 GPU에 업로드
         */
        void UpdateTransformCB();

    private:
        IRHIDevice*  m_device  = nullptr;
        IRHIContext* m_context = nullptr;

        TransformConstants       m_transformData;
        std::unique_ptr<IBuffer> m_transformBuffer;
    };
} // namespace TDME