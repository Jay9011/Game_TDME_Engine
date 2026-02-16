#include "pch.h"
#include "Renderer_DX9/Texture/DX9Texture.h"

namespace TDME
{
    DX9Texture::DX9Texture(IDirect3DDevice9* device, const TextureDesc& desc, const void* initialData)
        : m_desc(desc)
    {
        if (!device || desc.Width == 0 || desc.Height == 0)
            return;

        // 1. DX9 텍스처 생성
        //    D3DFMT_A8R8G8B8 : DX9에서 RGBA 32비트에 해당 (실제 메모리는 BGRA)
        //    D3DPOOL_MANAGED : GPU + 시스템 메모리 양쪽에 저장. (디바이스 로스트 시 자동 복구)
        HRESULT hr = device->CreateTexture(
            desc.Width,
            desc.Height,
            desc.MipLevels,           // 0이면 전체 밉맵 체인 생성, 1이면 밉맵 없음
            0,                        // Usage (0 = 정적 텍스처)
            D3DFMT_A8R8G8B8,          // DX9의 32비트 RGBA 포맷
            D3DPOOL_MANAGED,          // 메모리 관리 방식
            m_texture.GetAddressOf(), // 생성된 텍스처 포인터
            nullptr                   // SharedHandle (멀티프로세스용)
        );

        if (FAILED(hr) || !m_texture)
            return;

        // 2. 초기 데이터가 있으면 GPU 에 업로드
        if (initialData)
        {
            D3DLOCKED_RECT lockedRect;
            hr = m_texture->LockRect(0, &lockedRect, nullptr, 0);
            if (SUCCEEDED(hr))
            {
                const uint8* src = static_cast<const uint8*>(initialData);
                uint8*       dst = static_cast<uint8*>(lockedRect.pBits);

                const uint32 srcPitch = desc.Width * 4; // RGBA8 = 4 bytes per pixel

                for (uint32 y = 0; y < desc.Height; y++)
                {
                    const uint8* srcRow = src + y * srcPitch;
                    uint8*       dstRow = dst + y * lockedRect.Pitch;

                    for (uint32 x = 0; x < desc.Width; x++)
                    {
                        // RGBA -> BGRA 변환 (DX9의 D3DFMT_A8R8G8B8은 메모리상 BGRA)
                        dstRow[x * 4 + 0] = srcRow[x * 4 + 2]; // B <- R
                        dstRow[x * 4 + 1] = srcRow[x * 4 + 1]; // G <- G
                        dstRow[x * 4 + 2] = srcRow[x * 4 + 0]; // R <- B
                        dstRow[x * 4 + 3] = srcRow[x * 4 + 3]; // A <- A
                    }
                }

                m_texture->UnlockRect(0);
            }
        }
    }

} // namespace TDME