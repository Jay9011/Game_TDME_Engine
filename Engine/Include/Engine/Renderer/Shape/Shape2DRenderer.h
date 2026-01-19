#pragma once

#include <Core/Math/TVector2.h>

#include "Engine/RHI/Vertex/IVertexLayout.h"

#include <memory>

namespace TDME
{
    class IRenderer;
    struct Color;

    /**
     * @brief 2D 도형 렌더러
     */
    class Shape2DRenderer
    {
    public:
        explicit Shape2DRenderer(IRenderer* renderer);
        ~Shape2DRenderer() = default;

        /**
         * @brief 선 그리기
         * @param start 시작 위치
         * @param end 끝 위치
         * @param color 색상
         * @see TDME::Vector2
         * @see TDME::Color
         */
        void DrawLine(const Vector2& start, const Vector2& end, const Color& color);

        /**
         * @brief 삼각형 그리기
         * @param position 위치
         * @param width 너비
         * @param height 높이
         * @param rotation 회전 각도 (도)
         * @param color 색상
         * @see TDME::Vector2
         * @see TDME::Color
         */
        void DrawTriangle(const Vector2& position, float width, float height, float rotation, const Color& color);

        /**
         * @brief 사각형 그리기
         * @param position 위치
         * @param width 너비
         * @param height 높이
         * @param rotation 회전 각도 (도)
         * @param color 색상
         * @see TDME::Vector2
         * @see TDME::Color
         */
        void DrawRect(const Vector2& position, float width, float height, float rotation, const Color& color);

        /**
         * @brief 원 그리기
         * @param position 위치
         * @param radius 반지름
         * @param color 색상
         * @param segments 분할 개수
         * @see TDME::Vector2
         * @see TDME::Color
         * @see TDME::uint32
         */
        void DrawCircle(const Vector2& position, float radius, const Color& color, uint32 segments = 32);

    private:
        IRenderer* m_renderer;

        /**
         * @brief 2D 정점 레이아웃
         * @see TDME::IVertexLayout
         */
        std::unique_ptr<IVertexLayout> m_layoutPC;
    };
} // namespace TDME