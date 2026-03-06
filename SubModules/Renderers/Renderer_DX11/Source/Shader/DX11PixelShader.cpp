#include "pch.h"
#include "Renderer_DX11/Shader/DX11PixelShader.h"

namespace TDME
{
    DX11PixelShader::DX11PixelShader(ID3D11Device* device, const void* byteCode, uint32 byteCodeSize)
    {
        if (!device || !byteCode || byteCodeSize == 0)
            return;

        device->CreatePixelShader(byteCode, byteCodeSize, nullptr, m_shader.GetAddressOf());
    }
} // namespace TDME