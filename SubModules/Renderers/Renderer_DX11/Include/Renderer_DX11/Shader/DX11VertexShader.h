#pragma once

#include <Engine/RHI/Shader/IVertexShader.h>

#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

namespace TDME
{
    using Microsoft::WRL::ComPtr;

    /**
     * @brief DX11 Vertex Shader 구현체
     * @details Native Shader 객체 + ByteCode 저장 및 관리.
     * @see TDME::IVertexShader
     */
    class DX11VertexShader : public IVertexShader
    {
    public:
        DX11VertexShader(ID3D11Device* device, const void* byteCode, uint32 byteCodeSize);
        ~DX11VertexShader() override = default;

        //////////////////////////////////////////////////////////////
        // Getter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 컴파일된 셰이더 바이트코드 반환
         * @details DX11에서 CreateInputLayout()을 호출할 때, VS의 바이트코드 서명(input signature)이 필요.
         * @return const void* 셰이더 바이트코드 포인터 (InputLayout 생성용, 항상 유효)
         */
        [[nodiscard]] const void* GetByteCode() const override { return m_byteCode.data(); }

        /**
         * @brief 셰이더 바이트코드 크기
         * @return uint32 바이트코드 크기
         */
        [[nodiscard]] uint32 GetByteCodeSize() const override { return static_cast<uint32>(m_byteCode.size()); }

        /**
         * @brief Native DX11 Vertex Shader 객체 반환
         * @return ID3D11VertexShader* Native DX11 Vertex Shader 객체
         */
        [[nodiscard]] ID3D11VertexShader* GetNativeShader() const { return m_shader.Get(); }

        /**
         * @brief Shader 유효성 검사
         * @return true/false Shader 생성 여부
         */
        [[nodiscard]] bool IsValid() const { return m_shader != nullptr; }

    private:
        ComPtr<ID3D11VertexShader> m_shader;
        std::vector<uint8>         m_byteCode; // InputLayout 생성시 필요
    };
} // namespace TDME