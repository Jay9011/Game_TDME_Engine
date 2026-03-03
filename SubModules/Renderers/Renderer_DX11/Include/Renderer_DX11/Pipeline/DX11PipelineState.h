#pragma once

#include <Engine/RHI/Pipeline/IPipelineState.h>
#include <Engine/Renderer/EPrimitiveType.h>

#include <d3d11.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    class IInputLayout;

    /**
     * @brief DX11 Pipeline State 클래스
     * @details DX11에는 네이티브 PSO가 없으므로 SetPipelineState시 개별 COM State Object를 DeviceContext에 바인딩하는 방식으로 분해.
     */
    class DX11PipelineState : public IPipelineState
    {
    public:
        ComPtr<ID3D11InputLayout>       InputLayout;
        ComPtr<ID3D11RasterizerState>   RasterizerState;
        ComPtr<ID3D11BlendState>        BlendState;
        ComPtr<ID3D11DepthStencilState> DepthStencilState;

        // Shaders (관찰용 - 소유권은 호출자가)
        ID3D11VertexShader* VS = nullptr;
        ID3D11PixelShader*  PS = nullptr;

        // Topology
        D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    };
} // namespace TDME