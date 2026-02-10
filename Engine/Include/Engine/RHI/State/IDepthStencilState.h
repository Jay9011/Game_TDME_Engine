#pragma once

#include "DepthStencil/DepthStencilStateDesc.h"

namespace TDME
{
    /**
     * @brief DepthStencil (깊이/스텐실) 상태 인터페이스
     * @details DepthStencil (깊이/스텐실) 상태를 설정하는 인터페이스. (DX11 스타일 상태 객체.)
     * @note 초기화 시점에 생성하여 재사용.
     * @ref DepthStencilStateDesc "DepthStencilStateDesc"
     */
    class IDepthStencilState
    {
    public:
        virtual ~IDepthStencilState() = default;

        /**
         * @brief 상태 설정 구조체 반환
         * @return const DepthStencilStateDesc& 상태 설정 구조체
         * @see TDME::DepthStencilStateDesc
         */
        virtual const DepthStencilStateDesc& GetDesc() const = 0;
    };
} // namespace TDME