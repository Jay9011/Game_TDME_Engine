#pragma once

#include "IShader.h"

namespace TDME
{
    class IPixelShader : public IShader
    {
    public:
        /**
         * @brief 셰이더 타입 반환
         * @return EShaderType 셰이더 타입
         */
        [[nodiscard]] virtual EShaderType GetType() const override { return EShaderType::Pixel; }
    };
} // namespace TDME