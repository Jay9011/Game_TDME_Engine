#pragma once

#include <Core/Math/TMatrix4x4.h>
#include <Core/Math/TVector2.h>

#include "EPrimitiveType.h"

namespace TDME
{
    class IWindow;
    class ITexture;
    class IVertexLayout;
    struct SpriteDesc;
    struct RenderSettings;
    struct Color;

    /**
     * @brief 렌더러 인터페이스
     * @note 렌더러 기능을 제공하는 인터페이스
     */
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        /**
         * @brief 렌더러를 초기화합니다.
         * @param window 창 객체
         * @return true 성공, false 실패
         * @see TDME::IWindow
         */
        virtual bool Initialize(IWindow* window) = 0;

        /**
         * @brief 렌더러를 종료합니다.
         */
        virtual void Shutdown() = 0;

        /**
         * @brief 프레임을 시작합니다.
         * @note 백버퍼를 클리어하고 프레임을 시작.
         * @param clearColor 클리어 색상
         * @see TDME::Color
         */
        virtual void BeginFrame(const Color& clearColor) = 0;

        /**
         * @brief 프레임을 종료합니다.
         * @note 백버퍼를 화면에 출력.
         */
        virtual void EndFrame() = 0;

        //////////////////////////////////////////////////////////////
        // 행렬 설정 (World, View, Projection)
        //////////////////////////////////////////////////////////////

        /**
         * @brief 월드 행렬 설정
         * @param matrix 월드 행렬
         * @see TDME::Matrix4x4
         */
        virtual void SetWorldMatrix(const Matrix4x4& matrix) = 0;

        /**
         * @brief 뷰 행렬 설정
         * @param matrix 뷰 행렬
         * @see TDME::Matrix4x4
         */
        virtual void SetViewMatrix(const Matrix4x4& matrix) = 0;

        /**
         * @brief 투영 행렬 설정
         * @param matrix 투영 행렬
         * @see TDME::Matrix4x4
         */
        virtual void SetProjectionMatrix(const Matrix4x4& matrix) = 0;

        //////////////////////////////////////////////////////////////
        // 스프라이트 랜더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 스프라이트 랜더링
         * @param sprite 스프라이트 파라미터
         * @see TDME::SpriteDesc
         */
        virtual void DrawSprite(const SpriteDesc& sprite) = 0;

        //////////////////////////////////////////////////////////////
        // 렌더링 설정
        //////////////////////////////////////////////////////////////

        /**
         * @brief 렌더링 설정 적용
         * @param settings 렌더링 설정
         * @see TDME::RenderSettings
         */
        virtual void ApplyRenderSettings(const RenderSettings& settings) = 0;

        //////////////////////////////////////////////////////////////
        // 저수준 프리미티브 렌더링
        //////////////////////////////////////////////////////////////

        /**
         * @brief 정점 레이아웃 설정
         * @param layout 정점 레이아웃 (nullptr 면 해제)
         * @see TDME::IVertexLayout
         */
        virtual void SetVertexLayout(IVertexLayout* layout) = 0;

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
        virtual void DrawPrimitives(EPrimitiveType type, const void* vertices, uint32 vertexCount, uint32 stride) = 0;

        // NOTE: 우선 테스트용 삼각형 그리기 메서드 구현. 추후 다시 확인
        /**
         * @brief 삼각형 그리기
         * @param position 중심 위치 (화면 좌표계)
         * @param width 너비
         * @param height 높이
         * @param rotation 회전 각도 (도)
         * @param color 색상
         * @see TDME::Vector2
         * @see TDME::Color
         */
        virtual void DrawTriangle(const Vector2& position, float width, float height, float rotation, const Color& color) = 0;
    };
} // namespace TDME