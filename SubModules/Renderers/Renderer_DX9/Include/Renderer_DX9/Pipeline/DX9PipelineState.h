#pragma once

#include <Engine/RHI/Pipeline/IPipelineState.h>
#include <Engine/RHI/State/Rasterizer/RasterizerStateDesc.h>
#include <Engine/RHI/State/Blend/BlendStateDesc.h>
#include <Engine/RHI/State/DepthStencil/DepthStencilStateDesc.h>
#include <Engine/Renderer/EPrimitiveType.h>

#include <memory>

namespace TDME
{
    class IInputLayout;

    /**
     * @brief DX9 Pipeline State 클래스
     * @details DX9에는 네이티브 PSO가 없으므로 Desc 값을 저장.
     */
    class DX9PipelineState : public IPipelineState
    {
    public:
        RasterizerStateDesc   RasterizerState;
        BlendStateDesc        BlendState;
        DepthStencilStateDesc DepthStencilState;
        EPrimitiveType        TopologyType = EPrimitiveType::TriangleList;

        std::unique_ptr<IInputLayout> OwnedInputLayout;
        IInputLayout*                 InputLayout = nullptr; // DX9 VertexDeclaration
    };
} // namespace TDME