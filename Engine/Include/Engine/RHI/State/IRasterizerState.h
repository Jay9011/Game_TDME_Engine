#pragma once

#include "Rasterizer/RasterizerStateDesc.h"

namespace TDME
{
    /**
     * @brief Rasterizer 상태 인터페이스
     * @details Rasterizer 상태를 설정하는 인터페이스. (DX11 스타일 상태 객체.)
     * @note 초기화 시점에 생성하여 재사용.
     * @ref RasterizerStateDesc "RasterizerStateDesc"
     */
    class IRasterizerState
    {
    public:
        virtual ~IRasterizerState() = default;

        /**
         * @brief 상태 설정 구조체 반환
         * @return const RasterizerStateDesc& 상태 설정 구조체
         * @see TDME::RasterizerStateDesc
         */
        virtual const RasterizerStateDesc& GetDesc() const = 0;
    };
} // namespace TDME