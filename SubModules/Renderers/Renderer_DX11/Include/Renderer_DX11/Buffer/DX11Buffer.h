#pragma once

#include <Engine/RHI/Buffer/IBuffer.h>
#include <Engine/RHI/Buffer/BufferDesc.h>

#include <d3d11.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    /**
     * @brief DX11 버퍼 구현체 (Vertex/Index/Constant 통합)
     * @details ID3D11Buffer 하나로 BindFlags에 따라 Vertex/Index/Constant 버퍼 모두 처리.
     * @see TDME::IBuffer
     */
    class DX11Buffer : public IBuffer
    {
    public:
        DX11Buffer(ID3D11Device* device, const BufferDesc& desc, const void* initialData);
        ~DX11Buffer() override = default;

        /**
         * @brief 버퍼 데이터 갱신 (Dynamic 버퍼용)
         * @param data 데이터 포인터
         * @param size 데이터 크기 (바이트)
         * @return true/false 성공/실패
         */
        bool Update(const void* data, uint32 size) override;

        //////////////////////////////////////////////////////////////
        // Getter
        //////////////////////////////////////////////////////////////

        EBufferType  GetType() const override { return m_desc.Type; }
        EBufferUsage GetUsage() const override { return m_desc.Usage; }
        uint32       GetByteSize() const override { return m_desc.ByteSize; }
        uint32       GetStride() const override { return m_desc.Stride; }
        void*        GetNativeHandle() const override { return m_buffer.Get(); }

        [[nodiscard]] bool IsValid() const { return m_buffer != nullptr; }

    private:
        BufferDesc           m_desc;
        ComPtr<ID3D11Buffer> m_buffer;
    };
} // namespace TDME