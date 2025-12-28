#pragma once

#include "Core/Math/TVector2.h"
namespace TDME
{
    class IWindow;
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
        // 2D 렌더링 관련 메서드
        //////////////////////////////////////////////////////////////

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