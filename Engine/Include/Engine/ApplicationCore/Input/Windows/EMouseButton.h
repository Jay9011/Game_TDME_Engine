#pragma once

#include "Core/CoreTypes.h"

namespace TDME
{
    /**
     * @brief 마우스 버튼 코드
     * @see <winuser.h>
     * @see https://learn.microsoft.com/en-us/windows/win32/inputdev/mouse-input-concepts
     */
    enum class EMouseButton : uint8
    {
        Left     = 0x01,
        Right    = 0x02,
        Middle   = 0x04,
        XButton1 = 0x05,
        XButton2 = 0x06,

        COUNT
    };
} // namespace TDME