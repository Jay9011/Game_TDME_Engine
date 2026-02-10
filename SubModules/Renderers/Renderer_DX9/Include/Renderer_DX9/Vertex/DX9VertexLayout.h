#pragma once

#include <Engine/RHI/Vertex/IVertexLayout.h>

#include <d3d9.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr; // ComPtr은 스마트 포인터와 비슷하게 사용하도록 별칭 선언 (namespace 충돌 염려 없을 것 같음)

    struct VertexLayoutDesc;

    class DX9VertexLayout : public IVertexLayout
    {
    public:
        /**
         * @brief 생성자
         * @param device Direct3D 렌더링 디바이스
         * @param desc 버텍스 레이아웃 정보 구조체
         */
        DX9VertexLayout(IDirect3DDevice9* device, const VertexLayoutDesc& desc);
        ~DX9VertexLayout() override = default;

        /**
         * @brief 정점 하나의 바이트 크기 반환
         * @return 바이트 크기
         */
        uint32 GetStride() const override;

        /**
         * @brief 요소 개수 반환
         * @return 요소 개수
         */
        size_t GetElementCount() const override;

        /**
         * @brief Direct3D 버텍스 레이아웃 객체 반환
         * @return 네이티브 버텍스 레이아웃 객체
         */
        IDirect3DVertexDeclaration9* GetNativeDeclaration() const;

    private:
        ComPtr<IDirect3DVertexDeclaration9> m_declaration;

        uint32 m_stride;
        size_t m_elementCount;
    };
} // namespace TDME