#pragma once

#include "IShader.h"

namespace TDME
{
    /**
     * @brief Vertex Shader 인터페이스
     */
    class IVertexShader : public IShader
    {
    public:
        /**
         * @brief 셰이더 타입 반환
         * @return EShaderType 셰이더 타입
         */
        [[nodiscard]] virtual EShaderType GetType() const override { return EShaderType::Vertex; }
    };
} // namespace TDME