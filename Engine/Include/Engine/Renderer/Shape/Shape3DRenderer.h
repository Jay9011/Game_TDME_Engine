#pragma once

#include <Core/CoreTypes.h>
#include <Core/Math/TMatrix4x4.h>

#include "Engine/RHI/Vertex/IVertexLayout.h"
#include <memory>

namespace TDME
{
    class IRenderer;
    class IRHIDevice;
    struct Color;

    /**
     * @brief 3D 도형 렌더러
     */
    class Shape3DRenderer
    {
    public:
        explicit Shape3DRenderer(IRenderer* renderer, IRHIDevice* device);
        ~Shape3DRenderer() = default;

        /**
         * @brief 구(Sphere) 그리기
         * @param worldMatrix 월드 행렬
         * @param radius 반지름
         * @param color 색상
         * @param stacks 세로 줄 분할 수 (위도)
         * @param slices 가로 줄 분할 수 (경도)
         * @see TDME::Matrix
         * @see TDME::Color
         * @see TDME::uint32
         */
        void DrawSphere(const Matrix& worldMatrix, float radius, const Color& color, uint32 stacks = 16, uint32 slices = 32);

    private:
        IRenderer*  m_renderer = nullptr;
        IRHIDevice* m_device   = nullptr;

        std::unique_ptr<IVertexLayout> m_colorLayout = nullptr; // 3D 정점 레이아웃 (Position, Color)
    };
} // namespace TDME