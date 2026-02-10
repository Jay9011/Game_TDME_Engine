#pragma once

#include "EBlendFactor.h"
#include "EBlendOp.h"

namespace TDME
{
    /**
     * @brief Blend 상태 설정 구조체
     * @details Blend 상태를 설정하는 구조체
     * @note 기본 값: 블렌딩 비활성화
     */
    struct BlendStateDesc
    {
        /**
         * @brief 블렌딩 활성화 여부
         */
        bool BlendEnable = false;

        /**
         * @brief 소스 색상 블렌드 팩터
         */
        EBlendFactor SrcBlend = EBlendFactor::One;

        /**
         * @brief 대상 색상 블렌드 팩터
         */
        EBlendFactor DestBlend = EBlendFactor::Zero;

        /**
         * @brief 색상 블렌드 연산
         */
        EBlendOp BlendOp = EBlendOp::Add;

        /**
         * @brief 소스 알파 블렌드 팩터
         */
        EBlendFactor SrcBlendAlpha = EBlendFactor::One;

        /**
         * @brief 대상 알파 블렌드 팩터
         */
        EBlendFactor DestBlendAlpha = EBlendFactor::Zero;

        /**
         * @brief 알파 블렌드 연산
         */
        EBlendOp BlendOpAlpha = EBlendOp::Add;
    };
} // namespace TDME