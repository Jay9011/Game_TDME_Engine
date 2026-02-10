#pragma once

#include "Blend/BlendStateDesc.h"

namespace TDME
{
    /**
     * @brief Blend 상태 인터페이스
     * @details Blend 상태를 설정하는 인터페이스. (DX11 스타일 상태 객체.)
     * @note 초기화 시점에 생성하여 재사용.
     * @ref BlendStateDesc "BlendStateDesc"
     */
    class IBlendState
    {
    public:
        virtual ~IBlendState() = default;

        /**
         * @brief 상태 설정 구조체 반환
         * @return const BlendStateDesc& 상태 설정 구조체
         * @see TDME::BlendStateDesc
         */
        virtual const BlendStateDesc& GetDesc() const = 0;
    };
} // namespace TDME