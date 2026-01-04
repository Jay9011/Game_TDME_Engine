#pragma once

#include <Core/CoreTypes.h>
#include <cstddef>

namespace TDME
{
    /**
     * @brief Vertex 레이아웃 인터페이스
     * @details 플랫폼별 네이티브 정점 레이아웃 객체의 추상화
     * @note DX9: IDirect3DVertexDeclaration9
     * @note DX11: ID3D11InputLayout
     * @note Vulkan: VkPipelineVertexInputStateCreateInfo
     */
    class IVertexLayout
    {
    public:
        virtual ~IVertexLayout() = default;

        /**
         * @brief 정점 하나의 바이트 크기 반환
         * @return 바이트 크기
         */
        virtual uint32 GetStride() const = 0;

        /**
         * @brief 요소 개수 반환
         * @return 요소 개수
         */
        virtual size_t GetElementCount() const = 0;
    };
} // namespace TDME