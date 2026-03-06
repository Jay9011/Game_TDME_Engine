#include "pch.h"
#include "Renderer_DX11/Buffer/DX11Buffer.h"

#include "Renderer_DX11/DX11TypeConversion.h"

namespace TDME
{
    DX11Buffer::DX11Buffer(ID3D11Device* device, const BufferDesc& desc, const void* initialData)
        : m_desc(desc)
    {
        if (!device || desc.ByteSize == 0)
            return;

        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth         = desc.ByteSize;

        // Usage 결정
        bufferDesc.Usage          = (desc.Usage == EBufferUsage::Dynamic) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
        bufferDesc.CPUAccessFlags = (desc.Usage == EBufferUsage::Dynamic) ? D3D11_CPU_ACCESS_WRITE : 0;

        // BindFlags 결정
        bufferDesc.BindFlags = ToDX11BindFlags(desc.Type);

        // 초기 데이터 설정
        D3D11_SUBRESOURCE_DATA  initData  = {};
        D3D11_SUBRESOURCE_DATA* pInitData = nullptr;
        if (initialData)
        {
            initData.pSysMem = initialData;
            pInitData        = &initData;
        }

        device->CreateBuffer(&bufferDesc, pInitData, m_buffer.GetAddressOf());
    }

    bool DX11Buffer::Update(const void* data, uint32 size)
    {
        return false;
    }
} // namespace TDME