#pragma once

#include <Engine/RHI/Texture/ITexture.h>
#include <Engine/RHI/Texture/TextureDesc.h>

#include <d3d9.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    /**
     * @brief DX9 텍스처
     * @details IDirect3DTexture9를 래핑하여 ITexture 인터페이스를 구현.
     *          생성시 초기 데이터(RGBA8 픽셀)을 GPU에 업로드합니다.
     * @see TDME::ITexture
     */
    class DX9Texture : public ITexture
    {
    public:
        /**
         * @brief DX9 텍스처 생성자
         * @param device DX9 Native 디바이스 (텍스처 생성에 사용)
         * @param desc 텍스처 설정
         * @param initialData 초기 픽셀 데이터 (RGBA8, nullptr 허용)
         */
        DX9Texture(IDirect3DDevice9* device, const TextureDesc& desc, const void* initialData);
        ~DX9Texture() override = default;

        //////////////////////////////////////////////////////////////
        // ITexture 구현
        //////////////////////////////////////////////////////////////

        uint32         GetWidth() const override { return m_desc.Width; }
        uint32         GetHeight() const override { return m_desc.Height; }
        uint32         GetMipLevels() const override { return m_desc.MipLevels; }
        ETextureFormat GetFormat() const override { return m_desc.Format; }
        void*          GetNativeHandle() const override { return m_texture.Get(); }

        //////////////////////////////////////////////////////////////
        // Getter/Setter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 텍스처 생성 성공 여부
         */
        [[nodiscard]] bool IsValid() const { return m_texture != nullptr; }

    private:
        TextureDesc               m_desc;
        ComPtr<IDirect3DTexture9> m_texture;
    };
} // namespace TDME