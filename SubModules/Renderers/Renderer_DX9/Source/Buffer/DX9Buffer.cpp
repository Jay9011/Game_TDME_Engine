#include "pch.h"
#include "Renderer_DX9/Buffer/DX9Buffer.h"

#include <Engine/RHI/Buffer/EBufferUsage.h>
#include <cstring>

namespace TDME
{
    DX9Buffer::DX9Buffer(IDirect3DDevice9* device, const BufferDesc& desc, const void* initialData)
        : m_desc(desc)
    {
        if (!device || desc.ByteSize == 0)
            return;

        // Usage/Pool 결정
        //      Default -> D3DPOOL_MANAGED (GPU + 시스템 메모리, 디바이스 로스트 자동 복구)
        //      Dynamic -> D3DPOOL_DEFAULT + D3DUSAGE_DYNAMIC (빠른 CPU 갱신)
        const DWORD   usage = (desc.Usage == EBufferUsage::Dynamic) ? D3DUSAGE_DYNAMIC : 0;
        const D3DPOOL pool  = (desc.Usage == EBufferUsage::Dynamic) ? D3DPOOL_DEFAULT : D3DPOOL_MANAGED;

        HRESULT hr;
        if (desc.Type == EBufferType::Vertex) // Buffer Type이 Vertex인 경우 Vertex Buffer 생성
        {
            hr = device->CreateVertexBuffer(
                desc.ByteSize,
                usage,
                0, // FVF (Vertex Declaration 사용시 0)
                pool,
                m_vertexBuffer.GetAddressOf(),
                nullptr);
        }
        else // Buffer Type이 Index인 경우 Index Buffer 생성
        {
            hr = device->CreateIndexBuffer(
                desc.ByteSize,
                usage,
                D3DFMT_INDEX16, // 16비트 인덱스 (uint16, 65535 정점까지)
                pool,
                m_indexBuffer.GetAddressOf(),
                nullptr);
        }

        if (FAILED(hr))
            return;

        // 초기 데이터 업로드
        if (initialData)
        {
            Update(initialData, desc.ByteSize);
        }
    }

    bool DX9Buffer::Update(const void* data, uint32 size)
    {
        if (!data || size == 0 || !IsValid())
        {
            return false;
        }

        void* locked = nullptr;

        // Lock -> memcpy -> Unlock 패턴
        HRESULT     hr;
        const DWORD lockFlags = (m_desc.Usage == EBufferUsage::Dynamic) ? D3DLOCK_DISCARD : 0;
        if (m_desc.Type == EBufferType::Vertex) // Vertex Buffer인 경우
        {
            hr = m_vertexBuffer->Lock(0, size, &locked, lockFlags);
        }
        else // Index Buffer인 경우
        {
            hr = m_indexBuffer->Lock(0, size, &locked, lockFlags);
        }

        if (FAILED(hr) || !locked)
        {
            return false;
        }

        std::memcpy(locked, data, size);

        if (m_desc.Type == EBufferType::Vertex) // Vertex Buffer인 경우
        {
            m_vertexBuffer->Unlock();
        }
        else // Index Buffer인 경우
        {
            m_indexBuffer->Unlock();
        }

        return true;
    }

    void* DX9Buffer::GetNativeHandle() const
    {
        if (m_desc.Type == EBufferType::Vertex) // Vertex Buffer인 경우
        {
            return m_vertexBuffer.Get();
        }
        else // Index Buffer인 경우
        {
            return m_indexBuffer.Get();
        }
    }

    bool DX9Buffer::IsValid() const
    {
        if (m_desc.Type == EBufferType::Vertex) // Vertex Buffer인 경우
        {
            return m_vertexBuffer != nullptr;
        }
        else // Index Buffer인 경우
        {
            return m_indexBuffer != nullptr;
        }
    }
} // namespace TDME