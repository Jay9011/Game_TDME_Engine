#pragma once

#include <Core/CoreTypes.h>

#include "EShaderType.h"

namespace TDME
{
    class IShader
    {
    public:
        virtual ~IShader() = default;

        //////////////////////////////////////////////////////////////
        // Getter
        //////////////////////////////////////////////////////////////

        /**
         * @brief 셰이더 타입 반환
         * @return EShaderType 셰이더 타입
         */
        [[nodiscard]] virtual EShaderType GetType() const = 0;

        /**
         * @brief 컴파일된 셰이더 바이트코드 반환
         * @details DX11에서 CreateInputLayout()을 호출할 때, VS의 바이트코드 서명(input signature)이 필요.
         * @return const void* 셰이더 바이트코드 포인터
         */
        [[nodiscard]] virtual const void* GetByteCode() const = 0;

        /**
         * @brief 셰이더 바이트코드 크기
         * @return uint32 바이트코드 크기
         */
        [[nodiscard]] virtual uint32 GetByteCodeSize() const = 0;
    };
} // namespace TDME