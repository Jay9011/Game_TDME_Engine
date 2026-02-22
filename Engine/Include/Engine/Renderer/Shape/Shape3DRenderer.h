#pragma once

#include <Core/CoreTypes.h>
#include <Core/Math/TMatrix4x4.h>

#include "Engine/RHI/IRHIDevice.h"
#include "Engine/RHI/Buffer/IBuffer.h"
#include "Engine/RHI/Vertex/IVertexLayout.h"
#include <memory>

namespace TDME
{
    struct Color;
    class IRenderer;
    class IRHIDevice;
    class ITexture;

    /**
     * @brief 3D 도형 렌더러
     * @details UV Sphere를 Index 기반으로 생성하여 GPU 버퍼에 캐싱한다.
     * @note 색상 기반(DrawSphere)과 텍스처 기반(DrawTexturedSphere)을 모두 지원
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

        /**
         * @brief 텍스처 구(Sphere) 그리기
         * @param worldMatrix 월드 행렬
         * @param radius 반지름
         * @param texture 텍스처
         * @param stacks 세로 줄 분할 수 (위도)
         * @param slices 가로 줄 분할 수 (경도)
         * @see TDME::Matrix
         * @see TDME::ITexture
         */
        void DrawTexturedSphere(const Matrix& worldMatrix, float radius, ITexture* texture, uint32 stacks = 16, uint32 slices = 32);

    private:
        /**
         * @brief Sphere 인덱스 버퍼 생성 (stacks x slices 공통)
         * @param stacks 세로 줄 분할 수 (위도)
         * @param slices 가로 줄 분할 수 (경도)
         */
        void BuildSphereBuffers(uint32 stacks, uint32 slices);

    private:
        IRHIDevice* m_device   = nullptr;
        IRenderer*  m_renderer = nullptr;

        std::unique_ptr<IVertexLayout> m_colorLayout   = nullptr; // 3D 정점 레이아웃 (Position, Color)
        std::unique_ptr<IVertexLayout> m_textureLayout = nullptr; // 3D 정점 레이아웃 (Position, UV)

        //////////////////////////////////////////////////////////////
        // Sphere GPU 버퍼 (캐싱 전략)
        // BuildSphereBuffers는 stacks/slices가 변경될 때만 다시 호출.
        // 같은 파라미터라면 이전에 만든 GPU 버퍼를 재사용 (Sphere의 모양은 버퍼에 고정되고, 크기(radius)는 월드 행렬의 스케일로 처리)
        //////////////////////////////////////////////////////////////
        std::unique_ptr<IBuffer> m_sphereVB = nullptr; // 텍스처용 정점 버퍼 (VertexPT)
        std::unique_ptr<IBuffer> m_sphereIB = nullptr; // 인덱스 버퍼 (uint16)

        uint32 m_cachedStacks = 0; // 캐싱된 stacks
        uint32 m_cachedSlices = 0; // 캐싱된 slices
        uint32 m_indexCount   = 0; // 인덱스 개수
    };
} // namespace TDME