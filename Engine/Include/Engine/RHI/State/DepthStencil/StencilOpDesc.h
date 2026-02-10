#pragma once

#include "EComparisonFunc.h"
#include "EStencilOp.h"

namespace TDME
{
    /**
     * @brief 스텐실 연산 서술자
     * @details 스텐실 테스트 결과별 수행할 연산을 정의
     */
    struct StencilOpDesc
    {
        /**
         * @brief 스텐실 테스트 실패 시 수행할 연산
         */
        EStencilOp StencilFailOp = EStencilOp::Keep;

        /**
         * @brief 스텐실 통과, 깊이 테스트 실패 시 수행할 연산
         */
        EStencilOp StencilDepthFailOp = EStencilOp::Keep;

        /**
         * @brief 스텐실, 깊이 모두 통과 시 수행할 연산
         */
        EStencilOp StencilPassOp = EStencilOp::Keep;

        /**
         * @brief 스텐실 비교 함수
         */
        EComparisonFunc StencilFunc = EComparisonFunc::Always;
    };
} // namespace TDME