#pragma once

namespace TDME
{
    /**
     * @brief 파이프라인 상태 객체 (PSO) 인터페이스
     * @details 셰이더, InputLayout, Rasterizer/Blend/DepthStencil, PrimitiveTopology를 하나의 불변 객체(Immutable Object)로 묶음.
     * @note DX12: ID3D12PipelineState, Vulkan: VkPipeline에 대응.
     */
    class IPipelineState
    {
    public:
        virtual ~IPipelineState() = default;
    };
} // namespace TDME