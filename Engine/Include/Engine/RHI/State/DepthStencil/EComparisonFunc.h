#pragma once

#include <Core/CoreTypes.h>

namespace TDME
{
    /**
     * @brief 비교 함수
     * @details 깊이/스텐실 버퍼에서 픽셀 통과 여부를 결정하는 비교 연산
     */
    enum class EComparisonFunc : uint8
    {
        Never,        /** 항상 실패 */
        Less,         /** 새 값 < 기존 값 */
        Equal,        /** 새 값 == 기존 값 */
        LessEqual,    /** 새 값 <= 기존 값 */
        Greater,      /** 새 값 > 기존 값 */
        NotEqual,     /** 새 값 != 기존 값 */
        GreaterEqual, /** 새 값 >= 기존 값 */
        Always,       /** 항상 통과 */
    };
} // namespace TDME