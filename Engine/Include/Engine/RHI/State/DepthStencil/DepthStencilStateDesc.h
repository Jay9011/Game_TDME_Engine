#pragma once

#include <Core/CoreTypes.h>

#include "EComparisonFunc.h"
#include "StencilOpDesc.h"

namespace TDME
{
    /**
     * @brief DepthStencil (깊이/스텐실) 상태 설정 구조체
     * @details IDepthStencilState 생성 시 사용하는 설정 구조체
     * @note 기본값: 깊이 테스트 ON, 깊이 쓰기 ON, 스텐실 OFF
     * @ref EComparisonFunc "EComparisonFunc"
     * @ref EStencilOp "EStencilOp"
     */
    struct DepthStencilStateDesc
    {
        //////////////////////////////////////////////////////////////
        // 깊이 (Depth)
        //////////////////////////////////////////////////////////////

        /**
         * @brief Depth 테스트 활성화 여부
         */
        bool DepthEnable = true;

        /**
         * @brief 깊이 버퍼 쓰기 활성 여부
         */
        bool DepthWriteEnable = true;

        /**
         * @brief 깊이 비교 함수
         * @details 깊이 테스트 시 사용되는 비교 함수
         * @note 기본값: Less (새 값 < 기존 값). (왼손 좌표계에서 카메라 가까운 것이 Z가 작음)
         * @ref EComparisonFunc "EComparisonFunc"
         */
        EComparisonFunc DepthFunc = EComparisonFunc::Less;

        //////////////////////////////////////////////////////////////
        // 스텐실 (Stencil)
        //////////////////////////////////////////////////////////////

        /**
         * @brief Stencil 테스트 활성화 여부
         */
        bool StencilEnable = false;

        /**
         * @brief Stencil 읽기 마스크
         * @details Stencil 테스트 시 사용되는 마스크
         * @note 기본값: 0xFF (모든 비트 활성)
         */
        uint8 StencilReadMask = 0xFF;

        /**
         * @brief Stencil 쓰기 마스크
         * @details Stencil 쓰기 시 사용되는 마스크
         * @note 기본값: 0xFF (모든 비트 활성)
         */
        uint8 StencilWriteMask = 0xFF;

        /**
         * @brief 앞면 스텐실 연산
         */
        StencilOpDesc FrontFace;

        /**
         * @brief 뒷면 스텐실 연산
         */
        StencilOpDesc BackFace;
    };
} // namespace TDME