#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 블렌드 팩터 (혼합 방식)
     * @details 소스/대상 색상의 혼합 방식을 지정
     */
    enum class EBlendFactor : uint8
    {
        Zero,         /** 0 */
        One,          /** 1 */
        SrcAlpha,     /** 소스 알파 */
        InvSrcAlpha,  /** 소스 알파의 반대 */
        DestAlpha,    /** 대상 알파 */
        InvDestAlpha, /** 대상 알파의 반대 */
        SrcColor,     /** 소스 색상 */
        InvSrcColor,  /** 소스 색상의 반대 */
        DestColor,    /** 대상 색상 */
        InvDestColor, /** 대상 색상의 반대 */
    };
} // namespace TDME