#include "pch.h"
#include "Renderer_DX11/Shader/DX11VertexShader.h"

namespace TDME
{
    DX11VertexShader::DX11VertexShader(ID3D11Device* device, const void* byteCode, uint32 byteCodeSize)
    {
        if (!device || !byteCode || byteCodeSize == 0)
            return;

        m_byteCode.assign(
            static_cast<const uint8*>(byteCode),
            static_cast<const uint8*>(byteCode) + byteCodeSize);

        device->CreateVertexShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
    }
} // namespace TDME