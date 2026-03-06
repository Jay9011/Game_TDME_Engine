#pragma once

#include <Engine/RHI/Shader/IPixelShader.h>

#include <d3d11.h>
#include <wrl/client.h>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    /**
     * @brief DX11 Pixel Shader 구현체
     * @details Native Shader 객체 저장 및 관리.
     * @see TDME::IPixelShader
     */
    class DX11PixelShader : public IPixelShader
    {
    public:
        DX11PixelShader(ID3D11Device* device, const void* byteCode, uint32 byteCodeSize);
        ~DX11PixelShader() override = default;

        //////////////////////////////////////////////////////////////
        // Getter
        //////////////////////////////////////////////////////////////

        /**
         * @brief PS는 InputLayout 생성에 관여하지 않으므로 바이트코드 미보관
         * @return nullptr
         */
        [[nodiscard]] const void* GetByteCode() const override { return nullptr; }

        /**
         * @brief PS 바이트코드 크기 (미보관)
         * @return 0
         */
        [[nodiscard]] uint32 GetByteCodeSize() const override { return 0; }

        /**
         * @brief Native DX11 Pixel Shader 객체 반환
         * @return ID3D11PixelShader* Native DX11 Pixel Shader 객체
         */
        [[nodiscard]] ID3D11PixelShader* GetNativeShader() const { return m_shader.Get(); }

        /**
         * @brief Shader 유효성 검사
         * @return true/false Shader 생성 여부
         */
        [[nodiscard]] bool IsValid() const { return m_shader != nullptr; }

    private:
        ComPtr<ID3D11PixelShader> m_shader;
    };
} // namespace TDME