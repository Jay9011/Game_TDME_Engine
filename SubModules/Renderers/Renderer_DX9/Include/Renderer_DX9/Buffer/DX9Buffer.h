#pragma once

#include <Engine/RHI/Buffer/IBuffer.h>
#include <Engine/RHI/Buffer/BufferDesc.h>

#include <d3d9.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    /**
     * @brief DX9 버퍼 구현체 (Vertex/Index 통합)
     * @details EBufferType에 따라 내부적으로 IDirect3DVertexBuffer9 또는 IDirect3DIndexBuffer9를 생성하여 래핑
     * @see TDME::IBuffer
     */
    class DX9Buffer : public IBuffer
    {
    public:
        /**
         * @briefDX9 버퍼 생성
         * @param device DX9 네이티브 디바이스
         * @param desc 버퍼 설정 (타입, 용도, 크기)
         * @param initialData 초기 데이터 (nullptr 허용)
         */
        DX9Buffer(IDirect3DDevice9* device, const BufferDesc& desc, const void* initialData);
        ~DX9Buffer() override = default;

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
        void*        GetNativeHandle() const override;

        /** @brief 버퍼 생성 성공 여부 */
        [[nodiscard]] bool IsValid() const;

    private:
        BufferDesc m_desc;

        ComPtr<IDirect3DVertexBuffer9> m_vertexBuffer;
        ComPtr<IDirect3DIndexBuffer9>  m_indexBuffer;
    };
} // namespace TDME