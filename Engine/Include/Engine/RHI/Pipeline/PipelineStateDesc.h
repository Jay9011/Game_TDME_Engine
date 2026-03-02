#pragma once

#include "Engine/Renderer/EPrimitiveType.h"
#include "Engine/RHI/State/Blend/BlendStateDesc.h"
#include "Engine/RHI/State/DepthStencil/DepthStencilStateDesc.h"
#include "Engine/RHI/State/Rasterizer/RasterizerStateDesc.h"
#include "Engine/RHI/Vertex/InputLayoutDesc.h"

namespace TDME
{
    class IVertexShader;
    class IPixelShader;

    /**
     * @brief PSO 생성 구조체
     * @details CreatePipelineState()에 전달하여 PSO 생성.
     * @note PSO에 포함되는 항목: VS, PS, InputLayout, RS, Blend, DS, Topology
     *       PSO에 미포함 항목: VertexBuffer, IndexBuffer, ConstantBuffer, Texture, Sampler, Viewport
     */
    struct PipelineStateDesc
    {
        IVertexShader*        VS = nullptr;
        IPixelShader*         PS = nullptr;
        InputLayoutDesc       InputLayout;
        RasterizerStateDesc   RasterizerState;
        BlendStateDesc        BlendState;
        DepthStencilStateDesc DepthStencilState;
        EPrimitiveType        TopologyType = EPrimitiveType::TriangleList;
    };
} // namespace TDME